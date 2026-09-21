#include "Archivo.hpp"
#include "Busqueda.hpp"
#include "Ordenamientos.hpp"

#include <chrono>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

using namespace std;

string obtenerMejorCaso(Algoritmo algoritmo) {
    switch (algoritmo) {
        case Algoritmo::Swap:
            return "O(n^2)";
        case Algoritmo::Seleccion:
            return "O(n^2)";
        case Algoritmo::Burbuja:
            return "O(n)";
        case Algoritmo::Insercion:
            return "O(n)";
        case Algoritmo::Merge:
            return "O(n log n)";
        case Algoritmo::Quick:
            return "O(n log n)";
        case Algoritmo::Shell:
            return "O(n log n)";
    }

    return "No definida";
}

string obtenerPeorCaso(Algoritmo algoritmo) {
    switch (algoritmo) {
        case Algoritmo::Swap:
            return "O(n^2)";
        case Algoritmo::Seleccion:
            return "O(n^2)";
        case Algoritmo::Burbuja:
            return "O(n^2)";
        case Algoritmo::Insercion:
            return "O(n^2)";
        case Algoritmo::Merge:
            return "O(n log n)";
        case Algoritmo::Quick:
            return "O(n^2)";
        case Algoritmo::Shell:
            return "O(n^2)";
    }

    return "No definida";
}

void mostrarAlgoritmos() {
    cout << "Seleccione un algoritmo:\n";
    cout << "1. Swap Sort\n";
    cout << "2. Selection Sort\n";
    cout << "3. Bubble Sort\n";
    cout << "4. Insertion Sort\n";
    cout << "5. Merge Sort\n";
    cout << "6. Quick Sort\n";
    cout << "7. Shell Sort\n";
}

Algoritmo seleccionarAlgoritmo(int opcion) {
    vector<Algoritmo> algoritmos = {
        Algoritmo::Swap,
        Algoritmo::Seleccion,
        Algoritmo::Burbuja,
        Algoritmo::Insercion,
        Algoritmo::Merge,
        Algoritmo::Quick,
        Algoritmo::Shell
    };

    return algoritmos[opcion - 1];
}

void guardarHistorial(
    const string& ruta,
    Algoritmo algoritmo,
    size_t cantidad,
    long long tiempo,
    const string& prediccion,
    const string& justificacion,
    const string& coincidencia
) {
    ofstream historial("out/historial607.txt", ios::app);

    if (!historial) {
        return;
    }

    historial << "Algoritmo: "
              << nombreAlgoritmo(algoritmo) << '\n';
    historial << "Archivo: " << ruta << '\n';
    historial << "Registros: " << cantidad << '\n';
    historial << "Tiempo: " << tiempo << " microsegundos\n";
    historial << "Mejor caso: "
              << obtenerMejorCaso(algoritmo) << '\n';
    historial << "Peor caso: "
              << obtenerPeorCaso(algoritmo) << '\n';
    historial << "Prediccion: " << prediccion << '\n';
    historial << "Justificacion: " << justificacion << '\n';
    historial << "Coincidencia: " << coincidencia << '\n';
    historial << "-----------------------------\n";
}

int main() {
    vector<Registro> registrosOrdenados;
    string archivoActual;
    bool hayOrdenamiento = false;
    int opcionMenu;

    do {
        cout << "Menu principal\n";
        cout << "1. Ordenar archivo\n";
        cout << "2. Buscar rango\n";
        cout << "3. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcionMenu;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada invalida.\n";
            continue;
        }

        if (opcionMenu == 1) {
            int opcionArchivo;
            int opcionAlgoritmo;
            string prediccion;
            string justificacion;
            string coincidencia;
            string ruta;

            cout << "Seleccione el archivo:\n";
            cout << "1. log607-1.txt desordenado\n";
            cout << "2. log607-2.txt casi ordenado\n";
            cout << "Opcion: ";
            cin >> opcionArchivo;

            if (opcionArchivo == 1) {
                ruta = "data/log607-1.txt";
            } else if (opcionArchivo == 2) {
                ruta = "data/log607-2.txt";
            } else {
                cout << "Archivo invalido.\n";
                continue;
            }

            mostrarAlgoritmos();
            cout << "Opcion: ";
            cin >> opcionAlgoritmo;

            if (opcionAlgoritmo < 1 || opcionAlgoritmo > 7) {
                cout << "Algoritmo invalido.\n";
                continue;
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            Algoritmo algoritmo = seleccionarAlgoritmo(opcionAlgoritmo);

            cout << "Escriba su prediccion de velocidad: ";
            getline(cin, prediccion);

            cout << "Justifique su prediccion: ";
            getline(cin, justificacion);

            vector<Registro> registros = leerArchivo(ruta);

            if (registros.empty()) {
                cout << "No se pudieron leer registros.\n";
                continue;
            }

            auto inicio = chrono::high_resolution_clock::now();

            ordenar(registros, algoritmo);

            auto final = chrono::high_resolution_clock::now();

            long long tiempo =
                chrono::duration_cast<chrono::microseconds>(
                    final - inicio
                ).count();

            bool ordenCorrecto = estaOrdenado(registros);

            cout << "Resultado\n";
            cout << "Algoritmo: "
                 << nombreAlgoritmo(algoritmo) << '\n';
            cout << "Archivo: " << ruta << '\n';
            cout << "Registros: " << registros.size() << '\n';
            cout << "Tiempo: " << tiempo
                 << " microsegundos\n";
            cout << "Mejor caso: "
                 << obtenerMejorCaso(algoritmo) << '\n';
            cout << "Peor caso: "
                 << obtenerPeorCaso(algoritmo) << '\n';
            cout << "Prediccion: " << prediccion << '\n';
            cout << "Justificacion: "
                 << justificacion << '\n';

            if (ordenCorrecto) {
                cout << "Resultado: ordenamiento correcto\n";
            } else {
                cout << "Resultado: error en el ordenamiento\n";
            }

            cout << "¿Coincidio con la prediccion? ";
            getline(cin, coincidencia);

            escribirArchivo("out/output607.txt", registros);

            guardarHistorial(
                ruta,
                algoritmo,
                registros.size(),
                tiempo,
                prediccion,
                justificacion,
                coincidencia
            );

            registrosOrdenados = registros;
            archivoActual = ruta;
            hayOrdenamiento = ordenCorrecto;

            cout << "Se genero out/output607.txt\n";
            cout << "Se actualizo out/historial607.txt\n";
        } else if (opcionMenu == 2) {
            if (!hayOrdenamiento) {
                cout << "Primero debe ordenar un archivo.\n";
                continue;
            }

            string inicio;
            string fin;

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Ingrese fecha y hora inicial (AAAA-MM-DD HH:MM:SS): ";
            getline(cin, inicio);

            cout << "Ingrese fecha y hora final (AAAA-MM-DD HH:MM:SS): ";
            getline(cin, fin);

            if (inicio > fin) {
                cout << "El rango es invalido.\n";
                continue;
            }

            vector<Registro> resultado =
                buscarRango(registrosOrdenados, inicio, fin);

            escribirArchivo("out/range607.txt", resultado);

            cout << "Archivo utilizado: " << archivoActual << '\n';
            cout << "Registros encontrados: "
                 << resultado.size() << '\n';
            cout << "Se genero out/range607.txt\n";
            cout << "Los limites del rango son inclusivos.\n";
            cout << "Los timestamps duplicados se incluyen una sola vez por registro.\n";
        } else if (opcionMenu != 3) {
            cout << "Opcion invalida.\n";
        }

    } while (opcionMenu != 3);

    cout << "Programa terminado.\n";

    return 0;
}