#pragma once

#include <string>

using namespace std;

struct Registro {
    string lineaOriginal;
    string timestamp;
};

bool convertirLinea(const string& linea, Registro& registro);
bool compararRegistros(const Registro& izquierda, const Registro& derecha);