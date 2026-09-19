#include "Juego.h"
#include <cstdlib>
#include <ctime>

Juego::Juego() {
	srand(time(nullptr));
}

void Juego::iniciar() {

	tablero.inicializar();
	for (int i = 0;i < 5;i++) {
		colaPiezas.encolar(generarTipoAleatorio());
	}
	char tipo = colaPiezas.desencolar();
	pieza = crearPieza(tipo, 0);
	pieza.fila = 0;
	pieza.columna = 3;
}

char Juego::generarTipoAleatorio() {

	int numero = rand() % 7;
	switch (numero) {
	case 0:
		return 'I';
	case 1:
		return 'O';
	case 2:
		return 'T';
	case 3:
		return 'S';
	case 4:
		return 'Z';
	case 5:
		return 'J';
	case 6:
		return 'L';
	}
}

void Juego::moverDerecha() {

	tablero.moverDerecha(pieza);
}

void Juego::moverIzquierda() {

	tablero.moverIzquierda(pieza);
}

void Juego::moverAbajo() {

	if (!tablero.moverAbajo(pieza)) {
		fijarPieza();
	}
}

Pieza& Juego::ObtenerPieza() {

	return pieza;
}

void Juego::fijarPieza() {

	tablero.fijarPieza(pieza);
	tablero.limpiarLineas();

	char tipo = colaPiezas.desencolar();
	colaPiezas.encolar(generarTipoAleatorio());
	pieza = crearPieza(tipo, 0);
	pieza.fila = 0;
	pieza.columna = 3;
}
void Juego::rotar() {

	tablero.rotar(pieza);
}

Tablero& Juego::ObtenerTablero() {

	return tablero;
}