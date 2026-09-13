#include "Tablero.h"
#include <iostream>

using namespace std;

Tablero::Tablero() {
	inicio = nullptr;
	final = nullptr;
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
bool filaCompleta(NodoFila* fila) {
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
				anterior->siguiente = actual->siguiente;
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
		} else{

			anterior = actual;
			actual = actual->siguiente;
		}
	}
}