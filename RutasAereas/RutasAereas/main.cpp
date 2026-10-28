
#include <iostream>
#include "Grafo.h"
using namespace std;
int main() {
    Grafo grafo;

    cout << "SISTEMA DE RUTAS AEREAS\n\n";

    if (!grafo.cargarAeropuertos("datos/aeropuertos.txt")) {
        cout << "No se pudieron cargar los aeropuertos.\n";
        return 1;
    }

    if (!grafo.cargarRutas("datos/rutas.txt")) {
        cout << "No se pudieron cargar las rutas.\n";
        return 1;
    }

    int opcion;

    do {
        cout << "\n========== MENU ==========\n";
        cout << "1. Consultar aeropuerto\n";
        cout << "2. Mostrar resumen del grafo\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opcion: ";

        if (!(cin >> opcion)) {
            cout << "Entrada invalida.\n";
            return 1;
        }

        switch (opcion) {
        case 1: {
            string codigo;

            cout << "Ingrese el codigo del aeropuerto: ";
            cin >> codigo;

            grafo.consultarAeropuerto(codigo);
            break;
        }

        case 2:
            grafo.mostrarResumen();
            break;

        case 0:
            cout << "Cerrando el programa...\n";
            break;

        default:
            cout << "Opcion no valida.\n";
        }

    } while (opcion != 0);

    return 0;
}
