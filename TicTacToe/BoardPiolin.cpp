#include "BoardPiolin.h"
#include <iostream>

//Constructor, crea un array dinamico de vector<piolin> 
BoardPiolin::BoardPiolin(){

	Piolines = vector<vector<Piolin>>(CellsLength, vector<Piolin>(CellsLength));

	for (int x = 0; x < CellsLength; x++) {
		for (int y = 0; y < CellsLength; y++) {

			GetPiolin(x, y)->SetPos(x, y);
		}
	}
	PiolinGenerator();
}

//Generador de tipos genera el tipo de piolin al azar
void BoardPiolin::PiolinGenerator(){

	for (int x = 0; x < CellsLength; x++) {
		for (int y = 0; y < CellsLength; y++) {

			GetPiolin(x, y)->GenerateNewType();
		}
	}
}

//Dibuja el rectangulo de fondo.
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

//Dibujan las lineas que dividen el rectangulo y crean el tablero
void BoardPiolin::DrawPiolinLine(HDC hdc, int x1, int y1, int x2, int y2){

	MoveToEx(hdc, x1, y1, nullptr);
	LineTo(hdc, x2, y2);
}

//Define todos los sprites de piolin y sprites tambien los maneja
void BoardPiolin::DefinePiolin(RECT* rc, Gdiplus::Graphics* graphics,HDC hdc){

	try {

		Gdiplus::Bitmap bmp2(L"Restart.png");
		graphics->DrawImage(&bmp2, 50, 50, 100, 100);
		Gdiplus::Bitmap bmp3(L"Sin t�tulo-1.png");
		graphics->DrawImage(&bmp3, 50, 150, 100, 100);
		if (level1 == true) {
			Gdiplus::Bitmap level1(L"level1.png");
			graphics->DrawImage(&level1, 1200, 50, 100, 100);
		}
		if (level2 == true) {
			Gdiplus::Bitmap level1(L"level2.png");
			graphics->DrawImage(&level1, 1200, 50, 100, 100);
		}
		if (level3 == true) {
			Gdiplus::Bitmap level1(L"level3.png");
			graphics->DrawImage(&level1, 1200, 50, 100, 100);
		}
		if (score == 10) {
			Gdiplus::Bitmap bmp4(L"10score.png");
			graphics->DrawImage(&bmp4, 50, 250, 100, 100);
		}
		if (score == 20) {
			Gdiplus::Bitmap bmp4(L"20score.png");
			graphics->DrawImage(&bmp4, 50, 250, 100, 100);
		}
		if (score == 30) {
			Gdiplus::Bitmap bmp4(L"30score.png");
			graphics->DrawImage(&bmp4, 50, 250, 100, 100);
		}
		if (score == 40) {
			Gdiplus::Bitmap bmp4(L"40score.png");
			graphics->DrawImage(&bmp4, 50, 250, 100, 100);
		}
	}
	catch (...)
	{
		return;
	}
	try {
		if (score == 50) {

			if (level1 == true) {
				PiolinGenerator();
				score = 0;
				level2 = true;
				level1 = false;
			}
			if (level2 == true && score == 50) {
				PiolinGenerator();
				score = 0;
				level3 = true;
				level2 = false;
			}
			if (level3 == true && score == 50) {
				score = 0;
				level3 = false;
				Endgame = true;
			}
		}
	}
		catch (...)
		{
			return;
		}
		if (score == 0) {

			Gdiplus::Bitmap bmp4(L"0score.png");
			graphics->DrawImage(&bmp4, 50, 250, 100, 100);
		}
	

	for (int x = 0; x < CellsLength; x++)
		for (int y = 0; y < CellsLength; y++){

			Piolin* pio = GetPiolin(x, y);
			switch (pio->GetType()){

			case 0:
				break;
			case 1:{
				Gdiplus::Bitmap bmp0(L"piolin-corazon.jpg");
				graphics->DrawImage(&bmp0, rc->left + CellSize * x, rc->top + CellSize * y, 100, 100);
			}
			break;
			case 2:{
				Gdiplus::Bitmap bmp0(L"piolinkarate.png");
				graphics->DrawImage(&bmp0, rc->left + CellSize *x , rc->top + CellSize *y, 100, 100);
			}
			break;
			case 3:{
				Gdiplus::Bitmap bmp0(L"piolinmamado.png");
				graphics->DrawImage(&bmp0, rc->left + CellSize * x, rc->top + CellSize * y, 100, 100);
			}
			break;
			case 4:{
				Gdiplus::Bitmap bmp0(L"piolinssj.png");
				graphics->DrawImage(&bmp0, rc->left + CellSize * x, rc->top + CellSize * y, 100, 100);
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
//Dibuja menu principal o dibuja los piolines dentro de las casillas
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
//Retorna el numero (index) del piolin Super seleccionado
int BoardPiolin::GetNumPiolin(HWND hWnd, int x, int y){
	POINT p = { x,y };
	RECT rc;
	if (PiolinBoardRect(hWnd, &rc)){
		if (PtInRect(&rc, p)){
			x = p.x - rc.left;
			y = p.y - rc.top;
			int col = x / CellSize;
			int row = y / CellSize;
			int index = col + row * CellsLength;
			return index;
		}
		else{
			return -1;
		}
	}
	return -1;
}

//Retorna el tamano de celda 100x100
int BoardPiolin::GetCellPiolinSize(){

	return CellSize;
}

//Retorna el tamano del tablero 8x8
int BoardPiolin::GetCellsPiolinLength(){

	return CellsLength;
}
//Retorna un vector dinamico con Piolin, con sus coordenadas, retorna el objeto
Piolin* BoardPiolin::GetPiolin(int x, int y){

	return &Piolines[y][x];
}

//MEte todos los pioles del mismo tipo adyacentes a una misma lista, regresa la lista 
list<Piolin*> BoardPiolin::GetPiolinPattern(int x, int y){

	list<Piolin*> tmp;
	PiolinBro(x, y, &tmp);
	OutOfRangePiolines();
	return tmp;
}

//Mueve el piolin de acuerdo a los clicks del mouse,  regresa los piolines en esas coordenadas, toma sus tipos y los cambia, tambein llama a la funcion que destruye
//Si el cambio lo se realice se regresan a su valor original
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

//Checa los piolines vacios por medio de recursividad, se forman las cadenas de piolines PARA SER ELIMINADOS
void BoardPiolin::PiolinBro(int x, int y, list<Piolin*>* partners){

	if (x >= 0 && y >= 0)
		if (x < CellsLength && y < CellsLength){

			try{

				Piolin* pio = GetPiolin(x, y);
				if (!pio->GetVisited()){

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
//toma los tipos de piolines los mete a una lista y si es mayor su tamano a 3 cambia su tipo a 0 para despues eliminarlo, sino regresan a su posicion original
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
			
			piolin->SetType(0);
		}
		for (Piolin* piolin : piolines){

			if (piolin->GetType() == 0)
			{

				RearrangePiolines(piolin->GetX(), piolin->GetY(), EmptyPiolines(piolin->GetX(), piolin->GetY()));
			}
		}
	}
	else{

		pio1->SetType(m);
		pio2->SetType(n);
	}
}
//Regresa las casillas 0, dejandonos saber gemas van a ser cambiadas
int BoardPiolin::EmptyPiolines(int x, int y){

	if (y >= 0 && y < CellsLength){

		if (GetPiolin(x, y)->GetType() == 0)
			return 1 + EmptyPiolines(x, y - 1);
	}
	return 0;
}

//Reacomoda los piolines con tipos 0 para que obtengan un valor
void BoardPiolin::RearrangePiolines(int x, int y, int i){

	if (y < CellsLength && x < CellsLength)
		if (y >= 0 && x >= 0){

			Piolin* pio1;
			Piolin* pio2;

			for (int a = 0; a < i; a++){

				if ((y - a - i) >= 0){

					pio1 = GetPiolin(x, y - a);
					pio2 = GetPiolin(x, y - a - i);

					char n = pio1->GetType();
					char m = pio2->GetType();
					pio1->SetType(m);
					pio2->SetType(n);


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
//Cambia a los piolines a no visitados
void BoardPiolin::OutOfRangePiolines(){

	for (int x = 0; x < CellsLength; x++) {
		for (int y = 0; y < CellsLength; y++) {

			GetPiolin(x, y)->SetVisited(false);
		}
	}
}









