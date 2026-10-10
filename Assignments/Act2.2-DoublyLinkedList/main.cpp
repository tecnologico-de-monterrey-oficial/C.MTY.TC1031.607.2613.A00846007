// Ian Armando Borde Escobar - A00846007

#include "DoublyLinkedList.h"
#include <iostream>
#include <random>
#include <sstream>
#include <string>
template <typename T>
T readValue(const std::string& prompt) {
    while (true) {
        std::cout << prompt;
        std::string line;
        if (!std::getline(std::cin, line)) {
            throw std::runtime_error("Fin de la entrada.");
        }
        std::istringstream input(line);
        T value;
        if (input >> value) {
            input >> std::ws;
            if (input.eof()) return value;
        }
        std::cout << "Entrada invalida. Intenta de nuevo.\n";
    }
}

template <>
std::string readValue<std::string>(const std::string& prompt) {
    std::cout << prompt;
    std::string value;
    if (!std::getline(std::cin, value)) {
        throw std::runtime_error("Fin de la entrada.");
    }
    return value;
}

int readRange(const std::string& prompt, int minimum, int maximum) {
    while (true) {
        int value = readValue<int>(prompt);
        if (value >= minimum && value <= maximum) return value;
        std::cout << "El valor debe estar entre " << minimum << " y " << maximum << ".\n";
    }
}

template <typename T>
T randomValue(std::mt19937& engine);

template <>
int randomValue<int>(std::mt19937& engine) {
    return std::uniform_int_distribution<int>(0, 99)(engine);
}

template <>
double randomValue<double>(std::mt19937& engine) {
    return std::uniform_int_distribution<int>(0, 9999)(engine) / 100.0;
}

template <>
char randomValue<char>(std::mt19937& engine) {
    return static_cast<char>('a' + std::uniform_int_distribution<int>(0, 25)(engine));
}

template <>
std::string randomValue<std::string>(std::mt19937& engine) {
    std::string value;
    for (int i = 0; i < 5; ++i) value += randomValue<char>(engine);
    return value;
}

template <typename T>
void createList(DoublyLinkedList<T>& list, std::mt19937& engine) {
    int mode = readRange("1. Datos capturados\n2. Datos aleatorios\nModo: ", 1, 2);
    int count;
    do {
        count = readValue<int>("Cantidad de elementos: ");
        if (count < 0) std::cout << "La cantidad no puede ser negativa.\n";
    } while (count < 0);
    DoublyLinkedList<T> created;
    for (int i = 0; i < count; ++i) {
        if (mode == 1) {
            created.addLast(readValue<T>("Dato " + std::to_string(i) + ": "));
        } else {
            created.addLast(randomValue<T>(engine));
        }
    }
    list = created;
}

void printMenu() {
    std::cout << "\n1. Agregar al principio\n"
              << "2. Agregar al final\n"
              << "3. Insertar a la derecha de un indice\n"
              << "4. Borrar el primer dato igual al indicado\n"
              << "5. Borrar en una posicion\n"
              << "6. Obtener dato por posicion (getData)\n"
              << "7. Actualizar el primer dato igual al indicado\n"
              << "8. Actualizar por posicion (updateAt)\n"
              << "9. Encontrar un dato\n"
              << "10. Obtener por posicion con []\n"
              << "11. Actualizar por posicion con []\n"
              << "12. Igualar la lista con los datos de otra lista (=)\n"
              << "13. Limpiar lista\n"
              << "14. Ordenar lista\n"
              << "15. Duplicar cada elemento\n"
              << "16. Remover duplicados (ordena primero)\n"
              << "0. Salir\n";
}

template <typename T>
void runLists(std::mt19937& engine) {
    DoublyLinkedList<T> list;
    std::cout << "\nCrea la lista. Los indices empiezan en 0.\n";
    createList(list, engine);
    while (true) {
        std::cout << "\nLista: ";
        list.print(std::cout);
        std::cout << '\n';
        printMenu();
        int option = readRange("Opcion: ", 0, 16);
        if (option == 0) return;
        try {
            switch (option) {
                case 1: list.addFirst(readValue<T>("Dato: ")); break;
                case 2: list.addLast(readValue<T>("Dato: ")); break;
                case 3: {
                    int index = readValue<int>("Indice existente: ");
                    T data = readValue<T>("Dato: ");
                    list.insert(index, data);
                    break;
                }
                case 4: {
                    bool deleted = list.deleteData(readValue<T>("Dato a borrar: "));
                    std::cout << (deleted ? "Dato borrado.\n" : "Dato no encontrado.\n");
                    break;
                }
                case 5: {
                    bool deleted = list.deleteAt(readValue<int>("Posicion: "));
                    std::cout << (deleted ? "Dato borrado.\n" : "Posicion invalida.\n");
                    break;
                }
                case 6: {
                    int index = readValue<int>("Posicion: ");
                    std::cout << "Dato: " << list.getData(index) << '\n';
                    break;
                }
                case 7: {
                    T oldData = readValue<T>("Dato a buscar: ");
                    T newData = readValue<T>("Dato nuevo: ");
                    list.updateData(oldData, newData);
                    break;
                }
                case 8: {
                    int index = readValue<int>("Posicion: ");
                    T data = readValue<T>("Dato nuevo: ");
                    list.updateAt(index, data);
                    break;
                }
                case 9: {
                    T data = readValue<T>("Dato a buscar: ");
                    std::cout << "Posicion (-1 si no existe): " << list.findData(data) << '\n';
                    break;
                }
                case 10: {
                    int index = readValue<int>("Posicion: ");
                    std::cout << "Dato: " << list[index] << '\n';
                    break;
                }
                case 11: {
                    int index = readValue<int>("Posicion: ");
                    T data = readValue<T>("Dato nuevo: ");
                    list[index] = data;
                    break;
                }
                case 12: {
                    DoublyLinkedList<T> other;
                    std::cout << "Crea la otra lista cuyos datos se van a copiar.\n";
                    createList(other, engine);
                    list = other;
                    break;
                }
                case 13: list.clear(); break;
                case 14: list.sort(); break;
                case 15: list.duplicate(); break;
                case 16: list.removeDuplicates(); break;
            }
        } catch (const std::out_of_range& error) {
            std::cout << "Error: " << error.what() << '\n';
        }
    }
}

int main() {
    std::mt19937 engine(std::random_device{}());
    std::cout << "Act 2.2 - Listas doblemente encadenadas\n";
    try {
        int type = readRange("\nTipo de dato:\n1. Entero (int)\n2. Decimal (double)\n"
                             "3. Texto (string)\n4. Caracter (char)\n0. Salir\nTipo: ", 0, 4);
        switch (type) {
            case 0: return 0;
            case 1: runLists<int>(engine); break;
            case 2: runLists<double>(engine); break;
            case 3: runLists<std::string>(engine); break;
            case 4: runLists<char>(engine); break;
        }
    } catch (const std::exception& error) {
        std::cout << error.what() << '\n';
        return 1;
    }
}
