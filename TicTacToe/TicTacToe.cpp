// TicTacToe.cpp : Defines the entry point for the application.
//
#include <Windows.h>
#include "framework.h"
#include "TicTacToe.h"
#include "windowsx.h"
#include <gdiplus.h>


#define MAX_LOADSTRING 100
void Draw(HDC hdc, int xpos, int ypos, Gdiplus::Bitmap bmp);
// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.

	// Initialize global strings
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_TICTACTOE, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TICTACTOE));
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);
	MSG msg;

	// Main message loop:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TICTACTOE));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	//wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
	wcex.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_TICTACTOE);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
// wat=
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Almacenar identificador de instancia en una variable global

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

const int CELL_SIZE = 100;

HICON hIcon1, hIcon2, hIcon3, hIcon4, hIcon5;
bool paint = false;
HWND button;

BOOL GetGameBoardRect(HWND hWnd, RECT* pRect) {
	RECT rc;
	if (GetClientRect(hWnd, &rc))
	{
		int width = rc.right - rc.left;
		int height = rc.bottom - rc.top;
		pRect->left = (width - CELL_SIZE * 8) / 2;
		pRect->top = (height - CELL_SIZE * 8) / 2;
		pRect->bottom = pRect->top + CELL_SIZE * 8;
		pRect->right = pRect->left + CELL_SIZE * 8;
		return TRUE;
	}
	SetRectEmpty(pRect);
	return FALSE;
}

void DrawLine(HDC hdc, int xa, int ya, int xb, int yb)
{
	MoveToEx(hdc, xa, ya, nullptr);
	LineTo(hdc, xb, yb);
}

int GetNumber(HWND hWnd, int x, int y)
{
	POINT p = { x, y };
	RECT rc;
	if (GetGameBoardRect(hWnd, &rc))
	{
		if (PtInRect(&rc, p))
		{
			x = p.x - rc.left;
			y = p.y - rc.top;
			int col = x / CELL_SIZE;
			int row = y / CELL_SIZE;
			return col + row * 8;
		}
		else
		{
			return -1;
		}
	}
	return -1;
}

BOOL GetCell(HWND hWnd, int index, RECT * pRect)
{
	RECT board;
	SetRectEmpty(pRect);
	if (index < 0 || index > 63) return false;

	if (GetGameBoardRect(hWnd, &board))
	{
		int y = index / 8;
		int x = index % 8;
		pRect->left = board.left + x * CELL_SIZE;
		pRect->top = board.top + y * CELL_SIZE;

		pRect->right = pRect->left + CELL_SIZE;
		pRect->bottom = pRect->top + CELL_SIZE;
		return true;

	}
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;


		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;

	case WM_CREATE: {
		//brush = CreateSolidBrush(RGB(230,20,30));
		//carga de los iconos 
		hIcon1 = LoadIcon(hInst, MAKEINTRESOURCE(IDI_PIOLINMAMADO));
		hIcon2 = LoadIcon(hInst, MAKEINTRESOURCE(IDI_PIOLINKARATE));
		hIcon3 = LoadIcon(hInst, MAKEINTRESOURCE(IDI_PIOLINCOR));
		hIcon4 = LoadIcon(hInst, MAKEINTRESOURCE(IDI_PIOLINSSJ));
		hIcon5 = LoadIcon(hInst, MAKEINTRESOURCE(IDI_TICTACTOE));


	}
					break;
	case WM_LBUTTONDOWN: {
		short xPos = GET_X_LPARAM(lParam);
		short yPos = GET_Y_LPARAM(lParam);
		int index = GetNumber(hWnd, xPos, yPos);
		HDC hdc = GetDC(hWnd);
		if (hdc != NULL)
		{
			WCHAR temp[100];
			wsprintf(temp, L"[%d]", index);
			TextOut(hdc, xPos, yPos, temp, lstrlen(temp));
			if (paint == false && index == -1)
			{
				paint = true;

				// TODO: Add any drawing code that uses hdc here...
				RECT rc;
				if (GetGameBoardRect(hWnd, &rc))
				{
					FillRect(hdc, &rc, (HBRUSH)GetStockObject(WHITE_BRUSH));
					Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
				}
				int index = 0;
				if (hdc != NULL)
				{
					WCHAR temp[100];
					wsprintf(temp, L"[%d]", index);

				}

			}
			if (index != -1)
			{
				RECT rect;
				if (GetCell(hWnd, index, &rect))
				{
					for (int i = 0; i <= index; i++)
					{
						FillRect(hdc, &rect, (HBRUSH)GetStockObject(BLACK_BRUSH));
						DrawIcon(hdc, rect.left + CELL_SIZE / 2 - 16, rect.top + CELL_SIZE / 2 - 16, hIcon1);
					}

				}
			}
			ReleaseDC(hWnd, hdc);
		}
	}
						 break;
	case WM_GETMINMAXINFO:
	{
		MINMAXINFO* pMinMax = (MINMAXINFO*)lParam;
		if (pMinMax != nullptr) {
			pMinMax->ptMinTrackSize.x = CELL_SIZE * 5;
			pMinMax->ptMinTrackSize.y = CELL_SIZE * 5;
		}


	}
	break;
	case WM_PAINT:
	{
	
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		if (paint == false)
		{
			int index = 36;
			RECT rect;
			if (GetCell(hWnd, index, &rect))
			{
			}
			Draw(hdc, 0, 0, L"PiolinMenu.png");
		}
		if (paint == true) 
		{
			DestroyIcon(hIcon5);
			// TODO: Add any drawing code that uses hdc here...
			RECT rc;
			if (GetGameBoardRect(hWnd, &rc))
			{
				FillRect(hdc, &rc, (HBRUSH)GetStockObject(WHITE_BRUSH));
				Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
			}
			int index = 0;
			if (hdc != NULL)
			{
				WCHAR temp[100];
				wsprintf(temp, L"[%d]", index);
				for (index; index < 64; index++)
				{
					RECT rect;
					if (GetCell(hWnd, index, &rect))
					{

						int v1 = rand() % 4;
						if (v1 == 0)
							Draw(hdc, rect.left + CELL_SIZE / 2 - 40, rect.top + CELL_SIZE / 2 - 40, L"piolincorazon.png");
						if (v1 == 1)
							Draw(hdc, rect.left + CELL_SIZE / 2 - 40, rect.top + CELL_SIZE / 2 - 40, L"piolinkarate.png");
						if (v1 == 2)
							Draw(hdc, rect.left + CELL_SIZE / 2 - 40, rect.top + CELL_SIZE / 2 - 40, L"piolinssj.png");
						if (v1 == 3)
							Draw(hdc, rect.left + CELL_SIZE / 2 - 40, rect.top + CELL_SIZE / 2 - 40, L"piolinmamado.png");
						// int GetNumber(HWND hWnd, int x, int y)


					}
				}
			}
			for (unsigned short i = 0; i < 9; i++)
			{
				//verticales
				DrawLine(hdc, rc.left + CELL_SIZE * i, rc.top, rc.left + CELL_SIZE * i, rc.bottom);
				//horizontales
				DrawLine(hdc, rc.left, rc.top + CELL_SIZE * i, rc.right, rc.top + CELL_SIZE * i);
			}


		}
			EndPaint(hWnd, &ps);
		}
		break;

	case WM_DESTROY:
		DestroyIcon(hIcon1);
		DestroyIcon(hIcon2);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
	}

	void Draw(HDC hdc, int xpos, int ypos, Gdiplus::Bitmap bmp)
	{
		Gdiplus::Graphics gf(hdc);
		gf.DrawImage(&bmp, xpos, ypos);

	}
	// Message handler for about box.
	INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
	{
		UNREFERENCED_PARAMETER(lParam);
		switch (message)
		{
		case WM_INITDIALOG:
			return (INT_PTR)TRUE;

		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
			{
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
			break;
		}
		return (INT_PTR)FALSE;
	}
