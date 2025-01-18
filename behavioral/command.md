### **Command Design Pattern in C++**

The **Command Design Pattern** encapsulates a request as an object, allowing you to parameterize objects with different requests, delay execution, or support undoable operations.

---

### **When to Use?**

- To decouple the sender of a request from its receiver.
- To implement undo/redo functionality.
- To queue requests or log their execution.
- When you need to encapsulate operations as objects for flexibility.

---

### **Key Components**

1. **Command Interface**: Declares a method for executing a command.
2. **Concrete Command**: Implements the `execute()` method by invoking the corresponding actions on a receiver.
3. **Receiver**: The object that performs the actual operation.
4. **Invoker**: Stores and invokes commands.
5. **Client**: Creates command objects and assigns them to the invoker.

---

```cpp
#include <iostream>
#include <memory>
#include <vector>
using namespace std;

// Command Interface
class ICommand {
public:
  virtual void execute() = 0;
  virtual ~ICommand() = default;
};

// Receiver
class Light {
public:
  void turnOn() { cout << "Light is ON\n"; }

  void turnOff() { cout << "Light is OFF\n"; }
};

// Concrete Command: Turn On
class TurnOnCommand : public ICommand {
private:
  Light *light;

public:
  TurnOnCommand(Light *light) : light(light) {}

  void execute() override { light->turnOn(); }
};

// Concrete Command: Turn Off
class TurnOffCommand : public ICommand {
private:
  Light *light;

public:
  TurnOffCommand(Light *light) : light(light) {}

  void execute() override { light->turnOff(); }
};

// Invoker
class RemoteControl {
private:
  vector<unique_ptr<ICommand>> commands;

public:
  void addCommand(unique_ptr<ICommand> command) {
    commands.push_back(std::move(command));
  }

  void executeCommands() {
    for (const auto &command : commands) {
      command->execute();
    }
    commands.clear(); // Clear after execution
  }
};

// Client
int main() {
  Light livingRoomLight;

  auto turnOn = make_unique<TurnOnCommand>(&livingRoomLight);
  auto turnOff = make_unique<TurnOffCommand>(&livingRoomLight);

  RemoteControl remote;
  remote.addCommand(std::move(turnOn));
  remote.addCommand(std::move(turnOff));

  cout << "Executing commands through remote control:\n";
  remote.executeCommands();

  return 0;
}
```

---

### **Explanation**

1. **Command Interface**:
   - Declares the `execute()` method.
2. **Concrete Command**:

   - Implements the `execute()` method by invoking specific operations on the `Light` (Receiver).

3. **Receiver**:

   - The `Light` class knows how to perform actions such as `turnOn` and `turnOff`.

4. **Invoker**:

   - The `RemoteControl` class stores a list of commands and executes them sequentially.

5. **Client**:
   - Creates the concrete commands and assigns them to the `RemoteControl`.

---

### **Advantages**

- **Decoupling**: Separates the request's sender and the logic that handles it.
- **Flexibility**: Allows easy addition of new commands without changing existing code.
- **Undo/Redo Support**: The pattern can be extended to add undo functionality.

---

### **Real-World Examples**

1. **GUI Buttons**:
   - Buttons in an application execute commands, like opening a file or saving data.
2. **Task Scheduling**:
   - Scheduling tasks for execution at a later time (e.g., cron jobs).

---

### **Enhancements**

- Add an undo stack for reversible commands.
- Use smart pointers to manage memory more efficiently.
