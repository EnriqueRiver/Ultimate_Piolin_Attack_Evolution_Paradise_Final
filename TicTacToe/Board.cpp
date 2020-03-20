#include "Board.h"
#include <iostream>

Board::Board()
{
	Piolines = vector<vector<Piolin>>(CELL_COUNT, vector<Piolin>(CELL_COUNT));

	for (int x = 0; x < CELL_COUNT; x++)
		for (int y = 0; y < CELL_COUNT; y++)
			GetPiolinAt(x, y)->SetPos(x, y);

	GenerateNewLevel();
}

void Board::DrawBoard(HWND hWnd, HDC hdc, RECT* rc, Gdiplus::Graphics* graphics)
{

	if (GetGameBoardRect(hWnd, rc))
	{
		FillRect(hdc, rc, (HBRUSH)GetStockObject(WHITE_BRUSH));
		Rectangle(hdc, rc->left, rc->top, rc->right, rc->bottom);
	}

	for (unsigned short i = 0; i < CELL_COUNT + 1; i++)
	{
		//verticales
		DrawLine(hdc, rc->left + CELL_SIZE * i, rc->top, rc->left + CELL_SIZE * i, rc->bottom);

		//horizontales
		DrawLine(hdc, rc->left, rc->top + CELL_SIZE * i, rc->right, rc->top + CELL_SIZE * i);
	}
	DrawPiolinColor(rc, graphics);
}

void Board::DrawPiolinColor(RECT* rc, Gdiplus::Graphics* graphics)
{
	for (int x = 0; x < CELL_COUNT; x++)
		for (int y = 0; y < CELL_COUNT; y++)
		{
			Piolin* pio = GetPiolinAt(x, y);
			switch (pio->GetType())
			{
			case '0':
				break;
			case 'r':
			{
				Gdiplus::Bitmap bmp0(L"a.png");
				graphics->DrawImage(&bmp0, (int)rc->left + 15 + CELL_SIZE * x, (int)rc->top + 15 + CELL_SIZE * y, 10, 10);
			}
			break;
			case 'v':
			{
				Gdiplus::Bitmap bmp0(L"b.png");
				graphics->DrawImage(&bmp0, (int)rc->left + 100 + CELL_SIZE * x, (int)rc->top + 15 + CELL_SIZE * y, 10, 10);

			}
			break;
			case 'a':
			{
				Gdiplus::Bitmap bmp0(L"c.png");
				graphics->DrawImage(&bmp0, (int)rc->left + 15 + CELL_SIZE * x, (int)rc->top + 15 + CELL_SIZE * y, 10, 10);
			}
			break;
			case 'b':
			{
				Gdiplus::Bitmap bmp0(L"d.png");
				graphics->DrawImage(&bmp0, (int)rc->left + 15 + CELL_SIZE * x, (int)rc->top + 15 + CELL_SIZE * y, 10, 10);
			}
			break;
			default:
				break;
			}

			pio = 0;
			delete pio;
		}
}

BOOL Board::GetGameBoardRect(HWND hWnd, RECT* pRect)
{
	RECT rc;
	if (GetClientRect(hWnd, &rc))
	{
		int width = rc.right - rc.left;
		int height = rc.bottom - rc.top;

		pRect->left = (width - CELL_SIZE * CELL_COUNT) / 2;
		pRect->top = (height - CELL_SIZE * CELL_COUNT) / 2;

		pRect->right = pRect->left + CELL_SIZE * CELL_COUNT;
		pRect->bottom = pRect->top + CELL_SIZE * CELL_COUNT;

		return true;
	}

	SetRectEmpty(pRect);
	return false;
}

void Board::DrawLine(HDC hdc, int x1, int y1, int x2, int y2)
{
	MoveToEx(hdc, x1, y1, nullptr);
	LineTo(hdc, x2, y2);
}

int Board::GetNumber(HWND hWnd, int x, int y)
{
	POINT p = { x,y };
	RECT rc;
	if (GetGameBoardRect(hWnd, &rc))
	{
		if (PtInRect(&rc, p))
		{
			x = p.x - rc.left;
			y = p.y - rc.top;
			int col = x / CELL_SIZE;
			int row = y / CELL_SIZE;
			return col + row * CELL_COUNT;
		}
		else
		{
			return -1;
		}
	}
	return -1;
}

BOOL Board::GetCell(HWND hWnd, int index, RECT* pRect)
{
	RECT board;
	SetRectEmpty(pRect);
	if (index < 0 || index >(CELL_COUNT * CELL_COUNT) - 1)
		return false;
	if (GetGameBoardRect(hWnd, &board))
	{
		int y = index / CELL_COUNT;
		int x = index % CELL_COUNT;
		pRect->left = board.left + x * CELL_SIZE;
		pRect->top = board.top + y * CELL_SIZE;
		pRect->right = pRect->left + CELL_SIZE;
		pRect->bottom = pRect->top + CELL_SIZE;
		return true;
	}
}

int Board::GetCellSize()
{
	return CELL_SIZE;
}

int Board::GetCellCount()
{
	return CELL_COUNT;
}

Piolin* Board::GetPiolinAt(int x, int y)
{
	return &Piolines[y][x];
}

list<Piolin*> Board::GetPartnerPiolin(int x, int y)
{
	list<Piolin*> tmp;
	LookForPartners(x, y, &tmp);
	UnSeePiolines();
	return tmp;
}

//Busca todos los vecinos del mismo tipo
void Board::LookForPartners(int x, int y, list<Piolin*>* partners)
{
	if (x >= 0 && y >= 0)
		if (x < CELL_COUNT && y < CELL_COUNT)
		{
			try
			{
				Piolin* pio = GetPiolinAt(x, y);
				if (!pio->Visited())
				{
					pio->SetVisited(true);
					partners->push_back(pio);
					if (x + 1 < CELL_COUNT)
					{
						if (*pio == *GetPiolinAt(x + 1, y))
						{
							LookForPartners(x + 1, y, partners);
						}
					}
					if (y + 1 < CELL_COUNT)
					{
						if (*pio == *GetPiolinAt(x, y + 1))
						{
							LookForPartners(x, y + 1, partners);
						}
					}
					if (x - 1 >= 0)
					{
						if (*pio == *GetPiolinAt(x - 1, y))
						{
							LookForPartners(x - 1, y, partners);
						}
					}
					if (y - 1 >= 0)
					{
						if (*pio == *GetPiolinAt(x, y - 1))
						{
							LookForPartners(x, y - 1, partners);
						}
					}
				}
				pio = 0;
				delete pio;
			}
			catch (std::exception& e)
			{
				e.what();
			}

		}

}

//Recorre Todas Gemas un espacio hacia abajo en una columna
// param i es la cantidad de espacios que lo vamos a mover
void Board::MovePiolines(int x, int y, int i)
{
	if (y < CELL_COUNT && x < CELL_COUNT)
		if (y >= 0 && x >= 0)
		{
			Piolin* pio1;
			Piolin* pio2;

			for (int a = 0; a < i; a++)
			{
				if ((y - a - i) >= 0)
				{
					pio1 = GetPiolinAt(x, y - a);
					pio2 = GetPiolinAt(x, y - a - i);

					*pio2 >> pio1;

					pio2->GenerateNewType();
				}
				else
				{
					pio1 = GetPiolinAt(x, y - a);
					pio1->GenerateNewType();
				}

			}
			pio1 = 0;
			pio2 = 0;

			delete pio1;
			delete pio2;
		}
}

//Cuenta la cantidad de Gems vacias hay sobre una posici�n
int Board::EmptyNeighboards(int x, int y)
{
	if (y >= 0 && y < CELL_COUNT)
	{
		if (GetPiolinAt(x, y)->GetType() == '0')
			return 1 + EmptyNeighboards(x, y - 1);
	}

	return 0;
}

void Board::GenerateNewLevel()
{
	for (int x = 0; x < CELL_COUNT; x++)
		for (int y = 0; y < CELL_COUNT; y++)
		{
			GetPiolinAt(x, y)->GenerateNewType();
		}
}

//L�gica de un turno
void Board::PlayerMove(vector<int>* moves)
{
	int click1 = moves->at(0);
	int click2 = moves->at(1);
	moves->clear();

	if (click1 != click2)
	{
		int c1X = click1 % CELL_COUNT;
		int c1Y = click1 / CELL_COUNT;

		int c2X = click2 % CELL_COUNT;
		int c2Y = click2 / CELL_COUNT;

		Piolin* pio1 = GetPiolinAt(c1X, c1Y);
		Piolin* pio2 = GetPiolinAt(c2X, c2Y);

		//Si estan contiguas
		{
			DestoyPiolin(c1X, c1Y, pio1, pio2);
			DestoyPiolin(c2X, c2Y, pio1, pio2);

		}

		pio1 = 0;
		pio2 = 0;
		delete pio1;
		delete pio2;
	}


}

void Board::DestoyPiolin(int x, int y, Piolin* pio1, Piolin* pio2)
{
	//Swap;
	*pio1 >> pio2;


	list<Piolin*> piolines = GetPartnerPiolin(x, y);
	if (piolines.size() >= 3)
	{
		//Las marca como gems vacias - "Las elimina"
		for (Piolin* piolin : piolines)
		{
			piolin->SetType('0');
		}

		for (Piolin* piolin : piolines)
		{
			if (piolin->GetType() == '0')
			{
				MovePiolines(piolin->GetX(), piolin->GetY(), EmptyNeighboards(piolin->GetX(), piolin->GetY()));
			}
		}


	}
	else
	{
		*pio1 >> pio2;
	}
}

void Board::UnSeePiolines()
{
	for (int x = 0; x < CELL_COUNT; x++)
		for (int y = 0; y < CELL_COUNT; y++)
			GetPiolinAt(x, y)->SetVisited(false);
}