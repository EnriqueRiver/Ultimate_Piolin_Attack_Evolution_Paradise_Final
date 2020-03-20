#pragma once
#include <Windows.h>
#include "framework.h"
#include "Piolin.h"
#include <list>
#include <vector>
#include <gdiplus.h>

using namespace std;

class BoardPiolin
{
private:
	short int CellSize = 100;
	short int CellsLength = 8;
	vector<vector<Piolin>> Piolines;
	bool level1 = true;
	bool level2, level3 = false;
	
public:
	bool Endgame;
	int score;

	BoardPiolin();

	void PiolinGenerator();

	BOOL PiolinBoardRect(HWND hWnd, RECT* pRect);
	void DrawPiolinLine(HDC hdc, int x1, int y1, int x2, int y2);
	void DrawBoardPiolin(HWND hWnd, HDC hdc, RECT* rc, Gdiplus::Graphics* graphics, bool escena);
	void DefinePiolin(RECT* rc, Gdiplus::Graphics* graphics, HDC hdc);

	int GetNumPiolin(HWND hWnd, int x, int y);
	BOOL GetCellPiolin(HWND hWnd, int index, RECT* pRect);
	int GetCellPiolinSize();
	int GetCellsPiolinLength();

	Piolin* GetPiolin(int x, int y);
	list<Piolin*> GetPiolinPattern(int x, int y);

	void MovePiolin(vector<int>* moves);
	void PiolinBro(int x, int y, list<Piolin*>* list);
	void DestructPatternsPiolin(int, int, Piolin*, Piolin*);
	int EmptyPiolines(int x, int y);
	void RearrangePiolines(int x, int y, int i);
	void OutOfRangePiolines();

};

