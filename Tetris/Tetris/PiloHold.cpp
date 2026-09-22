#include "PiloHold.h"

PiloHold::PiloHold() {
	tope = 0;
}

bool PiloHold::Vacia() {

		return tope == 0;
}

bool PiloHold::Llena() {

	return tope == 7;
}

void PiloHold::apilar(char tipo) {
	
	if (Llena())
		return;

	elementos[tope] = tipo;
	tope++;
}

char PiloHold::desapilar() {
	
	if (Vacia())
		return '\0';

	tope--;
	return elementos[tope];

}

char PiloHold::verTope() {

	if (Vacia())
		return '\0';

	return elementos[tope - 1];
}