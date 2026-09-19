#pragma once

#include "Registro.hpp"

#include <string>
#include <vector>

using namespace std;

vector<Registro> leerArchivo(const string& ruta);
bool escribirArchivo(const string& ruta, const vector<Registro>& registros);