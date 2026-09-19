#include "Pieza.h"

Pieza crearPieza(char tipo,int orientacion) {
	
	if (tipo == 'T') {
		return crearT(orientacion);
	}
	if (tipo == 'I') {
		return crearI(orientacion);
	}
	if (tipo == 'O') {
		return crearO(orientacion);
	}
	if (tipo == 'S') {
		return crearS(orientacion);
	}
	if (tipo == 'Z') {
		return crearZ(orientacion);
	}
	if (tipo == 'L') {
		return crearL(orientacion);
	}
	if (tipo == 'J') {
		return crearJ(orientacion);
	}

	return Pieza{};
}
Pieza crearT(int orientacion) {
	Pieza pieza;
	pieza.tipo = 'T';
	pieza.orientacion = orientacion;
	pieza.fila = 0;
	pieza.columna = 0;
	
	for (int k = 0;k < 4;k++) {
		for (int i = 0;i < 4;i++) {
		pieza.forma[k][i] = 0;
		}
	}
	if (pieza.orientacion == 0) {

		pieza.forma[0][1] = 1;
		pieza.forma[1][0] = 1;
		pieza.forma[1][1] = 1;
		pieza.forma[1][2] = 1;
	
	}
	if (pieza.orientacion == 1) {

		pieza.forma[0][0] = 1;
		pieza.forma[1][0] = 1;
		pieza.forma[2][0] = 1;
		pieza.forma[1][1] = 1;
		
	}
	if (pieza.orientacion == 2) {

		pieza.forma[1][0] = 1;
		pieza.forma[0][1] = 1;
		pieza.forma[1][1] = 1;
		pieza.forma[2][1] = 1;
		
	}
	if (pieza.orientacion == 3) {

		pieza.forma[0][0] = 1;
		pieza.forma[0][1] = 1;
		pieza.forma[0][2] = 1;
		pieza.forma[1][1] = 1;
		
	}
	
	return pieza;

}
Pieza crearI(int orientacion) {
	Pieza pieza;
	pieza.tipo = 'I';
	pieza.orientacion = orientacion;
	pieza.fila = 0;
	pieza.columna = 0;
	for (int k = 0;k < 4;k++) {
		for (int i = 0;i < 4;i++) {
			pieza.forma[k][i] = 0;
		}
	}
	if (pieza.orientacion == 0) {

		pieza.forma[0][0] = 1;
		pieza.forma[0][1] = 1;
		pieza.forma[0][2] = 1;
		pieza.forma[0][3] = 1;
	
	}
	if (pieza.orientacion == 1) {

		pieza.forma[0][0] = 1;
		pieza.forma[1][0] = 1;
		pieza.forma[2][0] = 1;
		pieza.forma[3][0] = 1;
		
	}
	if (pieza.orientacion == 2) {

		pieza.forma[0][3] = 1;
		pieza.forma[1][3] = 1;
		pieza.forma[2][3] = 1;
		pieza.forma[3][3] = 1;
		
	}
	if (pieza.orientacion == 3) {

		pieza.forma[0][0] = 1;
		pieza.forma[0][1] = 1;
		pieza.forma[0][2] = 1;
		pieza.forma[0][3] = 1;
		
	}

	return pieza;

}
Pieza crearO(int orientacion) {
	Pieza pieza;
	pieza.tipo = 'O';
	pieza.orientacion = orientacion;
	pieza.fila = 0;
	pieza.columna = 0;
	for (int k = 0;k < 4;k++) {
		for (int i = 0;i < 4;i++) {
			pieza.forma[k][i] = 0;
		}
	}
	if (pieza.orientacion == 0) {

		pieza.forma[0][0] = 1;
		pieza.forma[0][1] = 1;
		pieza.forma[1][1] = 1;
		pieza.forma[1][0] = 1;
		
	}
	if (pieza.orientacion == 1) {

		pieza.forma[0][0] = 1;
		pieza.forma[0][1] = 1;
		pieza.forma[1][1] = 1;
		pieza.forma[1][0] = 1;
		
	}
	if (pieza.orientacion == 2) {

		pieza.forma[0][0] = 1;
		pieza.forma[0][1] = 1;
		pieza.forma[1][1] = 1;
		pieza.forma[1][0] = 1;
		
	}
	if (pieza.orientacion == 3) {

		pieza.forma[0][0] = 1;
		pieza.forma[0][1] = 1;
		pieza.forma[1][1] = 1;
		pieza.forma[1][0] = 1;
		
	}

	return pieza;

}
Pieza crearS(int orientacion) {
	Pieza pieza;
	pieza.tipo = 'S';
	pieza.orientacion = orientacion;
	pieza.fila = 0;
	pieza.columna = 0;
	for (int k = 0;k < 4;k++) {
		for (int i = 0;i < 4;i++) {
			pieza.forma[k][i] = 0;
		}
	}
	if (pieza.orientacion == 0) {

		pieza.forma[0][1] = 1;
		pieza.forma[0][2] = 1;
		pieza.forma[1][0] = 1;
		pieza.forma[1][1] = 1;
	}
	if (pieza.orientacion == 1) {

		pieza.forma[0][0] = 1;
		pieza.forma[1][0] = 1;
		pieza.forma[1][1] = 1;
		pieza.forma[2][1] = 1;
	}
	if (pieza.orientacion == 2) {

		pieza.forma[0][3] = 1;
		pieza.forma[0][2] = 1;
		pieza.forma[1][1] = 1;
		pieza.forma[1][2] = 1;
	}
	if (pieza.orientacion == 3) {

		pieza.forma[0][1] = 1;
		pieza.forma[1][0] = 1;
		pieza.forma[1][1] = 1;
		pieza.forma[2][0] = 1;
	}

	return pieza;

}
Pieza crearZ(int orientacion) {
	Pieza pieza;
	pieza.tipo = 'Z';
	pieza.orientacion = 0;
	pieza.fila = 0;
	pieza.columna = 0;

	for (int k = 0;k < 4;k++) {
		for (int i = 0;i < 4;i++) {
			pieza.forma[k][i] = 0;
		}
	}
	if (pieza.orientacion == 0) {

		pieza.forma[0][0] = 1;
		pieza.forma[0][1] = 1;
		pieza.forma[1][1] = 1;
		pieza.forma[1][2] = 1;
	}
	if (pieza.orientacion == 1) {

		pieza.forma[0][2] = 1;
		pieza.forma[0][3] = 1;
		pieza.forma[1][2] = 1;
		pieza.forma[1][1] = 1;
	}
	if (pieza.orientacion == 2) {

		pieza.forma[0][0] = 1;
		pieza.forma[1][0] = 1;
		pieza.forma[1][1] = 1;
		pieza.forma[2][1] = 1;
	}
	if (pieza.orientacion == 3) {

		pieza.forma[0][1] = 1;
		pieza.forma[1][0] = 1;
		pieza.forma[1][1] = 1;
		pieza.forma[2][0] = 1;
	}

	return pieza;

}
Pieza crearL(int orientacion) {
	Pieza pieza;
	pieza.tipo = 'L';
	pieza.orientacion = orientacion;
	pieza.fila = 0;
	pieza.columna = 0;

	for (int k = 0;k < 4;k++) {
		for (int i = 0;i < 4;i++) {
			pieza.forma[k][i] = 0;
		}
	}
	if (pieza.orientacion == 0) {

		pieza.forma[0][0] = 1;
		pieza.forma[1][0] = 1;
		pieza.forma[2][0] = 1;
		pieza.forma[3][0] = 1;
		pieza.forma[3][1] = 1;
		pieza.forma[3][2] = 1;
		pieza.forma[3][3] = 1;
	}
	if (pieza.orientacion == 1) {

		pieza.forma[0][0] = 1;
		pieza.forma[0][1] = 1;
		pieza.forma[0][2] = 1;
		pieza.forma[0][3] = 1;
		pieza.forma[1][3] = 1;
		pieza.forma[2][3] = 1;
		pieza.forma[3][3] = 1;
		
		
		
	}
	if (pieza.orientacion == 2) {

		pieza.forma[3][0] = 1;
		pieza.forma[3][1] = 1;
		pieza.forma[3][2] = 1;
		pieza.forma[3][3] = 1;
		pieza.forma[2][3] = 1;
		pieza.forma[1][3] = 1;
		pieza.forma[0][3] = 1;
	}
	if (pieza.orientacion == 3) {

		pieza.forma[0][0] = 1;
		pieza.forma[0][1] = 1;
		pieza.forma[0][2] = 1;
		pieza.forma[0][3] = 1;
	
		pieza.forma[1][0] = 1;
		pieza.forma[2][0] = 1;
		pieza.forma[3][0] = 1;
	
	}

	return pieza;

}
Pieza crearJ(int orientacion) {
	Pieza pieza;
	pieza.tipo = 'J';
	pieza.orientacion = orientacion;
	pieza.fila = 0;
	pieza.columna = 0;
	for (int k = 0;k < 4;k++) {
		for (int i = 0;i < 4;i++) {
			pieza.forma[k][i] = 0;
		}
	}
	if (pieza.orientacion == 0) {

		pieza.forma[0][0] = 1;
		pieza.forma[0][1] = 1;
		pieza.forma[0][2] = 1;
		pieza.forma[1][1] = 1;
		pieza.forma[2][1] = 1;
		pieza.forma[2][0] = 1;
	}
	if (pieza.orientacion == 1) {

		pieza.forma[0][0] = 1;
		pieza.forma[0][1] = 1;
		pieza.forma[1][1] = 1;
		pieza.forma[2][0] = 1;
		pieza.forma[2][2] = 1;
		pieza.forma[2][1] = 1;
	}
	if (pieza.orientacion == 2) {

		pieza.forma[0][1] = 1;
		pieza.forma[0][2] = 1;
		pieza.forma[1][1] = 1;
		pieza.forma[2][0] = 1;
		pieza.forma[2][1] = 1;
		pieza.forma[2][2] = 1;
	}
	if (pieza.orientacion == 3) {

		pieza.forma[0][0] = 1;
		pieza.forma[0][1] = 1;
		pieza.forma[0][2] = 1;
		pieza.forma[1][1] = 1;
		pieza.forma[2][1] = 1;
		pieza.forma[2][2] = 1;
	}

	return pieza;

}
