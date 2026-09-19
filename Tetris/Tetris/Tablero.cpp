#include "Tablero.h"
#include <iostream>


using namespace std;

Tablero::Tablero() {
	inicio = nullptr;
	final = nullptr;
}
Tablero::~Tablero() {
}

void Tablero::inicializar() {

	for (int k = 0;k < 20;k++) 
	{
		NodoFila* FilaN = new NodoFila();

		for (int i = 0;i < 10;i++) {
			FilaN->celdas[i] = 0;
		}
		FilaN->siguiente = nullptr;

		if (inicio == nullptr) {
			inicio = FilaN;
			final = FilaN;
		}
		else {

			final->siguiente = FilaN;
			final = FilaN;
		}
	}
}
void Tablero::mostrar() {
	NodoFila* actual = inicio;
	while (actual != nullptr) {
		for (int k = 0;k < 10;k++) {
			cout << actual->celdas[k] << " ";
		}
		cout << endl;
		actual = actual->siguiente;
	}
}
int Tablero::obtenerCelda(int fila, int columna) {
	NodoFila* actual = inicio;
	for (int k = 0;k < fila;k++) {
		actual = actual->siguiente;
	}
	return actual->celdas[columna];
}
void Tablero::establecerCelda(int fila, int columna, int valor) {
	NodoFila* actual = inicio;
	for (int k = 0;k < fila;k++) {
		actual = actual->siguiente;
	}
	actual->celdas[columna] = valor;
}
bool Tablero::filaCompleta(NodoFila* fila) {
	for (int k = 0;k < 10;k++) {
		if (fila->celdas[k] == 0) {
			return false;
		}
	}
	return true;
}
void Tablero::limpiarLineas() {
	NodoFila* actual = inicio;
	NodoFila* anterior = nullptr;
	
	while (actual != nullptr) {

		if (filaCompleta(actual)) {
			NodoFila* eliminar = actual;


			if (actual == inicio) {
				inicio = actual->siguiente;
				actual = inicio;
			}
			else {
				anterior->siguiente = actual;//actual->siguiente
				actual = actual->siguiente;
			}
			if (eliminar == final) {
				final = anterior;
			}
			delete eliminar;
			NodoFila* FilaN = new NodoFila();
			for (int k = 0;k < 10;k++) {
				FilaN->celdas[k] = 0;
			}
			FilaN->siguiente = inicio;
			inicio = FilaN;
			if (final == nullptr) {
				final = inicio;
			}
		}
		else {

			anterior = actual;
			actual = actual->siguiente;
		}
	}
}
NodoFila* Tablero::obtenerFila(int numeroFila) {
	NodoFila* actual = inicio;
	for (int k = 0;k < numeroFila;k++) {
		actual = actual->siguiente;
	}
	return actual;
}
bool Tablero::PuedoColocar(Pieza pieza, int nuevaFila, int nuevaColumna,int nuevaOrientacion) {
	Pieza piezaPrueba = crearPieza(pieza.tipo, nuevaOrientacion);
	for (int i = 0;i < 4;i++) {
		for (int k = 0;k < 4;k++) {
			if (pieza.forma[i][k] == 1) {
				int filaTablero = nuevaFila + i;
				int columnaTablero = nuevaColumna + k;

				if (filaTablero < 0 || filaTablero >= 20) {
					return false;
				}
				if (columnaTablero < 0 || columnaTablero >= 10) {
					return false;
				}

				NodoFila* fila = obtenerFila(filaTablero);
				if (fila->celdas[columnaTablero] != 0) {
					return false;
				}
			}
		}
	}
	return true;
}
bool Tablero::puedoMover(Pieza pieza, int nuevaFila, int nuevaColumna) {
	return PuedoColocar(pieza,nuevaFila,nuevaColumna,pieza.orientacion);
}
void Tablero::moverIzquierda(Pieza& pieza) {
	
	if (puedoMover(pieza, pieza.fila, pieza.columna - 1)) {
		pieza.columna--;
	}
}
void Tablero::moverDerecha(Pieza& pieza) {

	if (puedoMover(pieza, pieza.fila, pieza.columna + 1)) {
		pieza.columna++;
	}
}
bool Tablero::moverAbajo(Pieza& pieza) {

	if (puedoMover(pieza, pieza.fila + 1, pieza.columna)) {
		pieza.fila++;
		return true;
	}
	
	return false;
}

bool Tablero::rotar(Pieza& pieza) {
	int nuevaOrientacion = (pieza.orientacion + 1) % 4;
	if (PuedoColocar(pieza, pieza.fila, pieza.columna, nuevaOrientacion)) {
		Pieza piezaRotada = crearPieza(pieza.tipo, nuevaOrientacion);
		pieza.orientacion = nuevaOrientacion;
		for (int i = 0;i < 4;i++) {
			for (int k = 0;k < 4;k++) {
				pieza.forma[i][k] = piezaRotada.forma[i][k];
			}
		}
		return true;
	}
	return false;
}
void Tablero::fijarPieza(Pieza& pieza) {
	for (int i = 0;i < 4;i++) {
		for (int k = 0;k < 4;k++) {
			if (pieza.forma[i][k] == 1) {
				int filaTablero = pieza.fila + i;
				int columnaTablero = pieza.columna + k;

				NodoFila* fila = obtenerFila(filaTablero);
				fila->celdas[columnaTablero] = 1;

			}
		}
	}
}

