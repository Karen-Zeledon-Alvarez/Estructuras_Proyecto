#include "Interfaz.h"
#include <iostream>
#include <algorithm>
#include <optional>
#include <cmath>
#include <sstream>
#include <iomanip>

const float TAM_MUNDO = 1000.f;   // las coordenadas del archivo son de 1000x1000
const float RADIO = 6.f;

// Colores usados en varias partes
const sf::Color COLOR_ORIGEN(20, 150, 50);       // verde
const sf::Color COLOR_DESTINO(30, 80, 200);      // azul
const sf::Color COLOR_RUTA(255, 140, 0);         // naranja
const sf::Color COLOR_CANCELADA(220, 40, 40);    // rojo
const sf::Color COLOR_ALCANZABLE(40, 160, 230);  // celeste
const sf::Color COLOR_NO_ALCANZABLE(150, 150, 150);

static sf::Vector2f posicion(const Aeropuerto& a) {
    return { static_cast<float>(a.x), static_cast<float>(a.y) };
}

static string sinGuiones(string s) {
    replace(s.begin(), s.end(), '_', ' ');
    return s;
}

static string formatoMinutos(int m) {
    return to_string(m) + " min (" + to_string(m / 60) + " h "
        + to_string(m % 60) + " min)";
}

static string formatoCosto(double c) {
    ostringstream salida;
    salida << "$" << fixed << setprecision(2) << c;
    return salida.str();
}

// Agrega una línea al mensaje sin borrar lo que ya tenía.
static void agregarLinea(string& mensaje, const string& linea) {
    if (!mensaje.empty()) mensaje += "\n";
    mensaje += linea;
}

Interfaz::Interfaz(Grafo& g) : grafo(g) {}

bool Interfaz::iniciar(const string& rutaFuente) {
    if (!fuente.openFromFile(rutaFuente)) {
        cerr << "Error: no se pudo cargar la fuente " << rutaFuente << '\n';
        return false;
    }

    unsigned altoPantalla = sf::VideoMode::getDesktopMode().size.y;
    ladoMapa = min(900.f, altoPantalla * 0.85f);

    unsigned ancho = static_cast<unsigned>(ladoMapa + anchoPanel);
    unsigned alto = static_cast<unsigned>(ladoMapa);

    ventana.create(sf::VideoMode({ ancho, alto }), "Planificador de vuelos",
        sf::Style::Titlebar | sf::Style::Close);
    ventana.setFramerateLimit(60);

    vistaMapa = sf::View(sf::FloatRect({ 0.f, 0.f }, { TAM_MUNDO, TAM_MUNDO }));
    vistaMapa.setViewport(sf::FloatRect({ 0.f, 0.f }, { ladoMapa / ancho, 1.f }));

    crearBotones();
    return true;
}

void Interfaz::crearBotones() {
    botones.clear();

    float x0 = ladoMapa + 20.f;
    float ancho = (anchoPanel - 50.f) / 2.f;   // dos columnas, 10 px entre ellas
    float alto = 32.f;
    float y0 = 140.f;
    float paso = alto + 8.f;

    // Función local para no repetir las cuentas de posición.
    auto agregar = [&](int fila, int col, const string& texto, Accion accion) {
        float x = x0 + col * (ancho + 10.f);
        float y = y0 + fila * paso;
        botones.push_back({ sf::FloatRect({ x, y }, { ancho, alto }), texto, accion });
        };

    agregar(0, 0, "Menos escalas", Accion::ESCALAS);
    agregar(0, 1, "Mas rapida", Accion::RAPIDA);
    agregar(1, 0, "Mas barata", Accion::BARATA);
    agregar(1, 1, "Alcanzables", Accion::ALCANZABLES);
    agregar(2, 0, "Cancelar ruta", Accion::CANCELAR);
    agregar(2, 1, "Restaurar rutas", Accion::RESTAURAR);
    agregar(3, 0, "Limpiar", Accion::LIMPIAR);
}

void Interfaz::ejecutar() {
    while (ventana.isOpen()) {
        procesarEventos();

        ventana.clear(sf::Color(235, 242, 250));
        dibujarMapa();
        dibujarPanel();
        ventana.display();
    }
}

string Interfaz::codigo(int i) const {
    return grafo.getAeropuerto(i).codigo;
}

string Interfaz::unirCodigos(const vector<int>& lista) const {
    string texto;
    for (size_t k = 0; k < lista.size(); k++) {
        texto += codigo(lista[k]);
        if (k + 1 < lista.size()) {
            texto += (k % 5 == 4) ? "\n" : " > ";
        }
    }
    return texto;
}

void Interfaz::ejecutarAccion(Accion accion) {
    mensaje.clear();

    switch (accion) {
    case Accion::ESCALAS:
        modo = Modo::ESCALAS;
        mostrandoAlcanzables = false;
        break;

    case Accion::RAPIDA:
        modo = Modo::RAPIDA;
        mostrandoAlcanzables = false;
        break;

    case Accion::BARATA:
        modo = Modo::BARATA;
        mostrandoAlcanzables = false;
        break;

    case Accion::ALCANZABLES:
        if (origen == -1) {
            mensaje = "Seleccione un origen.";
            return;
        }
        modo = Modo::NINGUNO;
        mostrandoAlcanzables = true;
        break;

    case Accion::CANCELAR:
        if (origen == -1 || destino == -1) {
            mensaje = "Seleccione origen y destino\nde la ruta a cancelar.";
            return;
        }
        if (grafo.cancelarRuta(codigo(origen), codigo(destino))) {
            mensaje = "Ruta " + codigo(origen) + " -> " + codigo(destino) + " cancelada.";
        }
        else {
            mensaje = "No hay ruta directa activa\n"
                + codigo(origen) + " -> " + codigo(destino) + ".";
        }
        break;

    case Accion::RESTAURAR:
        mensaje = "Rutas restauradas: " + to_string(grafo.restaurarRutas());
        break;

    case Accion::LIMPIAR:
        origen = -1;
        destino = -1;
        modo = Modo::NINGUNO;
        mostrandoAlcanzables = false;
        break;
    }

    recalcular();   // cualquier cambio vuelve a consultar al grafo
}

void Interfaz::recalcular() {
    resultado = ResultadoRuta();   // borra la ruta anterior

    if (modo != Modo::NINGUNO) {
        if (origen == -1 || destino == -1) {
            agregarLinea(mensaje, "Seleccione origen y destino.");
        }
        else {
            string o = codigo(origen);
            string d = codigo(destino);

            if (modo == Modo::ESCALAS)
                resultado = grafo.rutaMenosEscalas(o, d);
            else if (modo == Modo::RAPIDA)
                resultado = grafo.rutaOptima(o, d, Criterio::MINUTOS);
            else
                resultado = grafo.rutaOptima(o, d, Criterio::COSTO);

            if (!resultado.existe) {
                agregarLinea(mensaje, "No existe ruta de " + o + " a " + d + ".");
            }
        }
    }

    if (mostrandoAlcanzables) {
        if (origen == -1) mostrandoAlcanzables = false;
        else alcanzable = grafo.alcanzables(codigo(origen));
    }
}

void Interfaz::procesarEventos() {
    while (const std::optional evento = ventana.pollEvent()) {
        if (evento->is<sf::Event::Closed>()) {
            ventana.close();
        }
        else if (const auto* clic = evento->getIf<sf::Event::MouseButtonPressed>()) {
            if (clic->button == sf::Mouse::Button::Left) {
                manejarClic(clic->position);
            }
        }
    }
}

void Interfaz::manejarClic(sf::Vector2i pixel) {
    // Clic en el panel: revisar si cayó en algún botón.
    if (pixel.x >= ladoMapa) {
        sf::Vector2f p(static_cast<float>(pixel.x), static_cast<float>(pixel.y));
        for (const Boton& b : botones) {
            if (b.area.contains(p)) {
                ejecutarAccion(b.accion);
                return;
            }
        }
        return;
    }

    // Clic en el mapa: píxel -> coordenadas del archivo.
    sf::Vector2f punto = ventana.mapPixelToCoords(pixel, vistaMapa);
    int i = aeropuertoEn(punto);
    if (i == -1) return;

    if (origen == -1 || destino != -1) {
        origen = i;
        destino = -1;
    }
    else if (i != origen) {
        destino = i;
    }
    else {
        return;   // clic otra vez en el origen: no cambia nada
    }

    mensaje.clear();
    recalcular();   // si ya había un criterio elegido, la ruta se calcula sola
}

int Interfaz::aeropuertoEn(sf::Vector2f p) const {
    const float tolerancia = 12.f;

    for (int i = 0; i < grafo.cantidadAeropuertos(); i++) {
        sf::Vector2f a = posicion(grafo.getAeropuerto(i));
        float dx = p.x - a.x;
        float dy = p.y - a.y;
        if (dx * dx + dy * dy <= tolerancia * tolerancia) {
            return i;
        }
    }
    return -1;
}

void Interfaz::escribir(const string& texto, float x, float y,
    unsigned tam, sf::Color color) {
    sf::Text t(fuente, texto, tam);
    t.setFillColor(color);
    t.setPosition({ x, y });
    ventana.draw(t);
}

// Una línea gruesa es un rectángulo largo y delgado, rotado.
void Interfaz::dibujarLineaGruesa(sf::Vector2f a, sf::Vector2f b,
    float grosor, sf::Color color) {
    sf::Vector2f d = b - a;
    float largo = std::sqrt(d.x * d.x + d.y * d.y);

    sf::RectangleShape barra({ largo, grosor });
    barra.setOrigin({ 0.f, grosor / 2.f });                  // centrada a lo ancho
    barra.setPosition(a);
    barra.setRotation(sf::radians(std::atan2(d.y, d.x)));    // apunta hacia b
    barra.setFillColor(color);
    ventana.draw(barra);
}

// Pedacitos de línea gruesa con huecos entre ellos.
void Interfaz::dibujarLineaPunteada(sf::Vector2f a, sf::Vector2f b, sf::Color color) {
    sf::Vector2f d = b - a;
    float largo = std::sqrt(d.x * d.x + d.y * d.y);
    if (largo == 0.f) return;

    sf::Vector2f direccion = d / largo;   // vector de largo 1 hacia b
    const float trazo = 10.f;
    const float hueco = 7.f;

    for (float t = 0.f; t < largo; t += trazo + hueco) {
        float fin = min(t + trazo, largo);
        dibujarLineaGruesa(a + direccion * t, a + direccion * fin, 2.5f, color);
    }
}

void Interfaz::dibujarMapa() {
    ventana.setView(vistaMapa);
    int n = grafo.cantidadAeropuertos();

    // 1. Rutas activas, en gris.
    sf::VertexArray lineas(sf::PrimitiveType::Lines);
    sf::Color gris(175, 175, 175);
    for (int i = 0; i < n; i++) {
        sf::Vector2f desde = posicion(grafo.getAeropuerto(i));
        for (const Ruta& r : grafo.getRutas(i)) {
            sf::Vector2f hasta = posicion(grafo.getAeropuerto(r.destino));
            lineas.append(sf::Vertex{ desde, gris });
            lineas.append(sf::Vertex{ hasta, gris });
        }
    }
    ventana.draw(lineas);

    // 2. Rutas canceladas, punteadas en rojo.
    for (const RutaCancelada& c : grafo.getCanceladas()) {
        dibujarLineaPunteada(posicion(grafo.getAeropuerto(c.origen)),
            posicion(grafo.getAeropuerto(c.ruta.destino)),
            COLOR_CANCELADA);
    }

    // 3. Ruta resultante, gruesa en naranja.
    if (resultado.existe) {
        const vector<int>& camino = resultado.camino;
        for (size_t k = 0; k + 1 < camino.size(); k++) {
            dibujarLineaGruesa(posicion(grafo.getAeropuerto(camino[k])),
                posicion(grafo.getAeropuerto(camino[k + 1])),
                4.f, COLOR_RUTA);
        }
    }

    // 4. Aeropuertos encima de todo.
    sf::CircleShape punto(RADIO);
    punto.setOrigin({ RADIO, RADIO });

    for (int i = 0; i < n; i++) {
        const Aeropuerto& a = grafo.getAeropuerto(i);

        sf::Color color(180, 30, 30);
        if (mostrandoAlcanzables) {
            color = alcanzable[i] ? COLOR_ALCANZABLE : COLOR_NO_ALCANZABLE;
        }
        if (i == origen) color = COLOR_ORIGEN;
        if (i == destino && !mostrandoAlcanzables) color = COLOR_DESTINO;

        punto.setFillColor(color);
        punto.setPosition(posicion(a));
        ventana.draw(punto);

        escribir(a.codigo, a.x + 8.f, a.y - 18.f, 14, sf::Color::Black);
    }
}

void Interfaz::dibujarBotones() {
    for (const Boton& b : botones) {
        // El botón del modo actual se pinta resaltado.
        bool activo =
            (b.accion == Accion::ESCALAS && modo == Modo::ESCALAS) ||
            (b.accion == Accion::RAPIDA && modo == Modo::RAPIDA) ||
            (b.accion == Accion::BARATA && modo == Modo::BARATA) ||
            (b.accion == Accion::ALCANZABLES && mostrandoAlcanzables);

        sf::RectangleShape rect(b.area.size);
        rect.setPosition(b.area.position);
        rect.setFillColor(activo ? COLOR_RUTA : sf::Color(60, 75, 105));
        rect.setOutlineThickness(1.f);
        rect.setOutlineColor(sf::Color(120, 135, 165));
        ventana.draw(rect);

        escribir(b.texto, b.area.position.x + 10.f, b.area.position.y + 7.f,
            14, sf::Color::White);
    }
}

void Interfaz::dibujarPanel() {
    ventana.setView(ventana.getDefaultView());

    sf::RectangleShape fondo({ anchoPanel, ladoMapa });
    fondo.setPosition({ ladoMapa, 0.f });
    fondo.setFillColor(sf::Color(30, 40, 60));
    ventana.draw(fondo);

    float x = ladoMapa + 20.f;
    sf::Color blanco = sf::Color::White;
    sf::Color tenue(170, 180, 200);
    sf::Color amarillo(250, 210, 80);

    escribir("PLANIFICADOR DE VUELOS", x, 20.f, 20, blanco);

    string txtOrigen = "(clic en el mapa)";
    if (origen != -1)
        txtOrigen = codigo(origen) + " - " + sinGuiones(grafo.getAeropuerto(origen).ciudad);
    string txtDestino = "(clic en el mapa)";
    if (destino != -1)
        txtDestino = codigo(destino) + " - " + sinGuiones(grafo.getAeropuerto(destino).ciudad);

    escribir("Origen:  " + txtOrigen, x, 70.f, 16, blanco);
    escribir("Destino: " + txtDestino, x, 100.f, 16, blanco);

    dibujarBotones();

    float y = 320.f;   // debajo de los botones

    // Resultado de la ruta
    if (resultado.existe) {
        string titulo = "Ruta mas barata";
        if (modo == Modo::ESCALAS) titulo = "Ruta con menos escalas";
        if (modo == Modo::RAPIDA)  titulo = "Ruta mas rapida";
        escribir(titulo, x, y, 17, COLOR_RUTA);
        y += 28.f;

        const vector<int>& camino = resultado.camino;
        escribir(unirCodigos(camino), x, y, 15, blanco);
        y += 22.f * ((camino.size() + 4) / 5) + 8.f;   // una línea cada 5 códigos

        escribir("Vuelos:  " + to_string(camino.size() - 1), x, y, 15, blanco);
        y += 24.f;
        escribir("Minutos: " + formatoMinutos(resultado.totalMinutos), x, y, 15, blanco);
        y += 24.f;
        escribir("Costo:   " + formatoCosto(resultado.totalCosto), x, y, 15, blanco);
        y += 34.f;
    }

    // Alcanzables
    if (mostrandoAlcanzables) {
        vector<int> no;
        int cantidadSi = 0;
        for (int i = 0; i < grafo.cantidadAeropuertos(); i++) {
            if (i == origen) continue;
            if (alcanzable[i]) cantidadSi++;
            else no.push_back(i);
        }

        escribir("Alcanzables desde " + codigo(origen) + ": " + to_string(cantidadSi),
            x, y, 16, COLOR_ALCANZABLE);
        y += 26.f;
        escribir("No alcanzables (" + to_string(no.size()) + "):", x, y, 16, blanco);
        y += 24.f;

        string lista = no.empty() ? "ninguno" : unirCodigos(no);
        replace(lista.begin(), lista.end(), '>', ',');   // aquí no es una ruta
        escribir(lista, x, y, 15, blanco);
        y += 22.f * ((no.size() + 4) / 5 + 1) + 8.f;
    }

    // Mensajes y avisos
    if (!mensaje.empty()) {
        escribir(mensaje, x, y, 15, amarillo);
    }

    // Leyenda
    escribir("Verde: origen   Azul: destino\n"
        "Naranja: ruta   Rojo punteado: cancelada\n"
        "Celeste / gris: alcanzable / no",
        x, ladoMapa - 75.f, 13, tenue);
}