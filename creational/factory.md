## What is the Factory Pattern?

The Factory Design Pattern is a creational design pattern that provides an interface for creating objects in a superclass but allows subclasses to alter the type of objects that will be created. It helps encapsulate the object creation logic, making the code more maintainable and scalable.

## Why Use the Factory Pattern?

1. **Encapsulation of Object Creation Logic**: Centralizes object creation, making it easier to manage and update.
2. **Decoupling**: Reduces the dependency between client code and specific implementations.
3. **Scalability**: Adding new types of objects becomes straightforward without modifying existing code.

---

## Practical Example: Payment Processing System

Imagine a system that processes different types of payments such as Credit Card, PayPal, and Bank Transfer. Using the Factory Pattern, we can centralize the creation of payment objects.

### Implementation

```cpp
#include <iostream>
#include <memory>
#include <string>
using namespace std;

// Step 1: Define an abstract base class for Payment
class IPayment {
public:
  virtual void processPayment(double amount) const = 0;
  virtual ~IPayment() = default;
};

// Step 2: Implement concrete classes for each payment method
class CreditCardPayment : public IPayment {
public:
  void processPayment(double amount) const override {
    cout << "Processing Credit Card Payment of $" << amount << endl;
  }
};

class PayPalPayment : public IPayment {
public:
  void processPayment(double amount) const override {
    cout << "Processing PayPal Payment of $" << amount << endl;
  }
};

class BankTransferPayment : public IPayment {
public:
  void processPayment(double amount) const override {
    cout << "Processing Bank Transfer Payment of $" << amount << endl;
  }
};

// Step 3: Create a PaymentFactory to generate Payment objects
class PaymentFactory {
public:
  static shared_ptr<IPayment> createPayment(const string &type) {
    if (type == "CreditCard") {
      return make_shared<CreditCardPayment>();
    } else if (type == "PayPal") {
      return make_shared<PayPalPayment>();
    } else if (type == "BankTransfer") {
      return make_shared<BankTransferPayment>();
    } else {
      throw invalid_argument("Unknown payment type");
    }
  }
};

// Step 4: Use the factory in the main function
int main() {
  try {
    auto payment = PaymentFactory::createPayment("CreditCard");
    payment->processPayment(150.00);

    payment = PaymentFactory::createPayment("PayPal");
    payment->processPayment(200.00);

    payment = PaymentFactory::createPayment("BankTransfer");
    payment->processPayment(300.00);
  } catch (const exception &e) {
    cerr << "Error: " << e.what() << endl;
  }

  return 0;
}
```

---

### Explanation

1. **Base Class**: `Payment` defines the interface for all payment methods.
2. **Concrete Implementations**: `CreditCardPayment`, `PayPalPayment`, and `BankTransferPayment` provide specific implementations.
3. **Factory Class**: `PaymentFactory` encapsulates the creation logic, returning the appropriate object based on input.
4. **Client Code**: The `main` function uses the factory to create and use payment objects without needing to know their implementation details.

---

## Benefits in Production

1. **Ease of Maintenance**: New payment methods can be added without changing existing client code.
2. **Centralized Logic**: All creation logic is centralized, reducing duplication.
3. **Testability**: Easy to mock factory methods for testing purposes.

---

## How to Extend?

To add a new payment method:

1. Create a new class inheriting from `Payment`.
2. Update the `PaymentFactory` to include the new type.

## Common Interview Questions:

1. **What problem does the Factory Pattern solve?**

   - It abstracts the instantiation process, making the system more modular and extensible.

2. **How is the Factory Pattern different from Builder or Singleton?**

   - Factory focuses on object creation.
   - Builder constructs complex objects step by step.
   - Singleton ensures a single instance of a class.

3. **Real-world examples of Factory Pattern?**

   - **Java**: `Calendar.getInstance()`
   - **C++ STL**: `std::make_shared`, `std::make_unique`.

4. **How does it promote Open/Closed Principle?**

   - Factories allow new object types to be added without modifying existing creation logic.

5. **What are some alternatives to the Factory Pattern?**
   - Dependency Injection
   - Prototype Pattern (for cloning objects)
