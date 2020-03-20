#pragma once
#include <iostream>
#include <ctime>
class Piolin
{
private:
	//Creamos la variables que va tener cada objeto.
	int x, y;
	int type;
	bool visited;

public:

	Piolin();
	//Le asigna una posicion
	void SetPos(int xPos, int yPos);
	//Le asigna un tipo
	void SetType(int caseType);
	//Le asigna si ha sido visitada default: false
	void SetVisited(bool);
	//Para obtener su X.
	int GetX();
	//Para obtener su Y.
	int GetY();
	//Para obtener su tipo.
	char GetType();
	//Para obtener si ha sido visitado;
	bool GetVisited();
	//Genera los casos para diferentes tipos de piolines.
	void GenerateNewType();
	//Compara el tipo de los piolines ingresados en el operador.
	bool operator==(Piolin pio);
};

