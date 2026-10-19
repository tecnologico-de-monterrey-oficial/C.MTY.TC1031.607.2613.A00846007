// Ian Armando Borde Escobar - A00846007

#include <chrono>
#include <cstddef>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <system_error>
#include <tuple>
#include "../include/Queue.h"
#include "../include/Stack.h"
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

        std::cout << "Entrada invalida\nEscribe un numero entero\n";
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

        std::cout << "No se pudo abrir el archivo: " << input << '\n';
    }
}

bool exportRecords(const DoublyLinkedList<LogRecord>& records) {
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

    std::cout << "\nRESULTADOS DEL ORDENAMIENTO\n"
              << "Algoritmo: Merge Sort estable\n"
              << "Archivo: " << filename << '\n'
              << "Registros: " << records.getSize() << '\n'
              << "Prediccion: "
              << (prediction == 1 ? "n * log2(n)" : "n^2") << '\n'
              << std::fixed << std::setprecision(6)
              << "Tiempo de ejecucion: " << milliseconds << " ms\n"
              << "Comparaciones del ordenamiento: "
              << metrics.comparisons << '\n'
              << "Profundidad maxima de recursion: "
              << metrics.maximumDepth << '\n'
              << "Coincide con la prediccion: "
              << (prediction == 1 ? "Si" : "No") << '\n';

    exportRecords(records);
    return true;
}

struct SearchDay {
    int year = 0;
    int month = 0;
    int day = 0;
};

std::string formatDay(const SearchDay& date) {
    std::ostringstream output;

    output << monthName(date.month) << ' '
           << std::setfill('0') << std::setw(2) << date.day << ' '
           << std::setw(4) << date.year;

    return output.str();
}

bool parseDayNumber(const std::string& text, int& value) {
    if (text.empty() || text.size() > 4)
        return false;

    value = 0;

    for (char character : text) {
        if (character < '0' || character > '9')
            return false;

        value = value * 10 + character - '0';
    }

    return true;
}

bool readSearchDay(SearchDay& date) {
    while (true) {
        std::cout << "Dia a buscar, por ejemplo Sep 14 2024: ";

        std::string line;

        if (!std::getline(std::cin, line))
            return false;

        std::istringstream input(line);
        std::string monthText, dayText, yearText, extra;
        SearchDay parsed;

        if (!(input >> monthText >> dayText >> yearText)
            || (input >> extra)) {
            std::cout << "Formato invalido Usa Mmm DD AAAA\n";
            continue;
        }

        parsed.month = monthNumber(monthText);

        if (parsed.month == 0) {
            std::cout << "Mes invalido Usa Jan, Feb, Mar, Apr, May, Jun, "
                      << "Jul, Aug, Sep, Oct, Nov o Dec\n";
            continue;
        }

        if (dayText.size() > 2 || yearText.size() != 4
            || !parseDayNumber(dayText, parsed.day)
            || !parseDayNumber(yearText, parsed.year)) {
            std::cout << "El dia debe tener uno o dos digitos "
                      << "y el anio cuatro digitos\n";
            continue;
        }

        std::string reason;

        if (!validateDate(parsed.month, parsed.day, parsed.year, reason)) {
            std::cout << reason << '\n';
            continue;
        }

        date = parsed;
        return true;
    }
}

bool searchLogs(
    const DoublyLinkedList<LogRecord>& records,
    bool sorted,
    SearchDay& lastDay,
    bool& searched,
    bool descending
) {
    if (!sorted) {
        std::cout << "Primero ordena los registros con la opcion 1\n";
        return true;
    }

    if (records.getSize() == 0) {
        std::cout << "No hay registros para buscar\n";
        return true;
    }

    if (!descending || !searched) {
        if (!readSearchDay(lastDay))
            return false;

        searched = true;
    }

    Stack<const LogRecord*> matches;
    std::size_t found = 0;
    auto target = std::tie(lastDay.year, lastDay.month, lastDay.day);

    std::cout << "\nLogs del dia " << formatDay(lastDay)
              << (descending ? " en orden descendente\n" : "\n");

    for (const NodeD<LogRecord>* current = records.getHead();
         current;
         current = current->next) {
        const LogRecord& record = current->data;
        auto date = std::tie(record.year, record.month, record.day);

        if (date > target)
            break;

        if (date == target) {
            ++found;

            if (descending)
                matches.push(&record);
            else
                std::cout << record << '\n';
        }
    }

    while (!matches.isEmpty())
        std::cout << *matches.pop() << '\n';

    if (found == 0)
        std::cout << "No se encontraron registros para ese dia\n";

    std::cout << "Total encontrado: " << found << '\n';
    return true;
}

template <typename Key, typename Format>
void printMostFrequent(
    const std::map<Key, std::size_t>& frequencies,
    const std::string& title,
    Format format
) {
    std::size_t maximum = 0;

    for (const auto& entry : frequencies) {
        if (entry.second > maximum)
            maximum = entry.second;
    }

    std::cout << '\n' << title << '\n';

    for (const auto& entry : frequencies) {
        if (entry.second == maximum)
            std::cout << format(entry.first)
                      << " | Apariciones: " << entry.second << '\n';
    }
}

void showStatistics(const DoublyLinkedList<LogRecord>& records) {
    std::cout << "\nESTADISTICAS DEL ARCHIVO\n"
              << "Total de registros: " << records.getSize() << '\n';

    if (records.getSize() == 0) {
        std::cout << "No hay registros para calcular estadisticas\n";
        return;
    }

    using DayKey = std::tuple<int, int, int>;

    std::map<DayKey, std::size_t> days;
    std::map<std::string, std::size_t> events;
    std::map<std::string, std::size_t> addresses;

    for (const NodeD<LogRecord>* current = records.getHead();
         current;
         current = current->next) {
        const LogRecord& record = current->data;

        ++days[std::make_tuple(record.year, record.month, record.day)];
        ++events[record.description];
        ++addresses[record.ip];
    }

    printMostFrequent(
        days,
        "Dias con mas incidentes",
        [](const DayKey& key) {
            return formatDay({
                std::get<0>(key),
                std::get<1>(key),
                std::get<2>(key)
            });
        }
    );

    printMostFrequent(
        events,
        "Tipos de evento mas frecuentes",
        [](const std::string& event) {
            return event;
        }
    );

    printMostFrequent(
        addresses,
        "Direcciones IP mas frecuentes",
        [](const std::string& ip) {
            return ip;
        }
    );
}

int main() {
    std::cout << "PROCESAMIENTO DE LOGS DE RED\n";

    std::ifstream file;
    std::string filename;

    if (!openLogFile(file, filename))
        return 0;

    Queue<std::string> pendingLines;
    std::string line;

    while (std::getline(file, line))
        pendingLines.enqueue(line);

    if (file.bad() || (file.fail() && !file.eof())) {
        std::cerr << "Ocurrio un error durante la lectura del archivo\n";
        return 1;
    }

    file.close();

    DoublyLinkedList<LogRecord> records;
    std::size_t lineNumber = 0;
    std::size_t omitted = 0;

    while (!pendingLines.isEmpty()) {
        std::string currentLine = pendingLines.dequeue();
        ++lineNumber;

        LogRecord record;
        std::string reason;

        if (parseLog(currentLine, record, reason)) {
            record.arrivalOrder = lineNumber;
            records.addLast(record);
        } else {
            ++omitted;

            std::cout << "Linea " << lineNumber
                      << " omitida: " << reason << '\n';
        }
    }

    std::cout << "\nRESUMEN DE CARGA\n"
              << "Archivo: " << filename << '\n'
              << "Registros cargados: " << records.getSize() << '\n'
              << "Lineas omitidas: " << omitted << '\n';

    if (records.getSize() == 0)
        std::cout << "El archivo no contiene registros validos\n";

    bool sorted = false;
    bool searched = false;
    SearchDay lastDay;

    while (true) {
        std::cout << "\nMENU PRINCIPAL\n"
                  << "1. Ordenar por fecha y hora\n"
                  << "2. Buscar logs por dia\n"
                  << "3. Mostrar logs por dia en orden descendente\n"
                  << "4. Estadisticas del archivo\n"
                  << "5. Salir\n";

        int option;

        if (!readInteger("Opcion: ", option))
            return 0;

        switch (option) {
            case 1:
                if (!sortLogs(records, filename))
                    return 0;

                sorted = true;
                break;

            case 2:
            case 3:
                if (!searchLogs(
                    records,
                    sorted,
                    lastDay,
                    searched,
                    option == 3
                )) {
                    return 0;
                }

                break;

            case 4:
                showStatistics(records);
                break;

            case 5:
                std::cout << "Programa finalizado\n";
                return 0;

            default:
                std::cout << "Opcion inexistente Selecciona un numero del 1 al 5\n";
                break;
        }
    }
}