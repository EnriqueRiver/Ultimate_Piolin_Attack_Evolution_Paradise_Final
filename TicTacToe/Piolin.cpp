#include "Piolin.h"

Piolin::Piolin()
{
	type = '0';
	visited = false;
	x = -1;
	y = -1;
}


void Piolin::SetPos(int _x, int _y)
{
	x = _x;
	y = _y;
}

int Piolin::GetX()
{
	return x;
}

int Piolin::GetY()
{
	return y;
}
bool Piolin::operator==(Piolin pio)
{
	if (type == pio.GetType())
		return true;
	else
		return false;
}

char Piolin::GetType()
{
	return type;	return 0;
}

void Piolin::SetType(char n_type)
{
	type = n_type;
}

bool Piolin::Visited()
{
	return visited;
}

void Piolin::SetVisited(bool state)
{
	visited = state;
}

void Piolin::operator>>(Piolin* gem)
{
	char tmp;
	tmp = type;
	SetType(gem->GetType());
	gem->SetType(tmp);
}

bool Piolin::Contiguous(Piolin gem)
{
	return 0;
}

void Piolin::GenerateNewType()
{
	int tmp = rand() % 4;

	switch (tmp)
	{
	case 0:
		type = 'r';
		break;
	case 1:
		type = 'v';
		break;
	case 2:
		type = 'a';
		break;
	case 3:
		type = 'b';
		break;
	default:
		type = '0';
		break;
	}
}
