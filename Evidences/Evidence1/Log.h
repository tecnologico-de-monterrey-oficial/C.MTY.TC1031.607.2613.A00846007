#ifdef Log_h
#define Log_h

#include <string>

class Log {
    private:
        int year;
        string month;
        int day;
        string time;
        string ip;
        string message;
        string key;
    public:
        Log(int year, string month, int day, string time, string ip, string message, string key);
        string createKey();
        bool operator>(const Log& other) const;
        bool operator<(const Log& other) const;
        bool operator==(const Log& other) const;
        bool operator!=(const Log& other) const;
};



















#endif