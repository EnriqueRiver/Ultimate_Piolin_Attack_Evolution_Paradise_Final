#include "Piolin.h"

Piolin::Piolin(){
	//Le asignamos x, y -1 ya que empieza en 1 ,1.
	x = -1;
	y = -1;
	//A todos le asignamos un tipo default.
	type = 0;
	//Le asignamos que no ha sido visitada.
	visited = false;
}
void Piolin::SetPos(int xPos, int yPos){
	//Igualamos las coordenadas a las recibidas.
	x = xPos;
	y = yPos;
}
void Piolin::SetType(int caseType){
	//Igualamos el tipo al recibido.
	type = caseType;
}
void Piolin::SetVisited(bool state){
	//Igualamos el booleano para saber si ha sido visitada
	visited = state;
}
int Piolin::GetX(){
	//Retronamos la X.
	return x;
}
int Piolin::GetY(){
	//Retornamos la Y.
	return y;
}
char Piolin::GetType(){
	//Retorna el tipo
	return type;	
}
bool Piolin::GetVisited(){
	//Retorna si ha sido visitado.
	return visited;
}
void Piolin::GenerateNewType(){
	//Genera numeros aleatorios y les asigna un tipo.
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
	//Regresa true si el tipo es igual y al revez si no es igual.
	if (type == pio.GetType()){
		return true;
	}
	else {
		return false;
	}
}