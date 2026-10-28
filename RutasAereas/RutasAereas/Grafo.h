#pragma once

#ifndef GRAFO_H
#define GRAFO_H

#include "Aeropuerto.h"
#include <vector>
#include <unordered_map>
#include <string>
using namespace std;
class Grafo {
private:
    vector<Aeropuerto> aeropuertos;

    // Lista de adyacencia: cada aeropuerto tiene sus rutas salientes.
   vector<vector<Ruta>> adyacencia;

    // Relaciona cada código con su índice en el vector.
    unordered_map<string, int> indices;

public:
    bool cargarAeropuertos(const string& archivo);
    bool cargarRutas(const string& archivo);

    void mostrarResumen() const;

    bool existeAeropuerto(const string& codigo) const;
    void consultarAeropuerto(const string& codigo) const;

};

#endif


