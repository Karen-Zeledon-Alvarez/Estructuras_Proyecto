// Tetris.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//
#include "Juego.h"
#include "ColaEventos.h"
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

int main()
{
    Juego juego;
    ColaEventos eventos;
    juego.iniciar();
    char tecla;
    while (!juego.terminado()) {
        cout << "Ingrese tecla: ";
        cin >> tecla;

        eventos.procesarTecla(tecla, juego);

        cout << "Fila: "
            << juego.ObtenerPieza().fila
            << endl;

        cout << "Columna: "
            << juego.ObtenerPieza().columna
            << endl;
        juego.actualizar();
        cout << "Fila: " << juego.ObtenerPieza().fila 
            << "Nivel: "
            << juego.obtenerNivel()
            << " | Velocidad: "
            << juego.obtenerVelocidad()
            << " ms" << endl;

        this_thread::sleep_for(
            chrono::milliseconds(
                juego.obtenerVelocidad()
            )
        );
       
    }
    
    cout << "GAME OVER"<<endl;

    return 0;
}
