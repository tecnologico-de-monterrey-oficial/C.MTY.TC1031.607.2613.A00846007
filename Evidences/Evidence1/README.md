Evidencia 1 - Avance 4

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

Instrucciones para compilar:

Para compilar se tiene que primero poner el path de Evidence1
cd /Users/"USUARIO"/"DONDE ESTE EL REPO"/C.MTY.TC1031.607.2613.A00846007/Evidences/Evidence1

Luego se usa en la terminal
clang++ -std=c++17 src/main.cpp src/Registro.cpp src/Archivo.cpp src/Ordenamientos.cpp src/Busqueda.cpp 
-Iinclude -o build/evidence1

y luego se pone
./build/evidence1

Estado de la evidencia:

va bien, ahorita el programa prueba los sorts que implemente sobre log607-1.txt y verifica que los registros queden ordenados cronologicamente

Aun esta pendiente por implementar
- Menu interactivo
- Selección entre los dos archivos
- Medición de tiempos
- Predicción inicial del usuario
- Exportación de output607.txt
- Búsqueda por rango
- Exportación de range607.txt
- Pruebas completas con ambos archivos
- Documentos de evidencias y reflexión
- Video explicativo

Uso de IA
La IA se utilizó como apoyo para revisar errores de compilación, explicar la organización de archivos .cpp y .hpp  y explicar como adaptar los algoritmos de ordenamiento para trabajar con los registros de logs
