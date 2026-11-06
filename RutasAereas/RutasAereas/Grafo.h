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
    vector<int> minutosTramo;
    vector<double> costoTramo;
};

enum class Criterio { MINUTOS, COSTO };

// Una ruta cancelada
struct RutaCancelada {
    int origen;
    Ruta ruta;
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
    
    // Que usa dijkstra
    static double peso(const Ruta& r, Criterio criterio);

    // DFS recursivo
    void dfs(int u, vector<bool>& visitado) const;

    vector<RutaCancelada> canceladas;
    
public:
    const string& codigoDe(int indice) const { return aeropuertos[indice].codigo; }
    bool cargarAeropuertos(const string& archivo);
    bool cargarRutas(const string& archivo);

    void mostrarResumen() const;

    bool existeAeropuerto(const string& codigo) const;
    void consultarAeropuerto(const string& codigo) const;

    ResultadoRuta rutaMenosEscalas(const string& codOrigen, const string& codDestino) const;
    void mostrarResultado(const ResultadoRuta& r) const;

    ResultadoRuta rutaOptima(const string& codOrigen,const string& codDestino,
        Criterio criterio) const;

    // visitado[i] == true si el aeropuerto i es alcanzable desde el origen.
    vector<bool> alcanzables(const string& codOrigen) const;
    void mostrarAlcanzables(const string& codOrigen) const;

    // Aeropuertos no es posible llegar al destino.
    vector<int> noLleganA(const string& codDestino) const;

    bool cancelarRuta(const string& codOrigen, const string& codDestino);
    int restaurarRutas();   // devuelve cuántas se restauraron

    // La interfaz la usará para dibujar las canceladas de otra forma.
    const vector<RutaCancelada>& getCanceladas() const { return canceladas; }

    // Rutas cuya cancelación deja algún aeropuerto inalcanzable desde el origen.
    vector<pair<int, int>> rutasCriticas(const string& codOrigen);
    
    int cantidadAeropuertos() const { 
        return static_cast<int>(aeropuertos.size()); }

    const Aeropuerto& getAeropuerto(int i) const { 
        return aeropuertos[i]; }

    const vector<Ruta>& getRutas(int i) const { 
        return adyacencia[i]; }
};

#endif


