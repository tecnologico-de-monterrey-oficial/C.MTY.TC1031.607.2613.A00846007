#include "Archivo.hpp"

#include <fstream>

using namespace std;

vector<Registro> leerArchivo(const string& ruta) {
    vector<Registro> registros;
    ifstream archivo(ruta);
    string linea;

    while (std::getline(archivo, linea)) {
        registros.push_back({linea, ""});
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