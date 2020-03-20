// TicTacToe.cpp : Defines the entry point for the application.
//
#include <Windows.h>
#include "framework.h"
#include "TicTacToe.h"
#include "windowsx.h"
#include <gdiplus.h>
#include "Board.h"
#include <vector>


#define MAX_LOADSTRING 100
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
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);

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
	wcex.hbrBackground = (HBRUSH)(GetStockObject(GRAY_BRUSH));
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
	hInst = hInstance; // Store instance handle in our global variable
	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
	//if (hMenuWnd)
	//{
	//	hWnd = false;
	//}
	if (!hWnd)
	{
		return FALSE;
	}
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//const int CELL_SIZE = 100;
//
HICON hIcon5;
bool paint = false;
bool restart = false;
HWND button;


Board gameB;
vector<int> moves;

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
	


	}
					break;
	case WM_LBUTTONDOWN: {
		short xPos = GET_X_LPARAM(lParam);
		short yPos = GET_Y_LPARAM(lParam);
		int index = gameB.GetNumber(hWnd, xPos, yPos);
		HDC hdc = GetDC(hWnd);
		if (hdc != NULL)
		{
			WCHAR temp[100];
			wsprintf(temp, L"[%d]", index);
			TextOut(hdc, xPos, yPos, temp, lstrlen(temp));
			if (paint == false && index == -1)
			{
				gameB.GenerateNewLevel();
				paint = true;


			}
			if (paint == true)
			{
				if (index==-1)
				{
					
				}
			}
			if (index != -1)
			{
				moves.push_back(index);
				if (moves.size() >= 2)
				{
					gameB.PlayerMove(&moves);

				}
			}

		}
		break;
	}
	
	case WM_GETMINMAXINFO:
	{
		MINMAXINFO* pMinMax = (MINMAXINFO*)lParam;
		if (pMinMax != nullptr) {
			pMinMax->ptMinTrackSize.x = gameB.GetCellSize() * 5;
			pMinMax->ptMinTrackSize.y = gameB.GetCellSize() * 5;
		}


	}
	break;
	case WM_PAINT:
	{

		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		RECT rc;
		Gdiplus::Graphics gf(hdc);
<<<<<<< Updated upstream

=======
		gameB.DrawBoard(hWnd, hdc, &rc, &gf, true);
		if (gameB.Endgame == true)
		{
			
			gameB.DrawBoard(hWnd, hdc, &rc, &gf, true);
		}
		if (paint == false && gameB.Endgame == false)
>>>>>>> Stashed changes
		gameB.DrawBoard(hWnd, hdc, &rc, &gf, false);

		if (paint == true)
		{
			
			DestroyIcon(hIcon5);
			// TODO: Add any drawing code that uses hdc here...
			//if (GetGameBoardRect(hWnd, &rc))
			//{
			//	FillRect(hdc, &rc, (HBRUSH)GetStockObject(WHITE_BRUSH));
			//	Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
			//}
			int index = 0;
			if (hdc != NULL)
			{
				WCHAR temp[100];
				wsprintf(temp, L"[%d]", index);
				for (index; index < 64; index++)
				{
					RECT rect;
					//if (GetCell(hWnd, index, &rect))
					//{

					//	int v1 = rand() % 4;
					//	if (v1 == 0)
					//		Draw(hdc, rect.left + CELL_SIZE / 2 - 40, rect.top + CELL_SIZE / 2 - 40, L"piolincorazon.png");
					//	if (v1 == 1)
					//		Draw(hdc, rect.left + CELL_SIZE / 2 - 40, rect.top + CELL_SIZE / 2 - 40, L"piolinkarate.png");
					//	if (v1 == 2)
					//		Draw(hdc, rect.left + CELL_SIZE / 2 - 40, rect.top + CELL_SIZE / 2 - 40, L"piolinssj.png");
					//	if (v1 == 3)
					//		Draw(hdc, rect.left + CELL_SIZE / 2 - 40, rect.top + CELL_SIZE / 2 - 40, L"piolinmamado.png");
					//	// int GetNumber(HWND hWnd, int x, int y)


					//}
				}
			}
			//for (unsigned short i = 0; i < 9; i++)
			//{
			//	//verticales
			//	DrawLine(hdc, rc.left + CELL_SIZE * i, rc.top, rc.left + CELL_SIZE * i, rc.bottom);
			//	//horizontales
			//	DrawLine(hdc, rc.left, rc.top + CELL_SIZE * i, rc.right, rc.top + CELL_SIZE * i);
			//}


		}
		EndPaint(hWnd, &ps);
	}
	break;

	case WM_DESTROY:
		//DestroyIcon(hIcon1);
		//DestroyIcon(hIcon2);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	 return 0;
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
