// Ian Armando Borde Escobar - A00846007

#include "../include/LogRecord.h"
#include <iomanip>
#include <sstream>

namespace {
    bool parseNumber(
        const std::string& text,
        int minimum,
        int maximum,
        int& value
    ) {
        if (text.empty() || text.size() > 4)
            return false;

        int result = 0;

        for (char character : text) {
            if (character < '0' || character > '9')
                return false;

            result = result * 10 + (character - '0');
        }

        if (result < minimum || result > maximum)
            return false;

        value = result;
        return true;
    }

    bool isLeapYear(int year) {
        return year % 400 == 0
            || (year % 4 == 0 && year % 100 != 0);
    }

    std::string trim(const std::string& text) {
        std::size_t first = text.find_first_not_of(" \t\r\n");

        if (first == std::string::npos)
            return "";

        std::size_t last = text.find_last_not_of(" \t\r\n");

        return text.substr(first, last - first + 1);
    }

    bool validateIP(const std::string& ip) {
        if (ip.empty() || ip.front() == '.' || ip.back() == '.')
            return false;

        std::istringstream input(ip);
        std::string part;
        int count = 0;

        while (std::getline(input, part, '.')) {
            int value;

            if (part.empty() || part.size() > 3)
                return false;

            if (!parseNumber(part, 0, 255, value))
                return false;

            ++count;
        }

        return count == 4;
    }
}

int monthNumber(const std::string& month) {
    if (month.size() != 3)
        return 0;

    const std::string months =
        "Jan Feb Mar Apr May Jun Jul Aug Sep Oct Nov Dec";

    std::size_t position = months.find(month);

    if (position == std::string::npos || position % 4 != 0)
        return 0;

    return static_cast<int>(position / 4) + 1;
}

std::string monthName(int month) {
    if (month < 1 || month > 12)
        return "";

    const std::string months =
        "Jan Feb Mar Apr May Jun Jul Aug Sep Oct Nov Dec";

    return months.substr(
        static_cast<std::size_t>((month - 1) * 4),
        3
    );
}

bool validateDate(
    int month,
    int day,
    int year,
    std::string& reason
) {
    reason.clear();

    if (month < 1 || month > 12) {
        reason = "Mes invalido";
        return false;
    }

    if (year < 1 || year > 9999) {
        reason = "Anio fuera del intervalo valido";
        return false;
    }

    int maximumDay = 31;

    if (month == 4 || month == 6 || month == 9 || month == 11)
        maximumDay = 30;
    else if (month == 2)
        maximumDay = isLeapYear(year) ? 29 : 28;

    if (day < 1 || day > maximumDay) {
        reason = "Dia invalido para el mes y anio indicados";
        return false;
    }

    return true;
}

bool parseLog(
    const std::string& line,
    LogRecord& record,
    std::string& reason
) {
    reason.clear();

    if (trim(line).empty()) {
        reason = "Linea vacia";
        return false;
    }

    std::istringstream input(line);
    std::string monthText;
    std::string dayText;
    std::string yearText;
    std::string timeText;
    std::string ipText;

    if (!(input >> monthText >> dayText >> yearText
                >> timeText >> ipText)) {
        reason = "Faltan campos de fecha, hora o IP";
        return false;
    }

    LogRecord parsed;
    parsed.month = monthNumber(monthText);

    if (parsed.month == 0) {
        reason = "Mes invalido; utiliza Jan, Feb, Mar, Apr, May, "
                 "Jun, Jul, Aug, Sep, Oct, Nov o Dec";
        return false;
    }

    if (dayText.size() > 2
        || !parseNumber(dayText, 1, 31, parsed.day)) {
        reason = "El dia debe tener uno o dos digitos y estar entre 1 y 31";
        return false;
    }

    if (yearText.size() != 4
        || !parseNumber(yearText, 1, 9999, parsed.year)) {
        reason = "El anio debe tener cuatro digitos y ser mayor que cero";
        return false;
    }

    if (!validateDate(parsed.month, parsed.day, parsed.year, reason))
        return false;

    if (timeText.size() != 8
        || timeText[2] != ':'
        || timeText[5] != ':') {
        reason = "La hora debe tener el formato HH:MM:SS";
        return false;
    }

    if (!parseNumber(timeText.substr(0, 2), 0, 23, parsed.hour)
        || !parseNumber(timeText.substr(3, 2), 0, 59, parsed.minute)
        || !parseNumber(timeText.substr(6, 2), 0, 59, parsed.second)) {
        reason = "Hora fuera de rango; utiliza 00:00:00 a 23:59:59";
        return false;
    }

    if (!validateIP(ipText)) {
        reason = "IP invalida; se esperan cuatro numeros entre 0 y 255";
        return false;
    }

    std::string description;
    std::getline(input, description);
    description = trim(description);

    if (description.empty()) {
        reason = "Falta la descripcion del evento";
        return false;
    }

    parsed.ip = ipText;
    parsed.description = description;
    record = parsed;

    return true;
}

std::ostream& operator<<(
    std::ostream& out,
    const LogRecord& record
) {
    char previousFill = out.fill('0');

    out << monthName(record.month) << ' '
        << std::setw(2) << record.day << ' '
        << std::setw(4) << record.year << ' '
        << std::setw(2) << record.hour << ':'
        << std::setw(2) << record.minute << ':'
        << std::setw(2) << record.second << ' '
        << record.ip << ' '
        << record.description;

    out.fill(previousFill);

    return out;
}