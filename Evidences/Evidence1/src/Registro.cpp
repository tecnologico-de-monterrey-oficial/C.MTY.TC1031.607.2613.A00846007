#include "Registro.hpp"

#include <iomanip>
#include <map>
#include <sstream>

using namespace std;

bool convertirLinea(const string& linea, Registro& registro) {
    string mes;
    string hora;
    int dia;
    int anio;

    stringstream entrada(linea);

    if (!(entrada >> mes >> dia >> anio >> hora)) {
        return false;
    }

    map<string, int> meses = {
        {"Jan", 1},
        {"Feb", 2},
        {"Mar", 3},
        {"Apr", 4},
        {"May", 5},
        {"Jun", 6},
        {"Jul", 7},
        {"Aug", 8},
        {"Sep", 9},
        {"Oct", 10},
        {"Nov", 11},
        {"Dec", 12}
    };

    if (meses.find(mes) == meses.end()) {
        return false;
    }

    if (dia < 1 || dia > 31 || anio < 1) {
        return false;
    }

    if (hora.size() != 8 || hora[2] != ':' || hora[5] != ':') {
        return false;
    }

    registro.lineaOriginal = linea;

    stringstream timestamp;
    timestamp << setfill('0')
              << setw(4) << anio << "-"
              << setw(2) << meses[mes] << "-"
              << setw(2) << dia << " "
              << hora;

    registro.timestamp = timestamp.str();

    return true;
}

bool compararRegistros(const Registro& izquierda, const Registro& derecha) {
    return izquierda.timestamp < derecha.timestamp;
}