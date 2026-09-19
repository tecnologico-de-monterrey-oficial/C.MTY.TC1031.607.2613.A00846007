#pragma once

#include "Registro.hpp"

#include <string>
#include <vector>

using namespace std;

size_t primeraPosicionDesde(const vector<Registro>& registros, const string& timestamp);
size_t primeraPosicionDespuesDe(const vector<Registro>& registros, const string& timestamp);
vector<Registro> buscarRango(
    const vector<Registro>& registros,
    const string& inicio,
    const string& fin
);