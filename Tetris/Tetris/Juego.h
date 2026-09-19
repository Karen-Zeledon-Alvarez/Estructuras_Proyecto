#pragma once
#include "Tablero.h"
#include "Pieza.h"
#include "ColaPiezas.h"

class Juego {

private:

	Tablero tablero;
	Pieza pieza;
	ColaPiezas colaPiezas;

private:

	Juego();

	void iniciar();

	char generarTipoAleatorio();

	void moverDerecha();

	void moverIzquierda();

	void moverAbajo();

	void rotar();

	void fijarPieza();

	Tablero& ObtenerTablero();

	Pieza& ObtenerPieza();
};

