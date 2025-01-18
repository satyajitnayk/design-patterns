The **Chain of Responsibility** pattern is a behavioral design pattern that allows a request to pass through a chain of handlers. Each handler decides whether to process the request or pass it to the next handler in the chain.

---

### **What is the Chain of Responsibility Pattern?**

- **Decoupling**: The sender of a request is decoupled from its receiver(s).
- **Chain**: Multiple handlers are linked in a chain, and each handler decides whether to process the request.
- **Responsibility**: Each handler focuses only on its specific task.

---

### **Why Use the Chain of Responsibility?**

1. **Flexible Handling**: Easily add/remove/modify handlers without affecting the overall flow.
2. **Dynamic Chains**: Construct chains at runtime for dynamic request processing.
3. **Single Responsibility**: Each handler has a specific task, promoting clean code.

---

#### **Example: Support Ticket Processing**

```c++
#include <iostream>
#include <memory>
using namespace std;

class Handler {
protected:
  shared_ptr<Handler> next;

public:
  virtual void setNext(shared_ptr<Handler> nextHandler) { next = nextHandler; }
  virtual void handle(const string &request) {
    if (next) {
      next->handle(request);
    }
  }
  virtual ~Handler() = default;
};

class LevelOneSupport : public Handler {
public:
  void handle(const string &request) override {
    if (request == "password reset") {
      cout << "Level 1 Support: Handling password reset request." << endl;
    } else {
      cout << "Level 1 Support: Passing to Level 2." << endl;
      // explicitly calls the handle() method defined in the base class Handler
      // if you called this->handle(request) instead of
      // Handler::handle(request), it would lead to infinite recursion
      Handler::handle(request);
    }
  }
};

class LevelTwoSupport : public Handler {
public:
  void handle(const string &request) override {
    if (request == "network issue") {
      cout << "Level 2 Support: Handling network issue request." << endl;
    } else {
      cout << "Level 2 Support: Passing to Level 3." << endl;
      Handler::handle(request);
    }
  }
};

class LevelThreeSupport : public Handler {
public:
  void handle(const string &request) override {
    cout << "Level 3 Support: Handling advanced request: " << request << endl;
  }
};

// Main function
int main() {
  // Create handlers
  auto level1 = make_shared<LevelOneSupport>();
  auto level2 = make_shared<LevelTwoSupport>();
  auto level3 = make_shared<LevelThreeSupport>();

  // Set up the chain
  level1->setNext(level2);
  level2->setNext(level3);

  // Pass requests through the chain
  cout << "Request 1: Password Reset" << endl;
  level1->handle("password reset");

  cout << "\nRequest 2: Network Issue" << endl;
  level1->handle("network issue");

  cout << "\nRequest 3: Server Crash" << endl;
  level1->handle("server crash");

  return 0;
}
```

---

### Explanation:

1. **Handler Interface**:
   - The `Handler` class defines the interface for setting the next handler and processing the request.
   - The `handle` method forwards the request to the next handler if it exists.
2. **Concrete Handlers**:
   - `LevelOneSupport`, `LevelTwoSupport`, and `LevelThreeSupport` implement the `handle` method to process specific requests.
   - If a handler cannot process the request, it forwards the request to the next handler in the chain.
3. **Chain Setup**:
   - The handlers are connected using the `setNext` method, forming a chain of responsibility.
   - Requests are passed to the first handler (`level1`), which either handles the request or forwards it along the chain.

---

### **Output**

```
Request 1: Password Reset
Level 1 Support: Handling password reset request.

Request 2: Network Issue
Level 1 Support: Passing to Level 2.
Level 2 Support: Handling network issue request.

Request 3: Server Crash
Level 1 Support: Passing to Level 2.
Level 2 Support: Passing to Level 3.
Level 3 Support: Handling advanced request: server crash
```

---

### **Advantages**

1. **Decoupled Logic**: The sender does not know which handler will process the request.
2. **Extensibility**: Easily add or remove handlers without breaking the chain.
3. **Focus**: Handlers are specific to their task.

---

### **Disadvantages**

1. **Performance Overhead**: Long chains may slow down request processing.
2. **No Guarantee**: If no handler processes the request, it may go unhandled.

---

### **When to Use the Chain of Responsibility?**

- When multiple handlers could process a request.
- When the order of processing matters.
- When you want to decouple senders from receivers.
