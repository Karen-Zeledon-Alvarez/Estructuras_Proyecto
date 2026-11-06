#include "Grafo.h"
#include <limits>
#include <iostream>
#include <fstream>
#include <queue>
#include <algorithm> 

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
    canceladas.clear();

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

const Ruta* Grafo::buscarRuta(int origen, int destino) const {
    for (const Ruta& r : adyacencia[origen]) {
        if (r.destino == destino) {
            return &r;
        }
    }
    return nullptr;
}

ResultadoRuta Grafo::construirResultado(int origen, int destino,
    const vector<int>& padre) const {
    ResultadoRuta r;
    r.existe = true;

    // Caminar hacia atrás
    for (int v = destino; v != -1; v = padre[v]) {
        r.camino.push_back(v);
    }
    reverse(r.camino.begin(), r.camino.end());

    // Sumar minutos y costo de cada arista
    for (size_t i = 0; i + 1 < r.camino.size(); i++) {
        const Ruta* tramo = buscarRuta(r.camino[i], r.camino[i + 1]);
        r.totalMinutos += tramo->minutos;
        r.totalCosto += tramo->costo;
        r.minutosTramo.push_back(tramo->minutos);
        r.costoTramo.push_back(tramo->costo);
    }
    return r;
}

ResultadoRuta Grafo::rutaMenosEscalas(const string& codOrigen,
    const string& codDestino) const {
    ResultadoRuta vacio;   // existe = false

    if (!existeAeropuerto(codOrigen) || !existeAeropuerto(codDestino)) {
        return vacio;
    }

    int origen = indices.at(codOrigen);
    int destino = indices.at(codDestino);
    int n = static_cast<int>(aeropuertos.size());

    vector<bool> visitado(n, false);
    vector<int> padre(n, -1);
    queue<int> cola;

    visitado[origen] = true;
    cola.push(origen);

    while (!cola.empty()) {
        int actual = cola.front();
        cola.pop();

        if (actual == destino) break;   // ya lo encontramos

        for (const Ruta& r : adyacencia[actual]) {
            if (!visitado[r.destino]) {
                visitado[r.destino] = true;   // se marca AL ENCOLAR
                padre[r.destino] = actual;
                cola.push(r.destino);
            }
        }
    }

    if (!visitado[destino]) {
        return vacio;   // nunca se llego a una ruta
    }
    return construirResultado(origen, destino, padre);
}

void Grafo::mostrarResultado(const ResultadoRuta& r) const {
    if (!r.existe) {
        cout << "No existe ruta.\n";
        return;
    }
    cout << "Ruta: ";
    for (size_t i = 0; i < r.camino.size(); i++) {
        cout << aeropuertos[r.camino[i]].codigo;
        if (i + 1 < r.camino.size()) cout << " -> ";
    }
    cout << "\nVuelos: " << r.camino.size() - 1
        << "\nMinutos totales: " << r.totalMinutos
        << "\nCosto total: $" << r.totalCosto << '\n';
}

double Grafo::peso(const Ruta& r, Criterio criterio) {
    if (criterio == Criterio::MINUTOS) {
        return r.minutos;
    }
    return r.costo;
}

ResultadoRuta Grafo::rutaOptima(const string& codOrigen,
    const string& codDestino,
    Criterio criterio) const {
    ResultadoRuta vacio;

    if (!existeAeropuerto(codOrigen) || !existeAeropuerto(codDestino)) {
        return vacio;
    }

    int origen = indices.at(codOrigen);
    int destino = indices.at(codDestino);
    int n = static_cast<int>(aeropuertos.size());

    const double INF = numeric_limits<double>::infinity();
    vector<double> dist(n, INF);
    vector<int> padre(n, -1);

    // Cola de prioridad de pares (distancia, aeropuerto).
    // greater<> hace que salga primero la MENOR distancia.
    using Par = pair<double, int>;
    priority_queue<Par, vector<Par>, greater<Par>> cola;

    dist[origen] = 0;
    cola.push({ 0, origen });

    while (!cola.empty()) {
        auto [d, u] = cola.top();
        cola.pop();

        // Entrada vieja: u ya se mejoró después de meter este par.
        if (d > dist[u]) continue;

        // Al sacarlo, su distancia es definitiva: podemos terminar.
        if (u == destino) break;

        for (const Ruta& r : adyacencia[u]) {
            double nueva = dist[u] + peso(r, criterio);

            if (nueva < dist[r.destino]) {      // relajación
                dist[r.destino] = nueva;
                padre[r.destino] = u;
                cola.push({ nueva, r.destino });
            }
        }
    }

    if (dist[destino] == INF) {
        return vacio;   // nunca se alcanzó
    }
    return construirResultado(origen, destino, padre);
}

void Grafo::dfs(int u, vector<bool>& visitado) const {
    visitado[u] = true;

    for (const Ruta& r : adyacencia[u]) {
        if (!visitado[r.destino]) {
            dfs(r.destino, visitado);
        }
    }
}

vector<bool> Grafo::alcanzables(const string& codOrigen) const {
    vector<bool> visitado(aeropuertos.size(), false);

    if (!existeAeropuerto(codOrigen)) {
        return visitado;   // todo en false
    }
    dfs(indices.at(codOrigen), visitado);
    return visitado;
}

void Grafo::mostrarAlcanzables(const string& codOrigen) const {
    vector<bool> visitado = alcanzables(codOrigen);
    int origen = indices.at(codOrigen);

    vector<string> si, no;
    for (size_t i = 0; i < aeropuertos.size(); i++) {
        if ((int)i == origen) continue;   // el origen no se lista
        if (visitado[i]) si.push_back(aeropuertos[i].codigo);
        else             no.push_back(aeropuertos[i].codigo);
    }

    cout << "\nAlcanzables desde " << codOrigen << " (" << si.size() << "): ";
    for (const string& c : si) cout << c << ' ';
    cout << "\nNo alcanzables (" << no.size() << "): ";
    for (const string& c : no) cout << c << ' ';
    if (no.empty()) cout << "ninguno";
    cout << '\n';
}

vector<int> Grafo::noLleganA(const string& codDestino) const {
    vector<int> resultado;
    if (!existeAeropuerto(codDestino)) return resultado;

    int destino = indices.at(codDestino);

    // Para cada aeropuerto, se hace un dfs y se revisa si toca el destino.
    for (size_t i = 0; i < aeropuertos.size(); i++) {
        if ((int)i == destino) continue;

        vector<bool> visitado(aeropuertos.size(), false);
        dfs((int)i, visitado);

        if (!visitado[destino]) {
            resultado.push_back((int)i);
        }
    }
    return resultado;
}

bool Grafo::cancelarRuta(const string& codOrigen, const string& codDestino) {
    if (!existeAeropuerto(codOrigen) || !existeAeropuerto(codDestino)) {
        return false;
    }

    int origen = indices.at(codOrigen);
    int destino = indices.at(codDestino);
    vector<Ruta>& lista = adyacencia[origen];   //modifica la real

    for (size_t i = 0; i < lista.size(); i++) {
        if (lista[i].destino == destino) {
            canceladas.push_back({ origen, lista[i] });   // guarda antes de borrar
            lista.erase(lista.begin() + i);
            return true;
        }
    }
    return false;   // esa ruta no existe
}

int Grafo::restaurarRutas() {
    int cantidad = static_cast<int>(canceladas.size());

    for (const RutaCancelada& c : canceladas) {
        adyacencia[c.origen].push_back(c.ruta);
    }
    canceladas.clear();
    return cantidad;
}

vector<pair<int, int>> Grafo::rutasCriticas(const string& codOrigen) {
    vector<pair<int, int>> criticas;
    if (!existeAeropuerto(codOrigen)) return criticas;

    int origen = indices.at(codOrigen);
    int n = static_cast<int>(aeropuertos.size());

    // Lo alcanzable con el grafo completo
    vector<bool> base = alcanzables(codOrigen);

    for (int u = 0; u < n; u++) {
        // Si u no es alcanzable
        if (!base[u]) continue;

        for (size_t k = 0; k < adyacencia[u].size(); k++) {
            // Quitar temporalmente la ruta k
            Ruta guardada = adyacencia[u][k];
            adyacencia[u].erase(adyacencia[u].begin() + k);

            vector<bool> visitado(n, false);
            dfs(origen, visitado);

            // Devolverla a la posición.
            adyacencia[u].insert(adyacencia[u].begin() + k, guardada);

            // aeropuerto que antes se alcanzaba dejó de alcanzarse
            for (int v = 0; v < n; v++) {
                if (base[v] && !visitado[v]) {
                    criticas.push_back({ u, guardada.destino });
                    break;
                }
            }
        }
    }
    return criticas;
}
