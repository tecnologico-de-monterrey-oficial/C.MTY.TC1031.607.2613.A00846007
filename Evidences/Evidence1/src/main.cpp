#include "Archivo.hpp"
#include "Ordenamientos.hpp"

#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<Algoritmo> algoritmos = {
        Algoritmo::Swap,
        Algoritmo::Seleccion,
        Algoritmo::Burbuja,
        Algoritmo::Insercion,
        Algoritmo::Merge,
        Algoritmo::Quick,
        Algoritmo::Shell
    };

    for (Algoritmo algoritmo : algoritmos) {
        vector<Registro> registros = leerArchivo("data/log607-1.txt");

        ordenar(registros, algoritmo);

        cout << nombreAlgoritmo(algoritmo) << ": ";

        if (estaOrdenado(registros)) {
            cout << "ordenado correctamente" << endl;
        } else {
            cout << "error en el ordenamiento" << endl;
        }
    }

    return 0;
}