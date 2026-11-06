
#include <iostream>
#include "Grafo.h"
#include "Interfaz.h"
#include "mainConsola.h"
#include <SFML/Graphics.hpp>
#include <optional>

using namespace std;

int main() {
    Grafo grafo;

    if (!grafo.cargarAeropuertos("datos/aeropuertos.txt")) {
        return 1;
            }

    if (!grafo.cargarRutas("datos/rutas.txt")) {
        return 1;
        }

    Interfaz interfaz(grafo);
    if (!interfaz.iniciar("datos/comic.ttf")) return 1;
    interfaz.ejecutar();

    return 0;

}
