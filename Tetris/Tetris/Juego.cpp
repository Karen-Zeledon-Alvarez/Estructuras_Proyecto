#include "Juego.h"
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>

Juego::Juego() {
	
	srand(time(nullptr));
	holdUsado = false;
	JuegoTerminado = false;
	puntos = 0;
	lineasEliminadas = 0;
	nivel = 1;
}

void Juego::iniciar() {

	tablero.inicializar();
	holdUsado = false;
	JuegoTerminado = false;
	puntos = 0;
	lineasEliminadas = 0;
	nivel = 1;

	for (int i = 0;i < 5;i++) {

		colaPiezas.encolar(generarTipoAleatorio());
	}

	crearSiguientePieza();
}

char Juego::generarTipoAleatorio() {

	int numero = rand() % 7;
	switch (numero) {
	case 0:
		return 'I';
		break;
	case 1:
		return 'O';
		break;
	case 2:
		return 'T';
		break;
	case 3:
		return 'S';
		break;
	case 4:
		return 'Z';
		break;
	case 5:
		return 'J';
		break;
	case 6:
		return 'L';
		break;
	}
}

void Juego::moverDerecha() {

	if (JuegoTerminado) {
		return;
	}
	tablero.moverDerecha(pieza);
}

void Juego::moverIzquierda() {

	if (JuegoTerminado) {
		return;
	}
	tablero.moverIzquierda(pieza);
}

void Juego::moverAbajo() {

	if (JuegoTerminado) {
		return;
	}
	if (!tablero.moverAbajo(pieza)) {
		fijarPieza();
	}
}

void Juego::rotar() {

	if (JuegoTerminado) {
		return;
	}
	tablero.rotar(pieza);
}

void Juego::caidaRapida() {

	if (JuegoTerminado) {
		return;
	}

	while (tablero.moverAbajo(pieza)) {

	}
	fijarPieza();
}
void Juego::fijarPieza() {

	tablero.fijarPieza(pieza);
	int lineas = tablero.limpiarLineas();
	agregarPuntos(lineas);
	lineasEliminadas += lineas;
	nivelActual();
	colaPiezas.encolar(generarTipoAleatorio());
	
	holdUsado = false;
	crearSiguientePieza();
	
}

void Juego::usarHold() {

	if (JuegoTerminado) {
		return;
	}
	if (holdUsado) {
		return;
	}
	holdUsado = true;

	if (hold.Vacia()) {

		hold.apilar(pieza.tipo);
		char sig = colaPiezas.desencolar();
		colaPiezas.encolar(generarTipoAleatorio());
		pieza = crearPieza(sig, 0);

	}
	else {
		char guardar = hold.desapilar();
		hold.apilar(pieza.tipo);
		pieza = crearPieza(guardar, 0);
		
	}
		pieza.fila = 0;
		pieza.columna = 3;
		if (!tablero.PuedoColocar(pieza, pieza.fila, pieza.columna, pieza.orientacion)) {
			JuegoTerminado = true;
		}
}

bool Juego::terminado() {

	return JuegoTerminado;
}

bool Juego::crearSiguientePieza() {

	char tipo = colaPiezas.desencolar();
	pieza = crearPieza(tipo, 0);
	pieza.fila = 0;
	pieza.columna = 3;

	if (!tablero.PuedoColocar(pieza, pieza.fila, pieza.columna, pieza.orientacion)) {
		JuegoTerminado = true;
		return false;
	}
	return true;
}

int Juego::obtenerPuntos() {

	return puntos;
}

void Juego::agregarPuntos(int lineas) {

	switch (lineas)
	{
	case 1:
		puntos += 100;
		break;
	case 2:
		puntos += 300;
		break;
	case 3:
		puntos += 500;
		break;
	case 4:
		puntos += 800;
		break;
	case 5:
		puntos += 1000;
		break;
	}
}

void Juego::nivelActual() {

	nivel = (lineasEliminadas / lineaNivel) + 1;
}

int Juego::obtenerLineas() {

	return lineasEliminadas;
}

int Juego::obtenerNivel() {

	return nivel;
}

int Juego::obtenerVelocidad() {

	int velocidad = velocidadInicio - ((nivel - 1) * reducirVelocidad);

	if (velocidad < velocidadMinima) {
		velocidad = velocidadMinima;
	}
	return velocidad;
}

void Juego::actualizar() {

	if (JuegoTerminado) {
		return;
	}
	moverAbajo();
}

Tablero& Juego::ObtenerTablero() {

	return tablero;
}

Pieza& Juego::ObtenerPieza() {

	return pieza;
}