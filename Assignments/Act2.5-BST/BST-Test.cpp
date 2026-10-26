// Ian Armando Borde Escobar - A00846007

#include <iostream>
#include <sstream>
#include <string>
#include "BST.h"

bool readInteger(const std::string& prompt, int& value) {
    std::string line;
    while (true) {
        std::cout << prompt;
        if (!std::getline(std::cin, line)) return false;
        std::istringstream input(line);
        char extra;
        if ((input >> value) && !(input >> extra)) return true;
        std::cout << "Entrada invalida. Escribe un numero entero.\n";
    }
}

int main() {
    BST<int> bst;
    int option;
    int value;

    while (true) {
        std::cout << "\n1. Insertar valor\n"
                  << "2. Mostrar inorder\n"
                  << "3. Mostrar preorder\n"
                  << "4. Mostrar postorder\n"
                  << "5. Buscar valor\n"
                  << "6. Mostrar altura\n"
                  << "7. Mostrar ancestros\n"
                  << "8. Consultar nivel\n"
                  << "9. Eliminar valor\n"
                  << "10. Imprimir arbol\n"
                  << "11. Mostrar recorrido por niveles\n"
                  << "0. Salir\n";
        if (!readInteger("Opcion: ", option) || option == 0) break;

        switch (option) {
            case 1:
                if (!readInteger("Valor: ", value)) return 0;
                if (bst.find(value)) std::cout << "El valor ya existe\n";
                else {
                    bst.insert(value);
                    std::cout << "Valor insertado\n";
                }
                break;
            case 2:
                bst.visit(2);
                break;
            case 3:
                bst.visit(1);
                break;
            case 4:
                bst.visit(3);
                break;
            case 5:
                if (!readInteger("Valor: ", value)) return 0;
                std::cout << (bst.find(value) ? "Valor encontrado\n" : "Valor no encontrado\n");
                break;
            case 6:
                std::cout << "Altura: " << bst.height() << '\n';
                break;
            case 7:
                if (!readInteger("Valor: ", value)) return 0;
                bst.ancestors(value);
                break;
            case 8:
                if (!readInteger("Valor: ", value)) return 0;
                std::cout << "Nivel: " << bst.whatLevelAmI(value) << '\n';
                break;
            case 9:
                if (!readInteger("Valor: ", value)) return 0;
                try {
                    bst.remove(value);
                    std::cout << "Valor eliminado\n";
                } catch (const std::out_of_range& error) {
                    std::cout << error.what() << '\n';
                }
                break;
            case 10:
                bst.print();
                break;
            case 11:
                bst.visit(4);
                break;
            default:
                std::cout << "Opcion invalida\n";
        }
    }
    return 0;
}
