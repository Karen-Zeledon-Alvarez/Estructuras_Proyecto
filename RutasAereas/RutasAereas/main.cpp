
#include <iostream>
#include "Grafo.h"
#include <SFML/Graphics.hpp>
#include <optional>

using namespace std;

// Pide origen y destino, y valida los casos especiales.
// Devuelve false si no se puede hacer la consulta.
bool pedirOrigenDestino(const Grafo& grafo, string& o, string& d) {
    cout << "Origen: ";  cin >> o;
    cout << "Destino: "; cin >> d;

    if (!grafo.existeAeropuerto(o)) {
        cout << "El aeropuerto " << o << " no existe.\n";
        return false;
    }
    if (!grafo.existeAeropuerto(d)) {
        cout << "El aeropuerto " << d << " no existe.\n";
        return false;
    }
    if (o == d) {
        cout << "El origen y el destino son iguales.\n";
        return false;
    }
    return true;
}

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
        cout << "3. Ruta con menos escalas\n";
        cout << "4. Ruta mas rapida\n";
        cout << "5. Ruta mas barata\n";
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
        case 3: {
            string o, d;
            cout << "Origen: ";  cin >> o;
            cout << "Destino: "; cin >> d;

            if (!grafo.existeAeropuerto(o)) { cout << "El aeropuerto " << o << " no existe.\n"; break; }
            if (!grafo.existeAeropuerto(d)) { cout << "El aeropuerto " << d << " no existe.\n"; break; }
            if (o == d) { cout << "El origen y el destino son iguales.\n"; break; }

            ResultadoRuta r = grafo.rutaMenosEscalas(o, d);
            if (!r.existe) cout << "No existe ruta de " << o << " a " << d << ".\n";
            else grafo.mostrarResultado(r);
            break;
        }
        case 4:
        case 5: {
            string o, d;
            if (!pedirOrigenDestino(grafo, o, d)) break;

            ResultadoRuta r;
            if (opcion == 3)      r = grafo.rutaMenosEscalas(o, d);
            else if (opcion == 4) r = grafo.rutaOptima(o, d, Criterio::MINUTOS);
            else                  r = grafo.rutaOptima(o, d, Criterio::COSTO);

            if (!r.existe) cout << "No existe ruta de " << o << " a " << d << ".\n";
            else grafo.mostrarResultado(r);
            break;
        }

        case 0:
            cout << "Cerrando el programa...\n";
            break;

        default:
            cout << "Opcion no valida.\n";
        }

    } while (opcion != 0);

    return 0;
}
