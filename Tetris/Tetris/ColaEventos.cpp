#include "ColaEventos.h"
void ColaEventos::procesarTecla(char tecla, Juego& juego) {

	switch (tecla)
	{
	case 'a':
		juego.moverIzquierda();
		break;
	case 'd':
		juego.moverDerecha();
		break;
	case 's':
		juego.moverAbajo();
		break;
	case 'w':
		juego.rotar();
		break;
	case 'c':
		juego.usarHold();
		break;
	case ' ':
		juego.caidaRapida();
		break;
	}
}