The **Mediator Pattern** is a behavioral design pattern that promotes loose coupling by preventing direct communication between components (colleagues). Instead, components communicate through a mediator that centralizes interaction logic.

---

### **What is the Mediator Pattern?**

- **Centralized Communication**: All communication between components is routed through a mediator.
- **Decoupling**: Components are independent of each other and only depend on the mediator.
- **Coordination**: The mediator encapsulates how objects interact.

---

### **Why Use the Mediator Pattern?**

1. **Simplifies Object Relationships**: Avoids complex dependencies between components.
2. **Centralizes Logic**: Interaction logic is placed in one class, improving maintainability.
3. **Decoupling**: Components become reusable and testable since they are unaware of each other.

---

#### **Example: Chatroom Communication**

```c++
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
using namespace std;

// Forward declaration of User
class User;

// Mediator Interface
class Mediator {
public:
  virtual ~Mediator() = default;
  virtual void sendMessage(const string &sender, const string &message) = 0;
  virtual void registerUser(const string &name, shared_ptr<User> user) = 0;
};

// Concrete Mediator
class ChatRoom : public Mediator {
public:
  void sendMessage(const string &sender, const string &message) override;

  void registerUser(const string &name, shared_ptr<User> user) override {
    users[name] = user;
  }

private:
  unordered_map<string, shared_ptr<User>> users;
};

// Colleague
class User {
public:
  User(const string &name, shared_ptr<Mediator> mediator)
      : name(name), mediator(mediator) {}

  void sendMessage(const string &message) {
    cout << name << " sends: " << message << endl;
    mediator->sendMessage(name, message);
  }

  void receiveMessage(const string &sender, const string &message) {
    cout << name << " receives from " << sender << ": " << message << endl;
  }

private:
  string name;
  shared_ptr<Mediator> mediator;
};

void ChatRoom::sendMessage(const string &sender, const string &message) {
  for (const auto &[name, user] : users) {
    if (name != sender) {
      user->receiveMessage(sender, message);
    }
  }
}

// Main function
int main() {
  auto chatRoom = make_shared<ChatRoom>();

  // Create users and register them with the chatroom
  auto alice = make_shared<User>("Alice", chatRoom);
  auto bob = make_shared<User>("Bob", chatRoom);
  auto charlie = make_shared<User>("Charlie", chatRoom);

  chatRoom->registerUser("Alice", alice);
  chatRoom->registerUser("Bob", bob);
  chatRoom->registerUser("Charlie", charlie);

  // Users send messages
  alice->sendMessage("Hi, everyone!");
  bob->sendMessage("Hey Alice!");
  charlie->sendMessage("Hello Alice and Bob!");

  return 0;
}
```

---

### Explanation

1. **Mediator Interface**:

   - `Mediator` defines the interface for sending messages and registering users.

2. **Concrete Mediator (`ChatRoom`)**:

   - Manages a collection of users (`std::unordered_map`).
   - Implements `sendMessage` to broadcast messages to all users except the sender.
   - Implements `registerUser` to add users to the chat room.

3. **Colleague (`User`)**:

   - Represents a user in the chat room.
   - Sends messages via the `Mediator` and receives messages through the mediator.

4. **Usage**:
   - Users are created with a reference to the mediator (`ChatRoom`).
   - Each user registers itself with the chat room.
   - When a user sends a message, the chat room ensures other users receive it.

---

### **Output**

```
Alice sends: Hi, everyone!
Bob receives from Alice: Hi, everyone!
Charlie receives from Alice: Hi, everyone!

Bob sends: Hey Alice!
Alice receives from Bob: Hey Alice!
Charlie receives from Bob: Hey Alice!

Charlie sends: Hello Alice and Bob!
Alice receives from Charlie: Hello Alice and Bob!
Bob receives from Charlie: Hello Alice and Bob!
```

---

### **Advantages**

1. **Reduces Dependencies**: Components don’t reference each other directly.
2. **Centralized Control**: The mediator encapsulates interaction logic, making it easier to maintain.
3. **Reusability**: Components are independent and reusable.

---

### **Disadvantages**

1. **Mediator Complexity**: As the number of interactions increases, the mediator can become complex.
2. **Single Point of Failure**: The mediator is critical; if it fails, the entire system can break.

---

### **When to Use the Mediator Pattern?**

- When components have many-to-many relationships.
- When interaction logic is complex and needs centralization.
- When you want to reduce coupling between components.
