#include "logger.hpp"
#include <iostream>
using namespace std;

Logger *Logger::loggerInstance = nullptr;
mutex Logger::mtx;

Logger::Logger() {
  cout << "New instance created."
       << "\n";
}

void Logger::Log(string message) { cout << message << "\n"; }

Logger *Logger::getLogger() {
  // double-checked lock
  if (loggerInstance == nullptr) {
    mtx.lock();
    if (loggerInstance == nullptr) {
      loggerInstance = new Logger();
    }
    mtx.unlock();
  }
  return loggerInstance;
}