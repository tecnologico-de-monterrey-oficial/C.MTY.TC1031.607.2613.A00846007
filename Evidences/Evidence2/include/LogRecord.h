// Ian Armando Borde Escobar - A00846007

#ifndef LOGRECORD_H
#define LOGRECORD_H

#include <ostream>
#include <string>

struct LogRecord {
    int month = 0;
    int day = 0;
    int year = 0;
    int hour = 0;
    int minute = 0;
    int second = 0;
    std::string ip;
    std::string description;
};

int monthNumber(const std::string& month);

std::string monthName(int month);

bool validateDate(
    int month,
    int day,
    int year,
    std::string& reason
);

bool parseLog(
    const std::string& line,
    LogRecord& record,
    std::string& reason
);

std::ostream& operator<<(
    std::ostream& out,
    const LogRecord& record
);

#endif