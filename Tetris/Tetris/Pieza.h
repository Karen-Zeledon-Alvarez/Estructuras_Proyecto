#pragma once
struct Pieza
{
	char tipo;
	int orientacion;
	int fila;
	int columna;
	int forma[4][4];
	
	
};
Pieza crearPieza(char tipo, int orientacion);
Pieza crearT(int orientacion);
Pieza crearI(int orientacion);
Pieza crearS(int orientacion);
Pieza crearO(int orientacion);
Pieza crearZ(int orientacion);
Pieza crearL(int orientacion);
Pieza crearJ(int orientacion);
