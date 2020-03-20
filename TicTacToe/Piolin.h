#pragma once
#include <iostream>
#include <ctime>
class Piolin
{
private:
	int x, y;
	char type;
	bool visited;

public:

	Piolin();

	bool operator==(Piolin gem);

	void SetPos(int, int);

	int GetX();

	int GetY();

	char GetType();

	void SetType(char);

	bool Visited();

	void SetVisited(bool);

	//Swap type de dos gemas
	void operator>>(Piolin* gem);

	bool Contiguous(Piolin gem);

	void GenerateNewType();

};

