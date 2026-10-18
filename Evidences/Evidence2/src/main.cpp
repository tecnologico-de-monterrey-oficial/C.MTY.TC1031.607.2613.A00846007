// Ian Armando Borde Escobar - A00846007

#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>
#include "../include/Queue.h"
#include "../include/DoublyLinkedList.h"
#include "../include/LogRecord.h"

bool openLogFile(
    std::ifstream& file,
    std::string& filename
) {
    while (true) {
        std::cout << "\nArchivo que deseas cargar:\n"
                  << "log607-1.txt\n"
                  << "log607-2.txt\n"
                  << "Tambien puedes escribir la ruta de otro archivo\n"
                  << "Archivo: ";

        std::string input;

        if (!std::getline(std::cin, input))
            return false;

        std::size_t first = input.find_first_not_of(" \t\r");
        std::size_t last = input.find_last_not_of(" \t\r");

        if (first == std::string::npos) {
            std::cout << "El nombre del archivo no puede estar vacio\n";
            continue;
        }

        input = input.substr(first, last - first + 1);

        file.open(input);

        if (file.is_open()) {
            filename = input;
            return true;
        }

        file.clear();

        if (input.find_first_of("/\\") == std::string::npos) {
            std::string dataPath = "data/" + input;
            file.open(dataPath);

            if (file.is_open()) {
                filename = dataPath;
                return true;
            }

            file.clear();
        }

        std::cout << "No se pudo abrir el archivo: " << input
                  << "\nVerifica que exista y que tengas permiso de lectura\n";
    }
}

int main() {
    std::cout << "PROCESAMIENTO DE LOGS DE RED\n";

    std::ifstream file;
    std::string filename;

    if (!openLogFile(file, filename)) {
        std::cout << "\nEntrada finalizada\n";
        return 0;
    }

    Queue<std::string> pendingLines;
    std::string line;
    std::size_t totalLines = 0;

    while (std::getline(file, line)) {
        pendingLines.enqueue(line);
        ++totalLines;
    }

    if (file.bad() || (file.fail() && !file.eof())) {
        std::cerr << "Ocurrio un error durante la lectura del archivo\n";
        return 1;
    }

    file.close();

    DoublyLinkedList<LogRecord> records;
    std::size_t lineNumber = 0;
    std::size_t loaded = 0;
    std::size_t omitted = 0;

    while (!pendingLines.isEmpty()) {
        std::string currentLine = pendingLines.dequeue();
        ++lineNumber;

        LogRecord record;
        std::string reason;

        if (parseLog(currentLine, record, reason)) {
            records.addLast(record);
            ++loaded;
        } else {
            ++omitted;

            std::cout << "Linea " << lineNumber
                      << " omitida: " << reason << '\n';
        }
    }

    std::cout << "\nRESUMEN DE CARGA\n"
              << "Archivo: " << filename << '\n'
              << "Lineas leidas: " << totalLines << '\n'
              << "Registros cargados: " << loaded << '\n'
              << "Lineas omitidas: " << omitted << '\n';

    if (loaded == 0)
        std::cout << "El archivo no contiene registros validos\n";
    else
        std::cout << "Los registros conservan el orden de llegada\n";

    return 0;
}