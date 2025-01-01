#include "logger.hpp"
#include <iostream>
#include <thread>
using namespace std;

void user1Logs() {
  Logger *logger1 = Logger::getLogger();
  logger1->Log("message from user1");
}

void user2Logs() {
  Logger *logger2 = Logger::getLogger();
  logger2->Log("message from user2");
}
int main() {
  thread t1(user1Logs);
  thread t2(user2Logs);

  t1.join();
  t2.join();
  return 0;
}