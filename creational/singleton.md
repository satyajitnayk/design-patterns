#### **Singleton Design Pattern**

The Singleton pattern ensures a class has only one instance and provides a global access point to that instance.

#### **When to Use**:

1. When only one instance of a class is needed (e.g., Logger, Configuration Manager, Database Connection).
2. To control access to a shared resource.

#### **Example: Logger**

```c++
#include <iostream>
#include <memory>
#include <mutex>
using namespace std;

class Logger {
private:
  // shared_ptr: Provides memory safety, lifetime management,
  // and integration with APIs requiring shared ownership.
  static shared_ptr<Logger> instance;
  static mutex mtx;

  // Private constructor to prevent instantiation
  Logger() {}

public:
  // Deleted methods to prevent copying and assignment
  Logger(const Logger &) = delete;
  Logger &operator=(const Logger &) = delete;

  // Static method to get the single instance
  static shared_ptr<Logger> getInstance() {
    // lock_guard: Ensures thread-safe creation and avoids potential race
    // conditions during instance initialization.
    lock_guard<mutex> lock(mtx);
    if (!instance) {
      instance = shared_ptr<Logger>(new Logger());
    }
    return instance;
  }

  // Log a message
  void log(const string &message) { cout << "[LOG]: " << message << endl; }
};

// Initialize static members
// NOTE: Static members are declared in the class definition but must be defined
// and initialized outside the class. This is because the compiler and linker
// treat static members as global variables. The class declaration only informs
// the compiler about their existence, but memory allocation happens separately
// during linking.
shared_ptr<Logger> Logger::instance = nullptr;
mutex Logger::mtx;

// Main Function
int main() {
  // Get the singleton instance and log messages
  auto logger1 = Logger::getInstance();
  logger1->log("Application started.");

  auto logger2 = Logger::getInstance();
  logger2->log("Performing some operations...");

  // Both instances are the same
  cout << "Logger1 and Logger2 are "
       << ((logger1 == logger2) ? "the same instance." : "different instances.")
       << endl;

  return 0;
}
```

1. **Private Constructor**: Ensures only the Singleton class can create its instance.
2. **Thread Safety**: Uses `std::mutex` to synchronize access and ensure only one instance is created in multithreaded environments.
3. **Lazy Initialization**: The instance is created only when `getInstance()` is called for the first time.
4. **Shared Ownership**: Uses `std::shared_ptr` to manage the instance's lifetime automatically.

### **Use Case: Logger**

- In production systems, logging is essential for debugging and monitoring.
- Using a Singleton Logger ensures consistent logging across different parts of the application while controlling the number of instances.

This example implements a thread-safe Singleton Logger.

#### **How It Works**:

- `getInstance()`: Provides the only access point to the single instance.
- `std::mutex`: Ensures thread-safe initialization in multithreaded scenarios.
- `std::shared_ptr`: Manages the Singleton instance's lifetime automatically.

#### **To Run**:

Compile the code with:

```bash
g++ -std=c++17 -pthread singleton.cpp -o singleton
```

Run:

```bash
./singleton
```

You should see:

```
[LOG]: Application started.
[LOG]: Performing some operations...
Logger1 and Logger2 are the same instance.
```
