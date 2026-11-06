# Planificador de rutas aéreas — Proyecto II

**EIF207 Estructuras de Datos · Universidad Nacional de Costa Rica · II Ciclo 2026**
Estudiante: Karen Zeledón Alvarez

Planificador de vuelos entre aeropuertos de América. Cada aeropuerto es un vértice de un
grafo dirigido y ponderado (lista de adyacencia); cada ruta es una arista con dos pesos:
duración en minutos y costo en dólares. El programa calcula la ruta con menos escalas (BFS),
la más rápida y la más barata (un mismo Dijkstra parametrizado por el peso), los destinos
alcanzables (DFS), y permite cancelar y restaurar rutas. La ruta elegida se anima en un mapa.

## Tecnologías

| | |
|---|---|
| Lenguaje | C++17 |
| Entorno | Visual Studio 2022 (plataforma x64) |
| Biblioteca gráfica | SFML 3.0.2 (módulos graphics, window y system) |
| Colecciones | Solo la STL: `vector`, `queue`, `priority_queue`, `unordered_map` |

No se usan bibliotecas de grafos. BFS, DFS y Dijkstra están implementados a mano.

## Estructura del código

| Archivo | Contenido |
|---|---|
| `Aeropuerto.h` | Estructuras `Aeropuerto` y `Ruta` |
| `Grafo.h` / `Grafo.cpp` | Grafo, carga de archivos, consultas, BFS, Dijkstra, DFS, cancelar/restaurar rutas |
| `Interfaz.h` / `Interfaz.cpp` | Ventana SFML: mapa, panel, botones, ruta resaltada, alcanzables, rutas canceladas y animación |
| `mainConsola.h` / `mainConsola.cpp` | Menú de texto usado como prototipo y para pruebas |
| `main.cpp` | Carga los archivos y abre la interfaz |
| `datos/aeropuertos.txt`, `datos/rutas.txt` | Datos de entrada |
| `datos/comic.ttf` | Fuente para los textos de la ventana |

## Instalar SFML

1. Descargar **SFML 3.0.2 para Visual Studio 2022, 64 bits** (`SFML-3.0.2-Windows.VS2022.x64.zip`)
   desde https://www.sfml-dev.org/download.
2. Descomprimir en `C:\SFML-3.0.2`, de modo que existan `C:\SFML-3.0.2\include`, `lib` y `bin`.

El proyecto ya está configurado para esa ruta. Si SFML se instala en otra carpeta, cambiarla en
**Propiedades del proyecto** (Todas las configuraciones, x64):

- C/C++ → General → Directorios de inclusión adicionales: `<ruta>\include`
- Vinculador → General → Directorios de bibliotecas adicionales: `<ruta>\lib`
- Eventos de compilación → Evento posterior a la compilación: `xcopy /y /d "<ruta>\bin\*.dll" "$(OutDir)"`

Bibliotecas enlazadas:

- Debug: `sfml-graphics-d.lib; sfml-window-d.lib; sfml-system-d.lib`
- Release: `sfml-graphics.lib; sfml-window.lib; sfml-system.lib`

## Compilar y ejecutar

1. Abrir la solución `.sln` en Visual Studio 2022.
2. Elegir la plataforma **x64** y la configuración **Debug** o **Release**.
3. Compilar → Recompilar solución. El evento posterior a la compilación copia las DLL de SFML
   junto al `.exe`.
4. Ejecutar con **F5** o **Ctrl+F5**.

El programa lee los archivos desde la ruta relativa `datos/`. Desde Visual Studio funciona
porque el directorio de trabajo es la carpeta del proyecto. Para ejecutar el `.exe` fuera de
Visual Studio, la carpeta `datos/` debe estar al lado del `.exe`, junto con las DLL de SFML.

## Probar con otros archivos

Todo se lee de los archivos; no hay datos escritos en el código. Para usar otros datos,
reemplazar `datos/aeropuertos.txt` y `datos/rutas.txt` por archivos con el mismo formato:

```
aeropuertos.txt:  cantidad, luego por línea: codigo x y ciudad pais
rutas.txt:        cantidad, luego por línea: origen destino minutos costo
```

Las coordenadas x, y son de una ventana de 1000 × 1000 (origen arriba a la izquierda).
Si un archivo tiene errores (códigos duplicados, rutas hacia códigos inexistentes, valores
negativos o líneas incompletas), el programa muestra el error en la consola y no arranca.

## Uso de la interfaz

| Acción | Cómo |
|---|---|
| Elegir origen y destino | Clic en un aeropuerto (origen, verde) y luego en otro (destino, azul). Un tercer clic elige un nuevo origen. |
| Calcular ruta | Botones *Menos escalas*, *Mas rapida* o *Mas barata*. La ruta se resalta en naranja y el panel muestra secuencia, vuelos, minutos y costo. |
| Animar | *Animar* recorre la ruta tramo por tramo, con una pausa en cada escala y los acumulados en el panel. *Pausar* / *Continuar* y *Reiniciar*. |
| Alcanzables | Con un origen elegido, *Alcanzables* pinta en celeste los alcanzables y en gris los no alcanzables. |
| Cancelar ruta | Elegir origen y destino de una ruta directa y presionar *Cancelar ruta*. Se dibuja punteada en rojo y todas las consultas se recalculan sin ella. |
| Restaurar | *Restaurar rutas* devuelve todas las rutas canceladas. Los archivos nunca se modifican. |
| Limpiar | Borra la selección y los resultados. |

## Menú de consola (pruebas)

En `main.cpp` se puede descomentar `mainConsola(grafo);` y comentar las tres líneas de la
interfaz para usar el menú de texto. Incluye consulta de aeropuerto, las tres rutas,
alcanzables, aeropuertos que no llegan a un destino, cancelar/restaurar y rutas críticas.
La versión entregada abre la interfaz gráfica.
