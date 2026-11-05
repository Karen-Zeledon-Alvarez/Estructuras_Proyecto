#pragma once

#ifndef GRAFO_H
#define GRAFO_H

#include "Aeropuerto.h"
#include <vector>
#include <unordered_map>
#include <string>
#include <queue>
#include <algorithm> 
using namespace std;

struct ResultadoRuta {
    bool existe = false;     // false si no hay ruta posible
    vector<int> camino;      // índices de aeropuertos, del origen al destino
    int totalMinutos = 0;
    double totalCosto = 0;
};

class Grafo {
private:
    vector<Aeropuerto> aeropuertos;

    // Cada aeropuerto tiene sus rutas salientes
   vector<vector<Ruta>> adyacencia;

    // Relaciona cada código con su índice en el vector
    unordered_map<string, int> indices;
    
    // Devuelve la ruta directa
    const Ruta* buscarRuta(int origen, int destino) const;

    //Reconstruye el camino usando el vector padre y suma
    ResultadoRuta construirResultado(int origen, int destino, const vector<int>& padre) const;

public:
    bool cargarAeropuertos(const string& archivo);
    bool cargarRutas(const string& archivo);

    void mostrarResumen() const;

    bool existeAeropuerto(const string& codigo) const;
    void consultarAeropuerto(const string& codigo) const;

    ResultadoRuta rutaMenosEscalas(const string& codOrigen, const string& codDestino) const;
    void mostrarResultado(const ResultadoRuta& r) const;
};

#endif


