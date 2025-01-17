The **SOLID principles** are five design principles that help developers write clean, maintainable, and scalable object-oriented code. These principles are:

1. **S**: **Single Responsibility Principle (SRP)**
2. **O**: **Open/Closed Principle (OCP)**
3. **L**: **Liskov Substitution Principle (LSP)**
4. **I**: **Interface Segregation Principle (ISP)**
5. **D**: **Dependency Inversion Principle (DIP)**

### **1. Single Responsibility Principle (SRP)**

**Definition**: A class or module should have only one reason to change, meaning it should have one responsibility.

#### Example Violating SRP:

```c++
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Employee {
private:
  string name;
  double salary;

public:
  Employee(const string &name, double salary) : name(name), salary(salary) {}
  // Stores employee details (responsibility 1)
  void printDetails() const {
    cout << "Employee: " << name << ", Salary: " << salary << endl;
  }
  // Calculates tax (responsibility 2)
  double calculateTax() const {
    return salary * 0.2; // Example tax calculation
  }
  // Generates report (responsibility 3)
  void generateReport() const {
    cout << "Report for " << name << ": Tax = " << calculateTax() << endl;
  }
};
```

**Problems**:

- Employee handles multiple responsibilities: storing data, calculating tax, and generating reports.
- If tax rules or report format changes, the Employee class needs modification, violating SRP.

---

#### Example Following SRP:

```c++
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Employee {
private:
  string name;
  double salary;

public:
  Employee(const string &name, double salary) : name(name), salary(salary) {}

  string getName() const { return name; }
  double getSalary() const { return salary; }
};

class TaxCalculator {
public:
  static double calculateTax(const Employee &employee) {
    return employee.getSalary() * 0.2; // Example tax calculation
  }
};

class ReportGenerator {
public:
  static void generateReport(const Employee &employee) {
    double tax = TaxCalculator::calculateTax(employee);
    cout << "Report for " << employee.getName() << ": Tax = " << tax << endl;
  }
};

int main() {
  Employee employee("John Doe", 50000);

  // Print details
  cout << "Employee: " << employee.getName()
       << ", Salary: " << employee.getSalary() << endl;

  // Generate report
  ReportGenerator::generateReport(employee);

  return 0;
}
```

**Benefits**:

- Change Isolation: Changing tax rules affects only TaxCalculator.
- Reusability: TaxCalculator can be reused for other purposes, like payroll systems.
- Readability: Each class has a clear, focused purpose.

---

### **2. Open/Closed Principle (OCP)**

**Definition**: A class should be open for extension but closed for modification. You should be able to add new functionality without changing existing code.

#### Example Violating OCP:

```c++
#include <iostream>
using namespace std;

class Notification {
public:
  void sendNotification(const string &type, const string &message) {
    if (type == "email") {
      cout << "Sending Email: " << message << endl;
    } else if (type == "sms") {
      cout << "Sending SMS: " << message << endl;
    }
  }
};
```

**Problem**: Adding a new notification type requires modifying the `sendNotification` method.

---

#### Example Following OCP:

```c++
#include <iostream>
#include <memory>
#include <vector>
using namespace std;

// Interface renamed to INotifier
class INotifier {
public:
  virtual void send(const string &message) const = 0;
  virtual ~INotifier() = default;
};

// Concrete implementation renamed to EmailNotifier
class EmailNotifier : public INotifier {
public:
  void send(const string &message) const override {
    cout << "Sending Email: " << message << endl;
  }
};

// Concrete implementation renamed to SMSNotifier
class SMSNotifier : public INotifier {
public:
  void send(const string &message) const override {
    cout << "Sending SMS: " << message << endl;
  }
};

class NotificationSender {
private:
  vector<shared_ptr<INotifier>> notifiers;

public:
  void addNotifier(const shared_ptr<INotifier> &notifier) {
    notifiers.push_back(notifier);
  }

  void notifyAll(const string &message) {
    for (const auto &notifier : notifiers) {
      notifier->send(message);
    }
  }
};

int main() {
  auto email = make_shared<EmailNotifier>();
  auto sms = make_shared<SMSNotifier>();
  NotificationSender sender;
  sender.addNotifier(email);
  sender.addNotifier(sms);
  sender.notifyAll("System update available!");
  return 0;
}
```

**Benefit**: Adding a new notification type only requires creating a new struct that implements `Notifier`.

---

### **3. Liskov Substitution Principle (LSP)**

**Definition**: Subtypes should be replaceable with their base types without altering the correctness of the program.

```cpp
#include <iostream>
#include <memory>
#include <vector>
using namespace std;

// interface IShape
class IShape {
public:
  virtual double area() const = 0; // Pure virtual function
  virtual ~IShape() = default;     // Virtual destructor
};

// Derived Class: Rectangle
class Rectangle : public IShape {
private:
  double width, height;

public:
  Rectangle(double w, double h) : width(w), height(h) {}
  double area() const override { return width * height; }
};

// Derived Class: Square
class Square : public IShape {
private:
  double side;

public:
  Square(double s) : side(s) {}
  double area() const override { return side * side; }
};

// Function to demonstrate LSP
void printAreas(const vector<shared_ptr<IShape>> &shapes) {
  for (const auto &shape : shapes) {
    cout << "Area: " << shape->area() << endl;
  }
}

int main() {
  // Create instances of Rectangle and Square
  auto rectangle = make_shared<Rectangle>(4.0, 5.0);
  auto square = make_shared<Square>(3.0);
  // Store them in a vector of IShape pointers
  vector<shared_ptr<IShape>> Ishapes = {rectangle, square};
  // LSP: Both Rectangle and Square can be treated as IShape
  printAreas(Ishapes);
  return 0;
}
```

- **Base Class**: Shape defines a virtual method area() for all derived shapes.
- **Derived Classes**: Specific shapes (Rectangle and Square) implement area() correctly and can replace the Shape base type without breaking the functionality.
- **LSP Compliance**: Any instance of Shape can be substituted with a Rectangle or Square without altering program correctness.

**What Happens If LSP Is Violated?**

- If a derived class (e.g., Square) incorrectly overrides the area() method, it might not conform to the expected behavior of the base class. This could lead to incorrect results when using polymorphism, violating LSP.

---

### **4. Interface Segregation Principle (ISP)**

**Definition**: A class should not be forced to implement interfaces it does not use.Instead, create smaller, specific interfaces.

**Scenario: Device Management System**

Consider a device management system where different types of devices have different capabilities:

- Printers can print.
- Scanners can scan.
- Multi-functional devices can print, scan, and fax.

**Violation of ISP**

A single `Device` interface with all methods (e.g., `print()`, `scan()`, `fax()`) would force all device classes to implement unused methods.

**Solution: Apply ISP**

Break the interface into smaller, role-specific interfaces: `IPrinter`, `IScanner`, and `IFax`.

```cpp
#include <iostream>
#include <memory>
using namespace std;

// Role-specific interfaces
class IPrinter {
public:
  virtual void print(const string &document) const = 0;
  virtual ~IPrinter() = default;
};

class IScanner {
public:
  virtual void scan(const string &document) const = 0;
  virtual ~IScanner() = default;
};

class IFax {
public:
  virtual void fax(const string &document) const = 0;
  virtual ~IFax() = default;
};

// Concrete classes implementing only relevant interfaces

class Printer : public IPrinter {
public:
  void print(const string &document) const override {
    cout << "Printing: " << document << endl;
  }
};

class Scanner : public IScanner {
public:
  void scan(const string &document) const override {
    cout << "Scanning: " << document << endl;
  }
};

class MultiFunctionDevice : public IPrinter, public IScanner, public IFax {
public:
  void print(const string &document) const override {
    cout << "Multi-function device printing: " << document << endl;
  }

  void scan(const string &document) const override {
    cout << "Multi-function device scanning: " << document << endl;
  }

  void fax(const string &document) const override {
    cout << "Multi-function device faxing: " << document << endl;
  }
};

// Client code
void performDeviceOperations() {
  auto printer = make_shared<Printer>();
  auto scanner = make_shared<Scanner>();
  auto mfd = make_shared<MultiFunctionDevice>();

  printer->print("Document 1");
  scanner->scan("Document 2");
  mfd->print("Document 3");
  mfd->scan("Document 4");
  mfd->fax("Document 5");
}

int main() {
  performDeviceOperations();
  return 0;
}
```

### **Explanation**

1. **Interface Segregation**:
   - `IPrinter`, `IScanner`, and `IFax` are small, focused interfaces, ensuring classes only implement the functionality they need.
2. **Concrete Classes**:
   - `Printer` implements only `IPrinter`.
   - `Scanner` implements only `IScanner`.
   - `MultiFunctionDevice` implements all three.
3. **Client Code**:
   - Uses the most specific interface for the required functionality, improving flexibility.

### **Benefits**

1. **Flexibility**: Easier to add new device types without modifying existing interfaces or classes.
2. **Clarity**: Classes are not bloated with irrelevant methods.
3. **Scalability**: Adding new capabilities is straightforward by creating new interfaces (e.g., `ICloudPrinter`).

### **5. Dependency Inversion Principle (DIP)**

**Definition**: High-level modules should not depend on low-level modules. Both should depend on abstractions.

```c++
#include <iostream>
#include <memory>
using namespace std;

class IPayment {
public:
  virtual void processPayment(double amount) = 0;
  virtual ~IPayment() = default;
};

class CreditCardPayment : public IPayment {
public:
  void processPayment(double amount) override {
    cout << "Processing credit card payment of $" << amount << endl;
  }
};

class PayPalPayment : public IPayment {
public:
  void processPayment(double amount) override {
    cout << "Processing PayPal payment of $" << amount << endl;
  }
};

class PaymentProcessor {
private:
  shared_ptr<IPayment> payment;

public:
  PaymentProcessor(shared_ptr<IPayment> p) : payment(p) {}

  void makePayment(double amount) { payment->processPayment(amount); }
};

int main() {
  auto creditCard = make_shared<CreditCardPayment>();
  PaymentProcessor processor(creditCard);
  processor.makePayment(100.0);

  auto payPal = make_shared<PayPalPayment>();
  processor = PaymentProcessor(payPal);
  processor.makePayment(200.0);

  return 0;
}
```

**Benefit**: The `PaymentProcessor` depends on an abstraction (`IPayment`), not specific implementations, making it flexible and extensible.

---

### Summary Table

| **Principle**         | **Core Idea**                                         | **Improvement**                                        |
| --------------------- | ----------------------------------------------------- | ------------------------------------------------------ |
| Single Responsibility | One class = one responsibility.                       | Reduces coupling and increases clarity.                |
| Open/Closed           | Open to extension, closed to modification.            | Easier to add features without changing core code.     |
| Liskov Substitution   | Subtypes must replace their base types seamlessly.    | Avoids unexpected behaviors in polymorphism.           |
| Interface Segregation | Use small, focused interfaces.                        | Prevents structs from implementing irrelevant methods. |
| Dependency Inversion  | Depend on abstractions, not concrete implementations. | Promotes loose coupling and testability.               |
