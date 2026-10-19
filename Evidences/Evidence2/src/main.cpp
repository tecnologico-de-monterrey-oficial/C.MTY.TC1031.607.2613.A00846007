// Ian Armando Borde Escobar - A00846007

#include <chrono>
#include <cstddef>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <system_error>
#include <tuple>
#include "../include/Queue.h"
#include "../include/DoublyLinkedList.h"
#include "../include/LogRecord.h"

bool chronologicalLess(
    const LogRecord& first,
    const LogRecord& second
) {
    return std::tie(
        first.year,
        first.month,
        first.day,
        first.hour,
        first.minute,
        first.second
    ) < std::tie(
        second.year,
        second.month,
        second.day,
        second.hour,
        second.minute,
        second.second
    );
}

bool readInteger(const std::string& prompt, int& value) {
    while (true) {
        std::cout << prompt;

        std::string line;

        if (!std::getline(std::cin, line))
            return false;

        std::istringstream input(line);
        int parsed;
        char extra;

        if ((input >> parsed) && !(input >> extra)) {
            value = parsed;
            return true;
        }

        std::cout << "Entrada invalida. Escribe un numero entero\n";
    }
}

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

bool hasStableOrder(
    const DoublyLinkedList<LogRecord>& records
) {
    const NodeD<LogRecord>* current = records.getHead();

    while (current && current->next) {
        const LogRecord& first = current->data;
        const LogRecord& second = current->next->data;

        bool sameTimestamp =
            !chronologicalLess(first, second)
            && !chronologicalLess(second, first);

        if (sameTimestamp && first.arrivalOrder > second.arrivalOrder)
            return false;

        current = current->next;
    }

    return true;
}

bool exportRecords(
    const DoublyLinkedList<LogRecord>& records
) {
    std::error_code error;
    std::filesystem::create_directories("out", error);

    if (error) {
        std::cout << "No se pudo preparar la carpeta out: "
                  << error.message() << '\n';
        return false;
    }

    std::ofstream output("out/output608.out");

    if (!output.is_open()) {
        std::cout << "No se pudo crear out/output608.out\n";
        return false;
    }

    for (const NodeD<LogRecord>* current = records.getHead();
         current;
         current = current->next) {
        output << current->data << '\n';
    }

    output.close();

    if (output.fail()) {
        std::cout << "No se pudo completar la escritura del archivo\n";
        return false;
    }

    std::cout << "Archivo generado: out/output608.out\n";
    return true;
}

bool sortLogs(
    DoublyLinkedList<LogRecord>& records,
    const std::string& filename
) {
    if (records.getSize() == 0) {
        std::cout << "No hay registros para ordenar\n";
        return true;
    }

    if (records.isSorted(chronologicalLess)) {
        std::cout << "La lista ya esta ordenada por fecha y hora\n";
        exportRecords(records);
        return true;
    }

    int prediction;

    while (true) {
        std::cout << "\nPredice el crecimiento de las comparaciones:\n"
                  << "1. Aproximadamente n * log2(n)\n"
                  << "2. Aproximadamente n^2\n";

        if (!readInteger("Prediccion: ", prediction))
            return false;

        if (prediction == 1 || prediction == 2)
            break;

        std::cout << "Selecciona 1 o 2\n";
    }

    auto start = std::chrono::steady_clock::now();

    auto metrics = records.mergeSort(chronologicalLess);

    auto finish = std::chrono::steady_clock::now();

    double milliseconds =
        std::chrono::duration<double, std::milli>(
            finish - start
        ).count();

    bool ordered = records.isSorted(chronologicalLess);
    bool stable = ordered && hasStableOrder(records);

    std::cout << "\nRESULTADOS DEL ORDENAMIENTO\n"
              << "Algoritmo: Merge Sort estable\n"
              << "Archivo: " << filename << '\n'
              << "Registros: " << records.getSize() << '\n'
              << "Prediccion: "
              << (prediction == 1 ? "n * log2(n)" : "n^2")
              << '\n';

    std::streamsize previousPrecision = std::cout.precision();
    std::ios_base::fmtflags previousFlags = std::cout.flags();

    std::cout << std::fixed << std::setprecision(6)
              << "Tiempo de ejecucion: "
              << milliseconds << " ms\n";

    std::cout.flags(previousFlags);
    std::cout.precision(previousPrecision);

    std::cout << "Comparaciones del ordenamiento: "
              << metrics.comparisons << '\n'
              << "Profundidad maxima de recursion: "
              << metrics.maximumDepth << '\n'
              << "Orden cronologico correcto: "
              << (ordered ? "Si" : "No") << '\n'
              << "Orden de llegada conservado en fechas y horas iguales: "
              << (stable ? "Si" : "No") << '\n';

    if (!ordered || !stable) {
        std::cout << "La verificacion fallo. No se exportaron los datos\n";
        return true;
    }

    std::cout << "Coincide con la prediccion: "
              << (prediction == 1 ? "Si" : "No")
              << ". El crecimiento teorico de Merge Sort es O(n log n)\n"
              << "Una sola corrida no demuestra el crecimiento asintotico\n";

    exportRecords(records);
    return true;
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
            record.arrivalOrder = lineNumber;
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

    while (true) {
        std::cout << "\nMENU PRINCIPAL\n"
                  << "1. Ordenar por fecha y hora\n"
                  << "5. Salir\n";

        int option;

        if (!readInteger("Opcion: ", option)) {
            std::cout << "\nEntrada finalizada\n";
            break;
        }

        switch (option) {
            case 1:
                if (!sortLogs(records, filename)) {
                    std::cout << "\nEntrada finalizada\n";
                    return 0;
                }

                break;

            case 5:
                std::cout << "Programa finalizado\n";
                return 0;

            default:
                std::cout << "Opcion inexistente. Selecciona 1 o 5\n";
                break;
        }
    }

    return 0;
}