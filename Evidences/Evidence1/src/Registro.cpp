#include "Registro.hpp"

using namespace std;

bool compararRegistros(const Registro& izquierda, const Registro& derecha) {
    return izquierda.timestamp < derecha.timestamp;
}