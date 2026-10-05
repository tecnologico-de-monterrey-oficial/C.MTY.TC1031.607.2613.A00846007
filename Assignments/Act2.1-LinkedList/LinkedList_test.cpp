// Ian Armando Borde Escobar - A00846007

#include <iostream>
#include <limits>
#include <random>
#include <stdexcept>
#include <string>
#include "LinkedList.h"

template <typename T>
T readValue(const std::string& prompt) {
    T value;

    while (true) {
        std::cout << prompt;

        if (std::cin >> value) {
            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(),
                '\n'
            );

            return value;
        }

        if (std::cin.eof())
            throw std::runtime_error("Fin de entrada");

        std::cin.clear();

        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(),
            '\n'
        );

        std::cout << "Entrada invalida. Intenta otra vez.\n";
    }
}

template <>
std::string readValue<std::string>(const std::string& prompt) {
    std::cout << prompt;

    std::string value;

    if (!std::getline(std::cin, value))
        throw std::runtime_error("Fin de entrada");

    return value;
}

int readRange(const std::string& prompt, int low, int high) {
    while (true) {
        int value = readValue<int>(prompt);

        if (value >= low && value <= high)
            return value;

        std::cout << "Valor fuera del intervalo permitido.\n";
    }
}

template <typename T>
T randomValue(std::mt19937& generator);

template <>
int randomValue<int>(std::mt19937& generator) {
    return std::uniform_int_distribution<int>(0, 99)(generator);
}

template <>
std::string randomValue<std::string>(std::mt19937& generator) {
    const std::string words[] = {
        "sol", "luna", "mar", "cielo", "nube"
    };

    return words[
        std::uniform_int_distribution<int>(0, 4)(generator)
    ];
}

template <typename T>
LinkedList<T> createList(std::mt19937& generator) {
    LinkedList<T> list;

    int mode = readRange(
        "1. Capturados  2. Aleatorios: ", 1, 2
    );

    int count = readRange(
        "Cantidad (0 a 1000): ", 0, 1000
    );

    for (int i = 0; i < count; ++i) {
        T value = mode == 1
            ? readValue<T>("Dato: ")
            : randomValue<T>(generator);

        list.addLast(value);
    }

    return list;
}

template <typename T>
void runMenu(std::mt19937& generator) {
    LinkedList<T> list = createList<T>(generator);

    while (true) {
        std::cout << "\nLista actual: ";
        list.print();

        std::cout <<
            "1. Agregar al principio\n"
            "2. Agregar al final\n"
            "3. Insertar despues de un indice\n"
            "4. Borrar por dato\n"
            "5. Borrar por posicion\n"
            "6. Obtener con getData\n"
            "7. Actualizar por dato\n"
            "8. Actualizar por posicion\n"
            "9. Buscar dato\n"
            "10. Leer con []\n"
            "11. Actualizar con []\n"
            "12. Duplicar con =\n"
            "0. Volver al menu de tipos\n";

        int option = readRange("Opcion: ", 0, 12);

        if (option == 0)
            return;

        try {
            switch (option) {
                case 1:
                    list.addFirst(readValue<T>("Dato: "));
                    break;

                case 2:
                    list.addLast(readValue<T>("Dato: "));
                    break;

                case 3: {
                    int index = readValue<int>("Indice: ");
                    T value = readValue<T>("Dato: ");

                    list.insert(index, value);
                    break;
                }

                case 4: {
                    T value = readValue<T>("Dato a borrar: ");
                    bool deleted = list.deleteData(value);

                    std::cout << (
                        deleted ? "Borrado\n" : "No encontrado\n"
                    );

                    break;
                }

                case 5: {
                    int index = readValue<int>("Posicion: ");
                    bool deleted = list.deleteAt(index);

                    std::cout << (
                        deleted ? "Borrado\n" : "Posicion invalida\n"
                    );

                    break;
                }

                case 6: {
                    int index = readValue<int>("Posicion: ");

                    std::cout << "Dato: "
                              << list.getData(index) << '\n';

                    break;
                }

                case 7: {
                    T oldValue = readValue<T>("Dato a buscar: ");
                    T newValue = readValue<T>("Nuevo dato: ");

                    list.updateData(oldValue, newValue);
                    break;
                }

                case 8: {
                    int index = readValue<int>("Posicion: ");
                    T value = readValue<T>("Nuevo dato: ");

                    list.updateAt(index, value);
                    break;
                }

                case 9: {
                    T value = readValue<T>("Dato a buscar: ");

                    std::cout << "Indice: "
                              << list.findData(value) << '\n';

                    break;
                }

                case 10: {
                    int index = readValue<int>("Posicion: ");

                    std::cout << "Dato: "
                              << list[index] << '\n';

                    break;
                }

                case 11: {
                    int index = readValue<int>("Posicion: ");
                    T value = readValue<T>("Nuevo dato: ");

                    list[index] = value;
                    break;
                }

                case 12: {
                    LinkedList<T> copy;
                    copy = list;

                    std::cout << "Copia: ";
                    copy.print();

                    if (copy.getSize() > 0) {
                        copy.deleteAt(0);

                        std::cout <<
                            "Copia tras borrar su primer elemento: ";

                        copy.print();
                    }

                    std::cout << "Original sin cambios: ";
                    list.print();

                    break;
                }
            }
        } catch (const std::out_of_range& error) {
            std::cout << "Error: " << error.what() << '\n';
        }
    }
}

int main() {
    std::mt19937 generator(std::random_device{}());

    try {
        while (true) {
            int type = readRange(
                "\n1. Enteros  2. Textos  0. Salir: ", 0, 2
            );

            if (type == 0)
                break;

            if (type == 1)
                runMenu<int>(generator);
            else
                runMenu<std::string>(generator);
        }
    } catch (const std::runtime_error& error) {
        std::cout << error.what() << '\n';
    }

    return 0;
}