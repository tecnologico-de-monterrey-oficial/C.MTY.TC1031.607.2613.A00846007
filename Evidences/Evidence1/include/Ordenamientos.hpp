#pragma once

#include "Registro.hpp"

#include <string>
#include <vector>

using namespace std;

enum class Algoritmo {
    Insercion,
    Seleccion,
    Burbuja,
    Merge,
    Quick
};

string nombreAlgoritmo(Algoritmo algoritmo);
void ordenar(vector<Registro>& registros, Algoritmo algoritmo);
bool estaOrdenado(const vector<Registro>& registros);