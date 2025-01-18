### Adapter Design Pattern Notes:

#### Definition:

The **Adapter Design Pattern** is a **structural design pattern** that allows incompatible interfaces to work together by acting as a bridge between them.

### Key Points:

1. **Purpose**:

   - Converts the interface of a class into another interface that a client expects.
   - Enables classes with incompatible interfaces to collaborate.

2. **When to Use**:

   - When you want to reuse an existing class whose interface does not match the one you need.
   - When a legacy system needs to integrate with a new system.

3. **Types of Adapters**:

   - **Class Adapter**: Uses inheritance to adapt one interface to another.
   - **Object Adapter**: Uses composition to achieve the same.

4. **Benefits**:

   - Promotes code reuse without modifying existing code.
   - Decouples client code from the concrete implementation.

5. **Drawbacks**:
   - Adds an extra layer of complexity.
   - May require additional maintenance if the adapter logic is complex.

### Key Components:

1. **Target**: Defines the interface expected by the client (`NewPrinter`).
2. **Adaptee**: The existing class with a different interface (`OldPrinter`).
3. **Adapter**: Bridges the gap by translating the interface of the adaptee to the target (`PrinterAdapter`).
4. **Client**: Uses the target interface (`clientCode`).

---

```c++
#include <iostream>
#include <memory>
#include <string>

using namespace std;

// Old system
class OldLogger {
public:
  void logMessage(string message) {
    cout << "Old log format: " << message << endl;
  }
};

// New system interface (what we want to use)
class NewLogger {
public:
  virtual void log(string message) = 0;
};

// Adapter class to make OldLogger compatible with NewLogger
class LoggerAdapter : public NewLogger {
private:
  unique_ptr<OldLogger> oldLogger;

public:
  LoggerAdapter(unique_ptr<OldLogger> oldLogger)
      : oldLogger(std::move(oldLogger)) {}

  void log(string message) override {
    // Adapting the old logging method to fit the new interface
    oldLogger->logMessage(message);
  }
};

int main() {
  auto oldLogger = make_unique<OldLogger>();
  auto adapter = make_unique<LoggerAdapter>(std::move(oldLogger));

  // Now we can use the new system's interface, but it's calling the old
  // system underneath
  adapter->log("This is a log message");

  return 0;
}
```

### Common Interview Questions:

1. **What is the Adapter Pattern?**

   - A pattern that allows incompatible interfaces to work together.

2. **Real-world examples?**

   - **Electrical Adapter**: Converting plug shapes or voltages.
   - **Legacy Systems**: Integrating old APIs with new ones.
   - **Media Players**: Converting different media formats.

3. **How does the Adapter differ from Bridge Pattern?**

   - Adapter focuses on compatibility between existing interfaces.
   - Bridge separates abstraction from implementation for scalability.

4. **Class vs. Object Adapter?**
   - Class Adapter uses **inheritance** and cannot adapt multiple adaptees.
   - Object Adapter uses **composition** and is more flexible.

### Summary:

The Adapter Pattern is about **compatibility**. It acts as a translator, allowing systems with mismatched interfaces to work together without altering their underlying code.
