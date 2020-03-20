#pragma once
#include <iostream>
#include <ctime>
class Piolin
{
private:
	int x, y;
	int type;
	bool visited;

public:

	Piolin();
	void SetPos(int xPos, int yPos);
	void SetType(int caseType);
	void SetVisited(bool);
	int GetX();
	int GetY();
	char GetType();
	bool GetVisited();
	void GenerateNewType();
	bool operator==(Piolin pio);
};

