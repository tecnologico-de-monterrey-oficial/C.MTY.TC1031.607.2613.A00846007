#include "Archivo.hpp"
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
    cout << "\nSeleccione un algoritmo:\n";
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

int main() {
    bool continuar = true;

    while (continuar) {
        int opcionArchivo;
        int opcionAlgoritmo;
        string prediccion;
        string justificacion;
        string coincidencia;
        string ruta;

        cout << "Menu principal\n";
        cout << "1. Ejecutar ordenamiento\n";
        cout << "2. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcionArchivo;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada invalida.\n";
            continue;
        }

        if (opcionArchivo == 2) {
            continuar = false;
            cout << "Programa terminado.\n";
            continue;
        }

        if (opcionArchivo != 1) {
            cout << "Opcion invalida.\n";
            continue;
        }

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

        long long tiempo = chrono::duration_cast<chrono::microseconds>(
            final - inicio
        ).count();

        bool ordenCorrecto = estaOrdenado(registros);

        cout << "Resultado\n";
        cout << "Algoritmo: " << nombreAlgoritmo(algoritmo) << endl;
        cout << "Archivo: " << ruta << endl;
        cout << "Registros: " << registros.size() << endl;
        cout << "Tiempo: " << tiempo << " microsegundos" << endl;
        cout << "Mejor caso: " << obtenerMejorCaso(algoritmo) << endl;
        cout << "Peor caso: " << obtenerPeorCaso(algoritmo) << endl;
        cout << "Prediccion: " << prediccion << endl;
        cout << "Justificacion: " << justificacion << endl;

        if (ordenCorrecto) {
            cout << "Resultado: ordenamiento correcto" << endl;
        } else {
            cout << "Resultado: error en el ordenamiento" << endl;
        }

        cout << "¿Coincidio con la prediccion? ";
        getline(cin, coincidencia);

        bool archivoGuardado = escribirArchivo(
            "out/output607.txt",
            registros
        );

        if (archivoGuardado) {
            cout << "Se genero out/output607.txt" << endl;
        } else {
            cout << "No se pudo generar el archivo de salida." << endl;
        }

        ofstream historial("out/historial607.txt", ios::app);

        if (historial) {
            historial << "Algoritmo: "
                      << nombreAlgoritmo(algoritmo) << '\n';
            historial << "Archivo: " << ruta << '\n';
            historial << "Registros: " << registros.size() << '\n';
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

        char respuesta;
        cout << "¿Desea realizar otra corrida? (s/n): ";
        cin >> respuesta;

        if (respuesta != 's' && respuesta != 'S') {
            continuar = false;
        }
    }

    return 0;
}