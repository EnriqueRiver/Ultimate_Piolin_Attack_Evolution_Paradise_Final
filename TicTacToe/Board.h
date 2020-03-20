#pragma once
#include <Windows.h>
#include "framework.h"
#include "Piolin.h"
#include <list>
#include <vector>
#include <gdiplus.h>


using std::list; using std::vector;

class Board
{
private:
	const int CELL_SIZE = 100;
	const int CELL_COUNT = 8;
	vector<vector<Piolin>> Piolines;

public:
	Board();

	void Draw(HDC hdc, int xpos, int ypos, Gdiplus::Bitmap bmp);

	void DrawBoard(HWND hWnd, HDC hdc, RECT* rc, Gdiplus::Graphics* graphics);

	BOOL GetGameBoardRect(HWND hWnd, RECT* pRect);

	void DrawLine(HDC hdc, int x1, int y1, int x2, int y2);

	BOOL GetCell(HWND hWnd, int index, RECT* pRect);

	int GetNumber(HWND hWnd, int x, int y);

	int GetCellSize();

	int GetCellCount();

	Piolin* GetPiolinAt(int x, int y);

	list<Piolin*> GetPartnerPiolin(int x, int y);

	void LookForPartners(int x, int y, list<Piolin*>* list);

	void MovePiolines(int x, int y, int i);

	int EmptyNeighboards(int x, int y);

	void GenerateNewLevel();

	void PlayerMove(vector<int>* moves);

private:
	void DrawPiolinColor(RECT* rc, Gdiplus::Graphics* graphics,HDC hdc);

	void DestoyPiolin(int, int, Piolin*, Piolin*);

	void UnSeePiolines();
};

