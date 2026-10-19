Ian Armando Borde Escobar A00846007

Para compilar:

Se necesita un compilador compatible con C++20

Entrar a Evidences con cd y luego a Evidence2:
cd Evidences/Evidence2

Usar:
g++ -std=c++20 -Wall -Wextra -Wpedantic src/main.cpp src/LogRecord.cpp -o logs
./logs

Archivos y fechas:

Archivos de entrada en data: log607-1.txt y log607-2.txt

Formato de los registros: Mmm DD AAAA HH:MM:SS IP descripción

Formato para buscar un día: Sep 14 2024

Archivo ordenado generado: out/output608.out

Uso de IA:

En esta actividad relacioné las estructuras de datos con tareas concretas de una aplicación, partí de estructuras que ya tenía, las adapté, preparé pruebas e integré el programa, la IA me ayudó con las validaciones, las búsquedas y las estadísticas, también vi que puede agregar funciones innecesarias, como las comprobaciones adicionales de orden y estabilidad, al comparar la propuesta con las instrucciones pedí retirar esos extras y conservé las verificaciones durante las pruebas y sin la ayuda de la IA habría dedicado más tiempo a consultar ejemplos y probar cada función y hacer validaciones