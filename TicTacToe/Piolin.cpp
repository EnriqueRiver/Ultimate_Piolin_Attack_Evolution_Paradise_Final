#include "Piolin.h"

Piolin::Piolin(){

	x = -1;
	y = -1;
	type = 0;
	visited = false;
}
void Piolin::SetPos(int xPos, int yPos){

	x = xPos;
	y = yPos;
}
void Piolin::SetType(int caseType){

	type = caseType;
}
void Piolin::SetVisited(bool state){

	visited = state;
}
int Piolin::GetX(){

	return x;
}
int Piolin::GetY(){

	return y;
}
char Piolin::GetType(){

	return type;	
}
bool Piolin::GetVisited(){

	return visited;
}
void Piolin::GenerateNewType(){

	int tmp = rand() % 4;

	switch (tmp){
	case 0:
		type = 1;
		break;
	case 1:
		type = 2;
		break;
	case 2:
		type = 3;
		break;
	case 3:
		type = 4;
		break;
	default:
		type = 0;
		break;
	}
}
bool Piolin::operator==(Piolin pio){

	if (type == pio.GetType()){
		return true;
	}
	else {
		return false;
	}
}