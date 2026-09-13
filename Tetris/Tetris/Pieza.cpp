#include "Pieza.h"

Pieza crear(char tipo) {
	Pieza pieza;
	pieza.tipo = tipo;
	pieza.orientacion = 0;
	return pieza;
	
}
Pieza crearT() {
	Pieza pieza;
	pieza.tipo = 'T';
	
	for (int k = 0;k < 5;k++) {
		for (int i = 0;i < 5;i++) {
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

		pieza.forma[0][2] = 1;
		pieza.forma[1][2] = 1;
		pieza.forma[2][2] = 1;
		pieza.forma[1][3] = 1;
	}
	if (pieza.orientacion == 2) {

		pieza.forma[0][1] = 1;
		pieza.forma[1][0] = 1;
		pieza.forma[1][1] = 1;
		pieza.forma[2][1] = 1;
	}
	if (pieza.orientacion == 3) {

		pieza.forma[0][1] = 1;
		pieza.forma[0][0] = 1;
		pieza.forma[0][2] = 1;
		pieza.forma[1][1] = 1;
	}
	
	return pieza;

}
Pieza crearI() {
	Pieza pieza;
	pieza.tipo = 'I';

	for (int k = 0;k < 5;k++) {
		for (int i = 0;i < 5;i++) {
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
Pieza crearO() {
	Pieza pieza;
	pieza.tipo = 'O';

	for (int k = 0;k < 5;k++) {
		for (int i = 0;i < 5;i++) {
			pieza.forma[k][i] = 0;
		}
	}
	if (pieza.orientacion == 0) {

		pieza.forma[0][0] = 1;
		pieza.forma[0][1] = 1;
		pieza.forma[1][0] = 1;
		pieza.forma[1][1] = 1;
	}
	if (pieza.orientacion == 1) {

		pieza.forma[0][0] = 1;
		pieza.forma[0][1] = 1;
		pieza.forma[1][0] = 1;
		pieza.forma[1][1] = 1;
	}
	if (pieza.orientacion == 2) {

		pieza.forma[0][0] = 1;
		pieza.forma[0][1] = 1;
		pieza.forma[1][0] = 1;
		pieza.forma[1][1] = 1;
	}
	if (pieza.orientacion == 3) {

		pieza.forma[0][0] = 1;
		pieza.forma[0][1] = 1;
		pieza.forma[1][0] = 1;
		pieza.forma[1][1] = 1;
	}

	return pieza;

}
Pieza crearS() {
	Pieza pieza;
	pieza.tipo = 'S';

	for (int k = 0;k < 5;k++) {
		for (int i = 0;i < 5;i++) {
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
Pieza crearZ() {
	Pieza pieza;
	pieza.tipo = 'Z';

	for (int k = 0;k < 5;k++) {
		for (int i = 0;i < 5;i++) {
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
Pieza crearL() {
	Pieza pieza;
	pieza.tipo = 'L';

	for (int k = 0;k < 5;k++) {
		for (int i = 0;i < 5;i++) {
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
Pieza crearI() {
	Pieza pieza;
	pieza.tipo = 'I';

	for (int k = 0;k < 5;k++) {
		for (int i = 0;i < 5;i++) {
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