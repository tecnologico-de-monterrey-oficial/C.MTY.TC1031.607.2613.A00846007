// Ian Armando Borde Escobar - A00846007

#include <iostream>
#include <sstream>
#include <string>
#include "Stack.h"

bool leerTexto(const std::string& mensaje, std::string& texto) {
    while (true) {
        std::cout << mensaje;
        if (!std::getline(std::cin, texto)) return false;
        if (texto.find_first_not_of(" \t\r") != std::string::npos) return true;
        std::cout << "El campo no puede estar vacio.\n";
    }
}

bool leerOpcion(int& opcion) {
    std::string linea;
    while (true) {
        std::cout << "Selecciona una opcion: ";
        if (!std::getline(std::cin, linea)) return false;
        std::istringstream entrada(linea);
        char extra;
        if ((entrada >> opcion) && !(entrada >> extra) && opcion >= 1 && opcion <= 5)
            return true;
        std::cout << "Entrada invalida. Ingresa un entero entre 1 y 5.\n";
    }
}

int main() {
    Stack<PaginaWeb> historial;
    int opcion;
    while (true) {
        std::cout << "\n HISTORIAL DE NAVEGACION \n"
                  << "1. Visitar una nueva pagina\n"
                  << "2. Retroceder a la pagina anterior\n"
                  << "3. Ver la pagina actual\n"
                  << "4. Mostrar cuantas paginas hay en el historial\n"
                  << "5. Salir\n";
        if (!leerOpcion(opcion)) break;
        try {
            switch (opcion) {
                case 1: {
                    PaginaWeb pagina;
                    if (!leerTexto("Titulo: ", pagina.titulo)) return 0;
                    if (!leerTexto("URL: ", pagina.url)) return 0;
                    historial.push(pagina);
                    std::cout << "Pagina visitada: " << pagina.titulo
                              << " (" << pagina.url << ").\n";
                    break;
                }
                case 2: {
                    PaginaWeb pagina = historial.pop();
                    std::cout << "Pagina cerrada: " << pagina.titulo
                              << " (" << pagina.url << ").\n";
                    if (!historial.empty()) {
                        PaginaWeb actual = historial.top();
                        std::cout << "Pagina actual: " << actual.titulo
                                  << " (" << actual.url << ").\n";
                    } else {
                        std::cout << "No hay paginas en el historial.\n";
                    }
                    break;
                }
                case 3: {
                    PaginaWeb pagina = historial.top();
                    std::cout << "Pagina actual: " << pagina.titulo
                              << " (" << pagina.url << ").\n";
                    break;
                }
                case 4:
                    std::cout << "Paginas en el historial: " << historial.size() << '\n';
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