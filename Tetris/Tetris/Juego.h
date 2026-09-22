#pragma once
#include "Tablero.h"
#include "Pieza.h"
#include "ColaPiezas.h"
#include "PiloHold.h"

class Juego {

private:

	Tablero tablero;
	Pieza pieza;

	ColaPiezas colaPiezas;
	PiloHold hold;
	bool holdUsado;

	bool JuegoTerminado;
	int puntos;
	int lineasEliminadas;
	int nivel;

	static const int lineaNivel = 10;
	static const int velocidadInicio = 1000;
	static const int reducirVelocidad = 100;
	static const int velocidadMinima = 100;

public:

	Juego();

	void iniciar();

	void actualizar();

	char generarTipoAleatorio();

	void moverDerecha();

	void moverIzquierda();

	void moverAbajo();

	void rotar();

	void caidaRapida();

	void fijarPieza();

	void usarHold();

	bool terminado();

	bool crearSiguientePieza();

	int obtenerPuntos();

	void agregarPuntos(int lineas);

	void nivelActual();

	int obtenerLineas();

	int obtenerNivel();

	int obtenerVelocidad();

	

	Tablero& ObtenerTablero();

	Pieza& ObtenerPieza();
};

