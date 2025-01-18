The **Strategy Pattern** is a behavioral design pattern that defines a family of algorithms, encapsulates each one, and makes them interchangeable. This allows the algorithm to vary independently from the clients that use it.

---

### **What is the Strategy Pattern?**

- **Purpose**: Enables selecting an algorithm's behavior at runtime.
- **Participants**:
  - **Context**: Maintains a reference to a strategy object.
  - **Strategy Interface**: Common interface for all supported algorithms.
  - **Concrete Strategies**: Implement the strategy interface with specific behaviors.

---

### **Why Use the Strategy Pattern?**

1. **Flexibility**: Easily switch between algorithms at runtime.
2. **Decoupling**: Separates the algorithm implementation from the client.
3. **Reusability**: Algorithms can be reused across different contexts.

#### **Example: Payment System**

```c++
#include <iostream>
#include <memory>
#include <string>
using namespace std;

// Strategy Interface
class IPayment {
public:
  virtual void Pay(double amount) = 0;
  virtual ~IPayment() = default;
};

// Concrete Strategy: Credit Card Payment
class CreditCardPayment : public IPayment {
private:
  string cardNumber;

public:
  CreditCardPayment(const string &cardNumber) : cardNumber(cardNumber) {}

  void Pay(double amount) override {
    cout << "Paid " << amount << " using Credit Card " << cardNumber << "."
         << endl;
  }
};

// Concrete Strategy: PayPal Payment
class PayPalPayment : public IPayment {
private:
  string email;

public:
  PayPalPayment(const string &email) : email(email) {}

  void Pay(double amount) override {
    cout << "Paid " << amount << " using PayPal account " << email << "."
         << endl;
  }
};

// Context
class PaymentProcessor {
private:
  unique_ptr<IPayment> strategy;

public:
  void SetStrategy(unique_ptr<IPayment> newStrategy) {
    strategy = std::move(newStrategy);
  }

  void ExecutePayment(double amount) {
    if (!strategy) {
      cout << "Payment strategy not set!" << endl;
      return;
    }
    strategy->Pay(amount);
  }
};

int main() {
  // Create a payment processor (context)
  PaymentProcessor paymentProcessor;

  // Pay using Credit Card
  auto creditCard = make_unique<CreditCardPayment>("1234-5678-9012-3456");
  paymentProcessor.SetStrategy(std::move(creditCard));
  paymentProcessor.ExecutePayment(100.00);

  // Pay using PayPal
  auto payPal = make_unique<PayPalPayment>("user@example.com");
  paymentProcessor.SetStrategy(std::move(payPal));
  paymentProcessor.ExecutePayment(200.00);

  return 0;
}
```

---

### **Advantages**

1. **Open/Closed Principle**: Add new strategies without modifying existing code.
2. **Runtime Flexibility**: Change algorithms dynamically.
3. **Code Reusability**: Algorithms are encapsulated into separate classes.

---

### **Disadvantages**

1. **Increased Complexity**: More classes/interfaces may increase complexity.
2. **Overhead**: Switching strategies at runtime can be less efficient.

---

### **When to Use the Strategy Pattern?**

- When you need to choose from multiple algorithms dynamically.
- When you want to isolate complex algorithm logic from the client.
- When the client should not be aware of specific algorithm implementations.
