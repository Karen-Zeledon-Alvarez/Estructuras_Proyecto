#include "Grafo.h"

#include <iostream>
#include <fstream>
using namespace std;
bool Grafo::cargarAeropuertos(const string& archivo) {
    ifstream entrada(archivo);

    if (!entrada.is_open()) {
        cerr << "Error: no se pudo abrir " << archivo << '\n';
        return false;
    }

    int cantidad;
    if (!(entrada >> cantidad) || cantidad < 0) {
        cerr << "Error: cantidad de aeropuertos invalida.\n";
        return false;
    }

    aeropuertos.clear();
    indices.clear();
    adyacencia.clear();

    for (int i = 0; i < cantidad; i++) {
        Aeropuerto a;

        if (!(entrada >> a.codigo >> a.x >> a.y
            >> a.ciudad >> a.pais)) {
            cerr << "Error leyendo el aeropuerto " << i + 1 << '\n';
            aeropuertos.clear();
            indices.clear();
            return false;
        }

        if (indices.count(a.codigo) > 0) {
            cerr << "Error: codigo duplicado: "
                << a.codigo << '\n';
            aeropuertos.clear();
            indices.clear();
            return false;
        }

        indices[a.codigo] = static_cast<int>(aeropuertos.size());
        aeropuertos.push_back(a);
    }

    adyacencia.resize(aeropuertos.size());

     cout << "Aeropuertos cargados: "
        << aeropuertos.size() << '\n';

    return true;
}

bool Grafo::cargarRutas(const string& archivo) {
    ifstream entrada(archivo);

    if (!entrada.is_open()) {
        cerr << "Error: no se pudo abrir " << archivo << '\n';
        return false;
    }

    if (aeropuertos.empty()) {
        cerr << "Error: primero cargue los aeropuertos.\n";
        return false;
    }

    int cantidad;
    if (!(entrada >> cantidad) || cantidad < 0) {
        cerr << "Error: cantidad de rutas invalida.\n";
        return false;
    }

    // Reinicia las conexiones para evitar duplicarlas al recargar.
    adyacencia.assign(aeropuertos.size(), {});

    for (int i = 0; i < cantidad; i++) {
        string origen, destino;
        int minutos;
        double costo;

        if (!(entrada >> origen >> destino >> minutos >> costo)) {
            cerr << "Error leyendo la ruta " << i + 1 << '\n';
            adyacencia.assign(aeropuertos.size(), {});
            return false;
        }

        // Verifica que ambos códigos existan.
        if (indices.count(origen) == 0 ||
            indices.count(destino) == 0) {
            cerr << "Error: aeropuerto desconocido en la ruta "
                << origen << " -> " << destino << '\n';
            adyacencia.assign(aeropuertos.size(), {});
            return false;
        }

        if (minutos < 0 || costo < 0) {
            cerr << "Error: minutos o costo negativos en "
                << origen << " -> " << destino << '\n';
            adyacencia.assign(aeropuertos.size(), {});
            return false;
        }

        int indiceOrigen = indices.at(origen);
        int indiceDestino = indices.at(destino);

        // Se agrega solamente la direccion indicada en el archivo.
        adyacencia[indiceOrigen].push_back({
            indiceDestino, minutos, costo
            });
    }

    cout << "Rutas cargadas: " << cantidad << '\n';
    return true;
}

void Grafo::mostrarResumen() const {
    cout << "\n========== RESUMEN DEL GRAFO ==========\n";
    cout << "Aeropuertos: " << aeropuertos.size() << '\n';

    size_t totalRutas = 0;

    for (const auto& lista : adyacencia) {
        totalRutas += lista.size();
    }

    cout << "Rutas dirigidas: " << totalRutas << '\n';
    cout << "========================================\n";
}


bool Grafo::existeAeropuerto(const string& codigo) const {
    return indices.count(codigo) > 0;
}

void Grafo::consultarAeropuerto(const string& codigo) const {
    // Verificar si el aeropuerto existe.
    if (!existeAeropuerto(codigo)) {
        cout << "\nError: el aeropuerto "
            << codigo << " no existe.\n";
        return;
    }

    // Obtener el indice del aeropuerto.
    int indice = indices.at(codigo);

    const Aeropuerto& aeropuerto = aeropuertos[indice];

    cout << "\n===== DATOS DEL AEROPUERTO =====\n";
    cout << "Codigo: " << aeropuerto.codigo << '\n';
    cout << "Ciudad: " << aeropuerto.ciudad << '\n';
    cout << "Pais: " << aeropuerto.pais << '\n';
    cout << "Posicion: (" << aeropuerto.x
        << ", " << aeropuerto.y << ")\n";

    cout << "\n===== RUTAS SALIENTES =====\n";

    const auto& rutas = adyacencia[indice];

    if (rutas.empty()) {
        cout << "Este aeropuerto no tiene rutas salientes.\n";
        return;
    }

    for (const Ruta& ruta : rutas) {
        const Aeropuerto& destino = aeropuertos[ruta.destino];

        cout << aeropuerto.codigo << " -> "
            << destino.codigo
            << " | Ciudad: " << destino.ciudad
            << " | Minutos: " << ruta.minutos
            << " | Costo: $" << ruta.costo
            << '\n';
    }

    cout << "Total de rutas salientes: "
        << rutas.size() << '\n';
}

