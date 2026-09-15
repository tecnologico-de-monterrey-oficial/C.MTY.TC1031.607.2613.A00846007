// Ian Armando Borde Escobar
// A00846007
#ifndef Log_h
#define Log_h

#include <string>
using namespace std;

struct Log {
    int year;
    string month;
    int day;
    string time;
    string ip;
    string message;
    string key;
    Log();
    Log(int year, string month, int day, string time, string ip, string message);
    string createKey();
    bool operator>(const Log &other) const;
    bool operator<(const Log &other) const;
    bool operator==(const Log &other) const;
    bool operator!=(const Log &other) const;
    bool operator>=(const Log &other) const;
    bool operator<=(const Log &other) const;
};

bool Log::operator>(const Log &other) const {
    return key > other.key;
}





#endif /* Log_h */