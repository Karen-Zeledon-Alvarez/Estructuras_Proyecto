#pragma once
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
};

#endif 
