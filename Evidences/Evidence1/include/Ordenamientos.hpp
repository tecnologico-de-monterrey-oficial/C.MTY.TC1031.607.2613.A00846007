#pragma once

#include "Registro.hpp"

#include <string>
#include <vector>

using namespace std;

enum class Algoritmo {
    Swap,
    Insercion,
    Seleccion,
    Burbuja,
    Merge,
    Quick,
    Shell
};

string nombreAlgoritmo(Algoritmo algoritmo);
void ordenar(vector<Registro>& registros, Algoritmo algoritmo);
bool estaOrdenado(const vector<Registro>& registros);