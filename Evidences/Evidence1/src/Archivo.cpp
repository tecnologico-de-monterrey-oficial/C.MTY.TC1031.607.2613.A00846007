#include "Archivo.hpp"

#include <fstream>

using namespace std;

vector<Registro> leerArchivo(const string& ruta) {
    vector<Registro> registros;
    ifstream archivo(ruta);
    string linea;

    if (!archivo) {
        return registros;
    }

    while (getline(archivo, linea)) {
        Registro registro;

        if (convertirLinea(linea, registro)) {
            registros.push_back(registro);
        }
    }

    return registros;
}

bool escribirArchivo(const string& ruta, const vector<Registro>& registros) {
    ofstream archivo(ruta);

    if (!archivo) {
        return false;
    }

    for (const Registro& registro : registros) {
        archivo << registro.lineaOriginal << '\n';
    }

    return true;
}