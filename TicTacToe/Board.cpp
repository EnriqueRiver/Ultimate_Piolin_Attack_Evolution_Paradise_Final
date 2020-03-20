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

void Board::DrawBoard(HWND hWnd, HDC hdc, RECT* rc, Gdiplus::Graphics* graphics,bool escena)
{
	if (!escena) {
		Gdiplus::Bitmap bmp1(L"PiolinMenu.png");
		graphics->DrawImage(&bmp1, 0, 0, 1600, 800);
	}
	else
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
		DrawPiolinColor(rc, graphics, hdc);
	}
}


void Board::DrawPiolinColor(RECT* rc, Gdiplus::Graphics* graphics,HDC hdc)
{
	Gdiplus::Bitmap bmp2(L"Restart.png");
	graphics->DrawImage(&bmp2, 50, 50, 100, 100);
	Gdiplus::Bitmap bmp3(L"Sin título-1.png");
	graphics->DrawImage(&bmp3, 50, 150, 100, 100);
	if (level1 == true)
	{
		Gdiplus::Bitmap level1(L"level1.png");
		graphics->DrawImage(&level1, 1200, 50, 100, 100);
	}
	if (level2 == true)
	{
		Gdiplus::Bitmap level1(L"level2.png");
		graphics->DrawImage(&level1, 1200, 50, 100, 100);
	}
	if (level3 == true)
	{
		Gdiplus::Bitmap level1(L"level3.png");
		graphics->DrawImage(&level1, 1200, 50, 100, 100);
	}
	if (score == 10)
	{
		Gdiplus::Bitmap bmp4(L"10score.png");
		graphics->DrawImage(&bmp4, 50, 250, 100, 100);
	}
	if (score == 20)
	{
		Gdiplus::Bitmap bmp4(L"20score.png");
		graphics->DrawImage(&bmp4, 50, 250, 100, 100);
	}
	if (score == 30)
	{
		Gdiplus::Bitmap bmp4(L"30score.png");
		graphics->DrawImage(&bmp4, 50, 250, 100, 100);
	}
	if (score == 40)
	{
		Gdiplus::Bitmap bmp4(L"40score.png");
		graphics->DrawImage(&bmp4, 50, 250, 100, 100);
	}
	if (score == 50)
	{
		
		if (level1 == true)
		{
			score = 0;
			level2 = true;
			level1 = false;
		}
		if (level2 == true && score == 50)
		{
			score = 0;
			level3 = true;
			level2 = false;
		}
		if (level3 == true && score == 50)
		{
			score = 0;
			level3 = false;
			Endgame = true;
		}
	}
	if (Endgame == true)
	{
		Gdiplus::Bitmap bmp1(L"Endgame.png");
		graphics->DrawImage(&bmp1, 0, 0, 1600, 800);
	}
	if (score == 0)
	{
		Gdiplus::Bitmap bmp4(L"0score.png");
		graphics->DrawImage(&bmp4, 50, 250, 100, 100);
	}
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
				Gdiplus::Bitmap bmp0(L"piolin-corazon.jpg");
				graphics->DrawImage(&bmp0, (int)rc->left + CELL_SIZE * x, (int)rc->top + CELL_SIZE * y, 100, 100);
			}
			break;
			case 'v':
			{
				Gdiplus::Bitmap bmp0(L"piolinkarate.png");
				graphics->DrawImage(&bmp0, (int)rc->left + CELL_SIZE *x , (int)rc->top + CELL_SIZE *y, 100, 100);
			}
			break;
			case 'a':
			{
				Gdiplus::Bitmap bmp0(L"piolinmamado.png");
				graphics->DrawImage(&bmp0, (int)rc->left + CELL_SIZE * x, (int)rc->top + CELL_SIZE * y, 100, 100);
			}
			break;
			case 'b':
			{
				Gdiplus::Bitmap bmp0(L"piolinssj.png");
				graphics->DrawImage(&bmp0, (int)rc->left + CELL_SIZE * x, (int)rc->top + CELL_SIZE * y, 100, 100);
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

//Cuenta la cantidad de Gems vacias hay sobre una posición
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

//Lógica de un turno
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
		char n = pio1->GetType();
		char m = pio2->GetType();

		//Si estan contiguas
		if(c1X <= c2X + 1)
			if(c1X >= c2X - 1)
				if(c1Y <= c2Y + 1)
					if (c1Y >= c2Y - 1) {
						pio1->SetType(m);
						pio2->SetType(n);
						DestoyPiolin(c1X, c1Y, pio1, pio2);

					}
		else
		{
			pio1->SetType(n);
			pio2->SetType(m);
		}
		pio1 = 0;
		pio2 = 0;
		delete pio1;
		delete pio2;
	}


}

void Board::ConvertirPiolines(int x, int y, list<Piolin*> list)
{
	if (x >= 0 && y >= 0)
		if (x < CELL_COUNT && y < CELL_COUNT)
		{
			try {
				if (y - 1 != 0) {
					//for (Piolin* piolin : list)
					//{
					//	piolin->SetType(GetPiolinAt(x, y - 1)->GetType());
					//}
					Piolin* pio = GetPiolinAt(x, y);
					char piolintype;
					piolintype = GetPiolinAt(x, y - 1)->GetType();
					pio->SetType(piolintype);
					ConvertirPiolines(x, y - 1, list);

				}
			}
			catch (std::exception& e)
			{
				e.what();
			}
		}
}

void Board::DestoyPiolin(int x, int y, Piolin* pio1, Piolin* pio2)
{
	//Swap;
	char n = pio1->GetType();
	char m = pio2->GetType();
	Piolin* piolin1 = GetPiolinAt(x, y);
	Piolin* piolin2 = GetPiolinAt(x, y);
	//if (pio1->GetType() != piolin1->GetType())
	//	if (pio2->GetType() != piolin2->GetType())
			//DestoyPiolin(x, y, pio1, pio2);
	pio1->SetType(n);
	pio2->SetType(m);

	list<Piolin*> piolines = GetPartnerPiolin(x, y);
	if (piolines.size() >= 3)
	{
		score += 10;
		//Las marca como gems vacias - "Las elimina"
		for (Piolin* piolin : piolines)
		{
			
			piolin->SetType('0');
		}

		for (Piolin* piolin : piolines)
		{
			if (piolin->GetType() == '0')
			{
				//ConvertirPiolines(x, y);
				MovePiolines(piolin->GetX(), piolin->GetY(), EmptyNeighboards(piolin->GetX(), piolin->GetY()));
			}
		}
	}
	else
	{

		pio1->SetType(m);
		pio2->SetType(n);
	}
}

void Board::UnSeePiolines()
{
	for (int x = 0; x < CELL_COUNT; x++)
		for (int y = 0; y < CELL_COUNT; y++)
			GetPiolinAt(x, y)->SetVisited(false);
}