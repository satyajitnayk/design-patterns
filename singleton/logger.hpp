#ifndef logger_hpp
#define logger_hpp

#include <mutex>
#include <string>
using namespace std;

class Logger {
private:
  static Logger *loggerInstance;
  static mutex mtx;
  Logger();
  Logger(const Logger &);         // copy constructor
  Logger operator=(const Logger); // operator overloading

public:
  static Logger *getLogger();
  void Log(string);
};

#endif