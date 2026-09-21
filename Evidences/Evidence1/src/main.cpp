#include "Archivo.hpp"

#include <iostream>

using namespace std;

void mostrarInformacion(const string& ruta) {
    vector<Registro> registros = leerArchivo(ruta);

    cout << "\nArchivo: " << ruta << endl;
    cout << "Registros leidos: " << registros.size() << endl;

    if (!registros.empty()) {
        cout << "Primer registro:" << endl;
        cout << registros.front().lineaOriginal << endl;
        cout << "Timestamp convertido: "
             << registros.front().timestamp << endl;

        cout << "Ultimo registro:" << endl;
        cout << registros.back().lineaOriginal << endl;
    }
}

int main() {
    mostrarInformacion("data/log607-1.txt");
    mostrarInformacion("data/log607-2.txt");

    return 0;
}