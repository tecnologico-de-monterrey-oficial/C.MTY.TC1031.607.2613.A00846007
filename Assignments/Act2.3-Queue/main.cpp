// Ian Armando Borde Escobar - A00846007

#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include "Queue.h"

bool leerEntero(const std::string& mensaje, int minimo, int maximo, int& valor) {
    std::string linea;
    while (true) {
        std::cout << mensaje;
        if (!std::getline(std::cin, linea)) return false;
        std::istringstream entrada(linea);
        char extra;
        if ((entrada >> valor) && !(entrada >> extra)
            && valor >= minimo && valor <= maximo) return true;
        std::cout << "Entrada invalida. Ingresa un entero entre "
                  << minimo << " y " << maximo << ".\n";
    }
}

int main() {
    Queue<Cliente> fila;
    int opcion;
    while (true) {
        std::cout << "\n TAQUILLA DE BOLETOS \n"
                  << "1. Llegada de un nuevo cliente\n"
                  << "2. Atender al siguiente cliente\n"
                  << "3. Ver al siguiente cliente\n"
                  << "4. Mostrar cuantas personas hay en la fila\n"
                  << "5. Salir\n";
        if (!leerEntero("Selecciona una opcion: ", 1, 5, opcion)) break;
        try {
            switch (opcion) {
                case 1: {
                    Cliente cliente;
                    do {
                        std::cout << "Nombre del cliente: ";
                        if (!std::getline(std::cin, cliente.nombre)) return 0;
                        if (cliente.nombre.find_first_not_of(" \t\r") == std::string::npos)
                            std::cout << "El nombre no puede estar vacio.\n";
                    } while (cliente.nombre.find_first_not_of(" \t\r") == std::string::npos);
                    if (!leerEntero("Cantidad de boletos: ", 1,
                                    std::numeric_limits<int>::max(), cliente.boletos)) return 0;
                    fila.push(cliente);
                    std::cout << cliente.nombre << " se agrego a la fila.\n";
                    break;
                }
                case 2: {
                    Cliente cliente = fila.pop();
                    std::cout << "Atendiendo a " << cliente.nombre << ": "
                              << cliente.boletos << " boletos.\n";
                    break;
                }
                case 3: {
                    Cliente cliente = fila.front();
                    std::cout << "Siguiente cliente: " << cliente.nombre << ": "
                              << cliente.boletos << " boletos.\n";
                    break;
                }
                case 4:
                    std::cout << "Personas en la fila: " << fila.size() << '\n';
                    break;
                case 5:
                    std::cout << "Programa finalizado.\n";
                    return 0;
            }
        } catch (const char* mensaje) {
            std::cout << mensaje << '\n';
        }
    }
    return 0;
}