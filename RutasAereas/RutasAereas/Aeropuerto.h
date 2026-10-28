#pragma once
#ifndef AEROPUERTO_HPP
#define AEROPUERTO_HPP
using namespace std;
#include <string>

struct Aeropuerto {
    string codigo;
    int x;
    int y;
    string ciudad;
    string pais;
};

struct Ruta {
    int destino;
    int minutos;
    double costo;
};

#endif