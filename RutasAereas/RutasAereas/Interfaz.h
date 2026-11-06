#pragma once
#include <SFML/Graphics.hpp>
#include "Grafo.h"

// consulta de ruta activa
enum class Modo { NINGUNO, ESCALAS, RAPIDA, BARATA };

// cada botón del panel
enum class Accion { ESCALAS, RAPIDA, BARATA, ALCANZABLES, CANCELAR, RESTAURAR, LIMPIAR };

struct Boton {
    sf::FloatRect area;   // posición y tamaño en píxeles
    string texto;
    Accion accion;
};

class Interfaz {
private:
    Grafo& grafo;

    sf::RenderWindow ventana;
    sf::View vistaMapa;
    sf::Font fuente;

    float ladoMapa = 800.f;
    float anchoPanel = 360.f;

    // Selección
    int origen = -1;
    int destino = -1;

    // Estado de la consulta
    Modo modo = Modo::NINGUNO;
    ResultadoRuta resultado;            // resultado.existe == false si no hay ruta
    bool mostrandoAlcanzables = false;
    vector<bool> alcanzable;            // alcanzable[i] según el DFS
    string mensaje;                     // avisos y errores para el panel

    vector<Boton> botones;

    // Lógica
    void crearBotones();
    void ejecutarAccion(Accion accion);
    void recalcular();
    string codigo(int i) const;
    string unirCodigos(const vector<int>& lista) const;

    // Eventos
    void procesarEventos();
    void manejarClic(sf::Vector2i pixel);
    int aeropuertoEn(sf::Vector2f punto) const;

    // Dibujo
    void dibujarMapa();
    void dibujarPanel();
    void dibujarBotones();
    void dibujarLineaGruesa(sf::Vector2f a, sf::Vector2f b, float grosor, sf::Color color);
    void dibujarLineaPunteada(sf::Vector2f a, sf::Vector2f b, sf::Color color);
    void escribir(const string& texto, float x, float y, unsigned tam, sf::Color color);

public:
    explicit Interfaz(Grafo& g);
    bool iniciar(const string& rutaFuente);
    void ejecutar();
};