#pragma once
#include "Pieza.h"
#ifndef TABLERO_H
#define TABLERO_H

struct NodoFila
{
    int celdas[10];
    NodoFila* siguiente;
};
class Tablero
{
private:
    NodoFila* inicio;
    NodoFila* final;
    
public:
    Tablero();
    ~Tablero();

    void inicializar();

    void mostrar();

    void establecerCelda(int fila, int columna, int valor);

    int obtenerCelda(int fila, int columna);

    bool filaCompleta(NodoFila* fila);

    void limpiarLineas();
    
    bool PuedoColocar(Pieza pieza, int nuevaFila, int nuevaColumna, int nuevaOrientacion);

    bool puedoMover(Pieza pieza, int nuevaFila, int nuevaColumna);

    NodoFila* obtenerFila(int numeroFila);

    void moverDerecha(Pieza& pieza);

    void moverIzquierda(Pieza& pieza);

    bool moverAbajo(Pieza& pieza);

    void fijarPieza(Pieza& pieza);

    bool rotar(Pieza& pieza);
};

#endif 
