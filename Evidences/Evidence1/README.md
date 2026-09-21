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

Se implementó un menú interactivo.
Se permite seleccionar cualquiera de los dos archivos
Se permite seleccionar cualquiera de los siete algoritmos
Se agregó la predicción y justificación antes de cada corrida
Se agregó la medición del tiempo de ejecución
Se agregó la complejidad teórica de cada algoritmo
Se generaron output607.txt e historial607.txt
Se implementó la búsqueda binaria por rango
Se generó range607.txt
Se documentó el manejo de límites inclusivos y timestamps duplicados
Se completaron las 14 combinaciones de algoritmo y archivo
Se probaron rangos con resultados, rangos vacíos y fechas fuera del periodo de los registros

Instrucciones para compilar:

Para compilar se tiene que primero poner el path de Evidence1
cd /Users/"USUARIO"/"DONDE ESTE EL REPO"/C.MTY.TC1031.607.2613.A00846007/Evidences/Evidence1

Luego se usa en la terminal
clang++ -std=c++17 src/main.cpp src/Registro.cpp src/Archivo.cpp src/Ordenamientos.cpp src/Busqueda.cpp -Iinclude -o build/evidence1

y luego se pone
./build/evidence1

Estado de la evidencia:

Ahora el programa permite seleccionar un archivo y un algoritmo, solicita una predicción y su justificación, mide el tiempo de ejecución, muestra la complejidad teórica y genera output607.txt e historial607.txt

También permite buscar un rango de fechas mediante búsqueda binaria y genera range607.txt. Los límites del rango son inclusivos y los timestamps duplicados se conservan como registros individuales

Se completaron las 14 combinaciones de algoritmo y archivo. Los resultados y tiempos están registrados en historial607.txt

Aún está pendiente:

- Completar EvidenciasPruebas.pdf
- Completar ReflexEvidencia1.pdf
- Grabar el video explicativo
- Agregar el enlace del video al README

Uso de IA
Se utilizó inteligencia artificial como apoyo durante el desarrollo del proyecto. La IA se utilizó para explicar errores de compilación, revisar la organización de archivos .cpp y .hpp, y explicar como adaptar los algoritmos de ordenamiento para trabajar con registros y revisar la implementación de búsqueda binaria

Algunos prompts utilizados fueron:

1. “¿Cómo puedo adaptar los algoritmos de ordenamiento de mi Actividad 1.5 para ordenar registros de logs por fecha y hora?”

2. “Revisa mi Ordenamientos.cpp y dime qué errores tiene al trabajar con vector<Registro>.”

3. “¿Cómo puedo implementar una búsqueda binaria por rango que incluya correctamente timestamps duplicados?”

La IA no generó el proyecto completo de una sola vez. Las sugerencias fueron revisadas, adaptadas, compiladas y probadas manualmente

Durante la revisión se detectó un error en una versión del algoritmo Selection Sort. La condición utilizaba una comparación incorrecta con la posición 1, cuando debía comparar la posición del elemento mínimo con la posición actual i. Esto podía provocar intercambios incorrectos y afectar el ordenamiento. La condición se corrigió para utilizar menor != i

También se detectó que inicialmente se habían considerado únicamente cinco algoritmos, aunque la Actividad 1.5 contenía siete. Después de comparar el código con la actividad original, se agregaron Swap Sort y Shell Sort
