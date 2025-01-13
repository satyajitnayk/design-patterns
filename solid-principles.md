The **SOLID principles** are five design principles that help developers write clean, maintainable, and scalable object-oriented code. These principles are:

1. **S**: **Single Responsibility Principle (SRP)**
2. **O**: **Open/Closed Principle (OCP)**
3. **L**: **Liskov Substitution Principle (LSP)**
4. **I**: **Interface Segregation Principle (ISP)**
5. **D**: **Dependency Inversion Principle (DIP)**

Here’s an explanation of each principle along with C++ examples.

---

### 1. **Single Responsibility Principle (SRP)**

**Definition**: A class should have one and only one reason to change. This means a class should have only one responsibility.

#### Example Without SRP:

```cpp
#include <iostream>
#include <fstream>
using namespace std;

class Logger {
public:
    void logToFile(conststring& message) {
        ofstream file("log.txt", ios::app);
        file << message << endl;
        file.close();
    }
};
```

**Problem**: `Logger` handles both message generation and file writing.

#### Example With SRP:

```cpp
#include <iostream>
#include <fstream>
using namespace std;

class Message {
public:
    string generateMessage(const string& content) {
        return "[LOG]: " + content;
    }
};

class FileWriter {
public:
    void writeToFile(const string& message, const string& filename) {
        ofstream file(filename, ios::app);
        file << message << endl;
        file.close();
    }
};

int main() {
    Message msg;
    FileWriter writer;
    string log = msg.generateMessage("System started");
    writer.writeToFile(log, "log.txt");
    return 0;
}
```

**Benefit**: `Message` generates content, and `FileWriter` handles file writing. Both have distinct responsibilities.

---

### 2. **Open/Closed Principle (OCP)**

**Definition**: A class should be open for extension but closed for modification. You should be able to add new functionality without changing existing code.

#### Example Without OCP:

```cpp
#include <iostream>
using namespace std;

class Notification {
public:
    void sendNotification(const string& type, const string& message) {
        if (type == "email") {
            cout << "Sending Email: " << message << endl;
        } else if (type == "sms") {
            cout << "Sending SMS: " << message << endl;
        }
    }
};

```

**Problem**: Adding a new notification type requires modifying the `sendNotification` method.

#### Example With OCP:

```cpp
#include <iostream>
#include <memory>
#include <vector>
using namespace std;

class Notification {
public:
    virtual void send(const string& message) const = 0;
    virtual ~Notification() = default;
};

class EmailNotification : public Notification {
public:
    void send(const string& message) const override {
        cout << "Sending Email: " << message << endl;
    }
};

class SMSNotification : public Notification {
public:
    void send(const string& message) const override {
        cout << "Sending SMS: " << message << endl;
    }
};

class NotificationSender {
private:
    vector<shared_ptr<Notification>> notifications;
public:
    void addNotification(const shared_ptr<Notification>& notification) {
        notifications.push_back(notification);
    }

    void notifyAll(const string& message) {
        for (const auto& notification : notifications) {
            notification->send(message);
        }
    }
};

int main() {
    auto email = make_shared<EmailNotification>();
    auto sms = make_shared<SMSNotification>();
    NotificationSender sender;
    sender.addNotification(email);
    sender.addNotification(sms);
    sender.notifyAll("System update available!");
    return 0;
}
```

**Benefit**: Adding a new notification type (e.g., PushNotification) doesn’t require modifying `NotificationSender`.

### 3. **Liskov Substitution Principle (LSP)**

**Definition**: Subtypes should work everywhere their base types are used without breaking the program or changing its expected behavior.

```cpp
#include <iostream>
#include <vector>
#include <memory>
using namespace std;

// Base Class
class Shape {
public:
    virtual double area() const = 0; // Pure virtual function
    virtual ~Shape() = default;     // Virtual destructor
};

// Derived Class: Rectangle
class Rectangle : public Shape {
private:
    double width, height;
public:
    Rectangle(double w, double h) : width(w), height(h) {}
    double area() const override {
        return width * height;
    }
};

// Derived Class: Square
class Square : public Shape {
private:
    double side;
public:
    Square(double s) : side(s) {}
    double area() const override {
        return side * side;
    }
};

// Function to demonstrate LSP
void printAreas(const vector<shared_ptr<Shape>>& shapes) {
    for (const auto& shape : shapes) {
        cout << "Area: " << shape->area() << endl;
    }
}

int main() {
    // Create instances of Rectangle and Square
    auto rectangle = make_shared<Rectangle>(4.0, 5.0);
    auto square = make_shared<Square>(3.0);

    // Store them in a vector of Shape pointers
    vector<shared_ptr<Shape>> shapes = {rectangle, square};

    // LSP: Both Rectangle and Square can be treated as Shape
    printAreas(shapes);

    return 0;
}
```

- **Base Class**: Shape defines a virtual method area() for all derived shapes.
- **Derived Classes**: Specific shapes (Rectangle and Square) implement area() correctly and can replace the Shape base type without breaking the functionality.
- **LSP Compliance**: Any instance of Shape can be substituted with a Rectangle or Square without altering program correctness.

**What Happens If LSP Is Violated?**

- If a derived class (e.g., Square) incorrectly overrides the area() method, it might not conform to the expected behavior of the base class. This could lead to incorrect results when using polymorphism, violating LSP.

---

### 4. **Interface Segregation Principle (ISP)**

**Definition**: A class should not be forced to implement interfaces it does not use. Instead, create smaller, specific interfaces.

#### Example Violating ISP:

```cpp
class Animal {
public:
    virtual void fly() = 0;
    virtual void swim() = 0;
    virtual void run() = 0;
};
```

**Problem**: A `Dog` does not need to implement `fly()`, but it is forced to.

#### Example Following ISP:

```cpp
class Flyable {
public:
    virtual void fly() = 0;
    virtual ~Flyable() = default;
};

class Swimable {
public:
    virtual void swim() = 0;
    virtual ~Swimable() = default;
};

class Runnable {
public:
    virtual void run() = 0;
    virtual ~Runnable() = default;
};

class Dog : public Runnable {
public:
    void run() override {cout << "Dog is running" <<endl; }
};

class Bird : public Flyable {
public:
    void fly() override {cout << "Bird is flying" <<endl; }
};
```

**Benefit**: Classes implement only the methods relevant to them.

### 5. **Dependency Inversion Principle (DIP)**

**Definition**: High-level modules should not depend on low-level modules. Both should depend on abstractions.

```c++
#include <iostream>
#include <memory>
using namespace std;

class Payment {
public:
    virtual void processPayment(double amount) = 0;
    virtual ~Payment() = default;
};

class CreditCardPayment : public Payment {
public:
    void processPayment(double amount) override {
        cout << "Processing credit card payment of $" << amount << endl;
    }
};

class PayPalPayment : public Payment {
public:
    void processPayment(double amount) override {
        cout << "Processing PayPal payment of $" << amount << endl;
    }
};

class PaymentProcessor {
private:
    shared_ptr<Payment> payment;
public:
    PaymentProcessor(shared_ptr<Payment> p) : payment(p) {}

    void makePayment(double amount) {
        payment->processPayment(amount);
    }
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

**Benefit**: The `PaymentProcessor` depends on an abstraction (`Payment`), not specific implementations, making it flexible and extensible.

---

### Summary Table

| **Principle**         | **Core Idea**                                         | **Improvement**                                        |
| --------------------- | ----------------------------------------------------- | ------------------------------------------------------ |
| Single Responsibility | One class = one responsibility.                       | Reduces coupling and increases clarity.                |
| Open/Closed           | Open to extension, closed to modification.            | Easier to add features without changing core code.     |
| Liskov Substitution   | Subtypes must replace their base types seamlessly.    | Avoids unexpected behaviors in polymorphism.           |
| Interface Segregation | Use small, focused interfaces.                        | Prevents classes from implementing irrelevant methods. |
| Dependency Inversion  | Depend on abstractions, not concrete implementations. | Promotes loose coupling and testability.               |
