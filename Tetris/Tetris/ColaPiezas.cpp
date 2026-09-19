#include "ColaPiezas.h"

ColaPiezas::ColaPiezas() {

	frente = 0;
	final = 0;
	cantidad = 0;
}

bool ColaPiezas::estaVacia() {
	return cantidad == 0;
}

bool ColaPiezas::estaLlena() {
	return cantidad == 100;
}

void ColaPiezas::encolar(char tipo) {
	if (estaLlena()) {
		return;
	}
	elementos[final] = tipo;
	final = (final + 1) % 100;
	cantidad++;
}
char ColaPiezas::desencolar() {
	if (estaVacia()) {
		return '\0';
	}
	char tipo = elementos[frente];
	frente = (frente + 1) % 100;
	cantidad--;
	return tipo;
}
char ColaPiezas::frenteCola() {
	if (estaVacia()) {
		return '\0';
	}

	return elementos[frente];
}