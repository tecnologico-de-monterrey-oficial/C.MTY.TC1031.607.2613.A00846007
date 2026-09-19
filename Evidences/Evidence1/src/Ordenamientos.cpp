#include "Ordenamientos.hpp"

#include <stdexcept>

using namespace std;

string nombreAlgoritmo(Algoritmo algoritmo) {
    switch (algoritmo) {
        case Algoritmo::Insercion: return "Insercion";
        case Algoritmo::Seleccion: return "Seleccion";
        case Algoritmo::Burbuja: return "Burbuja";
        case Algoritmo::Merge: return "Merge";
        case Algoritmo::Quick: return "Quick";
    }

    throw std::invalid_argument("Algoritmo no valido");
}

void ordenar(vector<Registro>& registros, Algoritmo algoritmo) {
    switch (algoritmo) {
        case Algoritmo::Insercion:
        case Algoritmo::Seleccion:
        case Algoritmo::Burbuja:
        case Algoritmo::Merge:
        case Algoritmo::Quick:
            return;
    }
}

bool estaOrdenado(const vector<Registro>& registros) {
    for (size_t i = 1; i < registros.size(); ++i) {
        if (compararRegistros(registros[i], registros[i - 1])) {
            return false;
        }
    }

    return true;
}