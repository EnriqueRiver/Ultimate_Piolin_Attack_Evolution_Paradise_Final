#include "BoardPiolin.h"
#include <iostream>

BoardPiolin::BoardPiolin(){

	Piolines = vector<vector<Piolin>>(CellsLength, vector<Piolin>(CellsLength));

	for (int x = 0; x < CellsLength; x++) {
		for (int y = 0; y < CellsLength; y++) {

			GetPiolin(x, y)->SetPos(x, y);
		}
	}
	PiolinGenerator();
}

void BoardPiolin::PiolinGenerator(){

	for (int x = 0; x < CellsLength; x++) {
		for (int y = 0; y < CellsLength; y++) {

			GetPiolin(x, y)->GenerateNewType();
		}
	}
}

BOOL BoardPiolin::PiolinBoardRect(HWND hWnd, RECT* pRect){

	RECT rc;
	if (GetClientRect(hWnd, &rc)){

		int width = rc.right - rc.left;
		int height = rc.bottom - rc.top;

		pRect->left = (width - CellSize * CellsLength) / 2;
		pRect->top = (height - CellSize * CellsLength) / 2;

		pRect->right = pRect->left + CellSize * CellsLength;
		pRect->bottom = pRect->top + CellSize * CellsLength;

		return true;
	}

	SetRectEmpty(pRect);
	return false;
}
void BoardPiolin::DrawPiolinLine(HDC hdc, int x1, int y1, int x2, int y2){

	MoveToEx(hdc, x1, y1, nullptr);
	LineTo(hdc, x2, y2);
}
void BoardPiolin::DefinePiolin(RECT* rc, Gdiplus::Graphics* graphics,HDC hdc){

	Gdiplus::Bitmap bmp2(L"Restart.png");
	graphics->DrawImage(&bmp2, 50, 50, 100, 100);
	Gdiplus::Bitmap bmp3(L"Sin título-1.png");
	graphics->DrawImage(&bmp3, 50, 150, 100, 100);
	if (level1 == true){
		Gdiplus::Bitmap level1(L"level1.png");
		graphics->DrawImage(&level1, 1200, 50, 100, 100);
	}
	if (level2 == true){
		Gdiplus::Bitmap level1(L"level2.png");
		graphics->DrawImage(&level1, 1200, 50, 100, 100);
	}
	if (level3 == true){
		Gdiplus::Bitmap level1(L"level3.png");
		graphics->DrawImage(&level1, 1200, 50, 100, 100);
	}
	if (score == 10){
		Gdiplus::Bitmap bmp4(L"10score.png");
		graphics->DrawImage(&bmp4, 50, 250, 100, 100);
	}
	if (score == 20){
		Gdiplus::Bitmap bmp4(L"20score.png");
		graphics->DrawImage(&bmp4, 50, 250, 100, 100);
	}
	if (score == 30){
		Gdiplus::Bitmap bmp4(L"30score.png");
		graphics->DrawImage(&bmp4, 50, 250, 100, 100);
	}
	if (score == 40){
		Gdiplus::Bitmap bmp4(L"40score.png");
		graphics->DrawImage(&bmp4, 50, 250, 100, 100);
	}
	if (score == 50){
		
		if (level1 == true){
			PiolinGenerator();
			score = 0;
			level2 = true;
			level1 = false;
		}
		if (level2 == true && score == 50){
			PiolinGenerator();
			score = 0;
			level3 = true;
			level2 = false;
		}
		if (level3 == true && score == 50){
			score = 0;
			level3 = false;
			Endgame = true;
		}
	}
	if (score == 0){

		Gdiplus::Bitmap bmp4(L"0score.png");
		graphics->DrawImage(&bmp4, 50, 250, 100, 100);
	}
	for (int x = 0; x < CellsLength; x++)
		for (int y = 0; y < CellsLength; y++){

			Piolin* pio = GetPiolin(x, y);
			switch (pio->GetType()){

			case '0':
				break;
			case 'r':{
				Gdiplus::Bitmap bmp0(L"piolin-corazon.jpg");
				graphics->DrawImage(&bmp0, (int)rc->left + CellSize * x, (int)rc->top + CellSize * y, 100, 100);
			}
			break;
			case 'v':{
				Gdiplus::Bitmap bmp0(L"piolinkarate.png");
				graphics->DrawImage(&bmp0, (int)rc->left + CellSize *x , (int)rc->top + CellSize *y, 100, 100);
			}
			break;
			case 'a':{
				Gdiplus::Bitmap bmp0(L"piolinmamado.png");
				graphics->DrawImage(&bmp0, (int)rc->left + CellSize * x, (int)rc->top + CellSize * y, 100, 100);
			}
			break;
			case 'b':{
				Gdiplus::Bitmap bmp0(L"piolinssj.png");
				graphics->DrawImage(&bmp0, (int)rc->left + CellSize * x, (int)rc->top + CellSize * y, 100, 100);
			}
			break;
			default:
				break;
			}
			if (Endgame == true){
				Gdiplus::Bitmap bmp1(L"Endgame.png");
				graphics->DrawImage(&bmp1, 0, 0, 1600, 800);
			}
			pio = 0;
			delete pio;
		}
}
void BoardPiolin::DrawBoardPiolin(HWND hWnd, HDC hdc, RECT* rc, Gdiplus::Graphics* graphics,bool escena){
	if (!escena) {
		Gdiplus::Bitmap bmp1(L"PiolinMenu.png");
		graphics->DrawImage(&bmp1, 0, 0, 1600, 800);
	}
	else{

		if (PiolinBoardRect(hWnd, rc)){
			FillRect(hdc, rc, (HBRUSH)GetStockObject(WHITE_BRUSH));
			Rectangle(hdc, rc->left, rc->top, rc->right, rc->bottom);
		}

		for (unsigned short i = 0; i < CellsLength + 1; i++){
			DrawPiolinLine(hdc, rc->left + CellSize * i, rc->top, rc->left + CellSize * i, rc->bottom);
			DrawPiolinLine(hdc, rc->left, rc->top + CellSize * i, rc->right, rc->top + CellSize * i);
		}
		DefinePiolin(rc, graphics, hdc);
	}
}

int BoardPiolin::GetNumPiolin(HWND hWnd, int x, int y){
	POINT p = { x,y };
	RECT rc;
	if (PiolinBoardRect(hWnd, &rc)){
		if (PtInRect(&rc, p)){
			x = p.x - rc.left;
			y = p.y - rc.top;
			int col = x / CellSize;
			int row = y / CellSize;
			return col + row * CellsLength;
		}
		else{
			return -1;
		}
	}
	return -1;
}
BOOL BoardPiolin::GetCellPiolin(HWND hWnd, int index, RECT* pRect){
	
	RECT BoardPiolin;
	SetRectEmpty(pRect);

	if (index < 0 || index >(CellsLength * CellsLength) - 1)
		return false;
	if (PiolinBoardRect(hWnd, &BoardPiolin)){

		int y = index / CellsLength;
		int x = index % CellsLength;
		pRect->left = BoardPiolin.left + x * CellSize;
		pRect->top = BoardPiolin.top + y * CellSize;
		pRect->right = pRect->left + CellSize;
		pRect->bottom = pRect->top + CellSize;
		return true;
	}
}
int BoardPiolin::GetCellPiolinSize(){

	return CellSize;
}
int BoardPiolin::GetCellsPiolinLength(){

	return CellsLength;
}

Piolin* BoardPiolin::GetPiolin(int x, int y){

	return &Piolines[y][x];
}
list<Piolin*> BoardPiolin::GetPiolinPattern(int x, int y){

	list<Piolin*> tmp;
	PiolinBro(x, y, &tmp);
	OutOfRangePiolines();
	return tmp;
}

void BoardPiolin::MovePiolin(vector<int>* moves){

	int click1 = moves->at(0);
	int click2 = moves->at(1);
	moves->clear();

	if (click1 != click2){

		int c1X = click1 % CellsLength;
		int c1Y = click1 / CellsLength;

		int c2X = click2 % CellsLength;
		int c2Y = click2 / CellsLength;

		Piolin* pio1 = GetPiolin(c1X, c1Y);
		Piolin* pio2 = GetPiolin(c2X, c2Y);
		char n = pio1->GetType();
		char m = pio2->GetType();

		//Si estan contiguas
		if(c1X <= c2X + 1)
			if(c1X >= c2X - 1)
				if(c1Y <= c2Y + 1)
					if (c1Y >= c2Y - 1) {
						pio1->SetType(m);
						pio2->SetType(n);
						DestructPatternsPiolin(c1X, c1Y, pio1, pio2);

					}
		else{
			pio1->SetType(n);
			pio2->SetType(m);
		}
		pio1 = 0;
		pio2 = 0;
		delete pio1;
		delete pio2;
	}
}
void BoardPiolin::PiolinBro(int x, int y, list<Piolin*>* partners){

	if (x >= 0 && y >= 0)
		if (x < CellsLength && y < CellsLength){

			try{

				Piolin* pio = GetPiolin(x, y);
				if (!pio->Visited()){

					pio->SetVisited(true);
					partners->push_back(pio);

					if (x + 1 < CellsLength){

						if (*pio == *GetPiolin(x + 1, y)){

							PiolinBro(x + 1, y, partners);
						}
					}
					if (y + 1 < CellsLength){

						if (*pio == *GetPiolin(x, y + 1)){

							PiolinBro(x, y + 1, partners);
						}
					}
					if (x - 1 >= 0){

						if (*pio == *GetPiolin(x - 1, y)){

							PiolinBro(x - 1, y, partners);
						}
					}
					if (y - 1 >= 0){

						if (*pio == *GetPiolin(x, y - 1)){

							PiolinBro(x, y - 1, partners);
						}
					}
				}
				pio = 0;
				delete pio;
			}
			catch (std::exception& e){

				e.what();
			}
		}

}
void BoardPiolin::DestructPatternsPiolin(int x, int y, Piolin* pio1, Piolin* pio2){

	char n = pio1->GetType();
	char m = pio2->GetType();
	Piolin* piolin1 = GetPiolin(x, y);
	Piolin* piolin2 = GetPiolin(x, y);

	pio1->SetType(n);
	pio2->SetType(m);

	list<Piolin*> piolines = GetPiolinPattern(x, y);
	if (piolines.size() >= 3){

		score += 10;
		for (Piolin* piolin : piolines){
			
			piolin->SetType('0');
		}
		for (Piolin* piolin : piolines){

			if (piolin->GetType() == '0')
			{
				//ConvertirPiolines(x, y);
				RearrangePiolines(piolin->GetX(), piolin->GetY(), EmptyPiolines(piolin->GetX(), piolin->GetY()));
			}
		}
	}
	else{

		pio1->SetType(m);
		pio2->SetType(n);
	}
}
int BoardPiolin::EmptyPiolines(int x, int y){

	if (y >= 0 && y < CellsLength){

		if (GetPiolin(x, y)->GetType() == '0')
			return 1 + EmptyPiolines(x, y - 1);
	}
	return 0;
}
void BoardPiolin::RearrangePiolines(int x, int y, int i){

	if (y < CellsLength && x < CellsLength)
		if (y >= 0 && x >= 0){

			Piolin* pio1;
			Piolin* pio2;

			for (int a = 0; a < i; a++){

				if ((y - a - i) >= 0){

					pio1 = GetPiolin(x, y - a);
					pio2 = GetPiolin(x, y - a - i);

					*pio2 >> pio1;

					pio2->GenerateNewType();
				}
				else{

					pio1 = GetPiolin(x, y - a);
					pio1->GenerateNewType();
				}

			}
			pio1 = 0;
			pio2 = 0;

			delete pio1;
			delete pio2;
		}
}
void BoardPiolin::OutOfRangePiolines(){

	for (int x = 0; x < CellsLength; x++)
		for (int y = 0; y < CellsLength; y++)
			GetPiolin(x, y)->SetVisited(false);
}









