Evidencia 1 - Avance 6

Ian Armando Borde Escobar
Matricula: A00846007

Descripcion:

Este proyecto procesa registros de eventos almacenados en la carpeta data, son dos archivos logs en txt, el programa convierte sus fechas a un formato comparable y permite ordenar los registros cronologicamente mediante diferentes algoritmos

Archivos de entrada: log607-1.txt y log607-2.txt, -1 es un archivo desordenado y el -2 es un archivo casi ordenado

El registro tiene el siguiente formato:
Mes Día Año Hora Dirección IP Mensaje

y un ejemplo:
Mar 11 2025 05:05:17 10.14.211.203 Broken authentication and session management

La estructura del proyecto esta basada en la estructura recomendada en la actividad de canvas
Evidencia1
    build
    data
        log607-1.txt
        log607-2.txt
    docs
    include
        Archivo.hpp
        Busqueda.hpp
        Ordenamientos.hpp
        Registro.hpp
    out
    scripts
    src
        Archivo.cpp
        Busqueda.cpp
        main.cpp
        Ordenamientos.cpp
        Registro.cpp

Avances:
Se creó la estructura inicial del proyecto
Se implementó la lectura de archivos
Se implementó la conversión de fechas a formato comparable
Se conserva la línea original de cada registro
Se implementó la comparación cronológica
Se implementó la validación del orden de los registros
Se implementaron siete algoritmos de ordenamiento:
- Swap Sort
- Selection Sort
- Bubble Sort
- Insertion Sort
- Merge Sort
- Quick Sort
- Shell Sort
Se verificó que los siete algoritmos ordenan correctamente log607-1.txt
Se implementó un menú interactivo
Se permite seleccionar cualquiera de los dos archivos
Se permite seleccionar cualquiera de los siete algoritmos
Se agregó la predicción y justificación antes de cada corrida
Se agregó la medición del tiempo de ejecución
Se agregó la complejidad teórica de cada algoritmo
Se generó output607.txt con los registros ordenados
Se generó historial607.txt con los resultados de las corridas
Se probaron Swap Sort con log607-1.txt e Insertion Sort con log607-2.txt
Se integró el menú principal
Se permite seleccionar el archivo y el algoritmo
Se agregó la predicción y justificación antes de cada corrida
Se agregó la medición del tiempo y la complejidad teórica
Se generaron output607.txt e historial607.txt
Se integró la búsqueda binaria por rango
Se generó range607.txt
Se documentó el manejo de límites inclusivos y timestamps duplicados

Instrucciones para compilar:

Para compilar se tiene que primero poner el path de Evidence1
cd /Users/"USUARIO"/"DONDE ESTE EL REPO"/C.MTY.TC1031.607.2613.A00846007/Evidences/Evidence1

Luego se usa en la terminal
clang++ -std=c++17 src/main.cpp src/Registro.cpp src/Archivo.cpp src/Ordenamientos.cpp src/Busqueda.cpp -Iinclude -o build/evidence1

y luego se pone
./build/evidence1

Estado de la evidencia:

Ahora el programa permite seleccionar un archivo y un algoritmo, solicita una predicción y su justificación, mide el tiempo de ejecución, muestra la complejidad teórica y genera output607.txt e historial607.txt. Se realizaron pruebas con ambos archivos y los registros quedaron ordenados correctamente.

Se probó Shell Sort con el archivo log607-1.txt y se verificó que los registros quedaran ordenados correctamente. También se realizó una búsqueda por rango sobre el resultado ordenado y se generó range607.txt

Aun esta pendiente por implementar
- Pruebas completas de los siete algoritmos con ambos archivos
- Casos de prueba de rangos vacíos, fechas inválidas y timestamps duplicados
- Documento de evidencias
- Documento de reflexión
- Video explicativo

Uso de IA
La IA se utilizó como apoyo para revisar errores de compilación, explicar la organización de archivos .cpp y .hpp  y explicar como adaptar los algoritmos de ordenamiento para trabajar con los registros de logs
