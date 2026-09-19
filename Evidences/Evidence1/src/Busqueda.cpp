#include "Busqueda.hpp"

using namespace std;

size_t primeraPosicionDesde(const vector<Registro>& registros, const string& timestamp) {
    size_t izquierda = 0;
    size_t derecha = registros.size();

    while (izquierda < derecha) {
        size_t medio = izquierda + (derecha - izquierda) / 2;

        if (registros[medio].timestamp < timestamp) {
            izquierda = medio + 1;
        } else {
            derecha = medio;
        }
    }

    return izquierda;
}

size_t primeraPosicionDespuesDe(const vector<Registro>& registros, const string& timestamp) {
    size_t izquierda = 0;
    size_t derecha = registros.size();

    while (izquierda < derecha) {
        size_t medio = izquierda + (derecha - izquierda) / 2;

        if (registros[medio].timestamp <= timestamp) {
            izquierda = medio + 1;
        } else {
            derecha = medio;
        }
    }

    return izquierda;
}

vector<Registro> buscarRango(
    const vector<Registro>& registros,
    const string& inicio,
    const string& fin
) {
    size_t primero = primeraPosicionDesde(registros, inicio);
    size_t ultimo = primeraPosicionDespuesDe(registros, fin);

    if (primero >= ultimo) {
        return {};
    }

    return vector<Registro>(registros.begin() + primero, registros.begin() + ultimo);
}