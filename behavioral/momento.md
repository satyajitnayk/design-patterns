The **Memento Pattern** is a behavioral design pattern that allows you to capture and restore an object's state without exposing its internal details. It's useful for implementing undo/redo functionality or managing checkpoints in an application's state.

---

### **What is the Memento Pattern?**

- **Purpose**: Save the state of an object to restore it later.
- **Participants**:
  - **Originator**: The object whose state you want to save.
  - **Memento**: A snapshot of the state.
  - **Caretaker**: Manages mementos and interacts with the originator to save or restore state.

---

### **Why Use the Memento Pattern?**

1. **State Management**: Enables undo/redo or checkpoint functionality.
2. **Encapsulation**: Protects the internal state of an object from being accessed directly.
3. **Separation of Concerns**: Keeps state-saving logic separate from the object's main functionality.

---

#### **Example: Text Editor with Undo Feature**

```c++
#include <iostream>
#include <memory>
#include <string>
#include <vector>
using namespace std;

// Memento: Represents the saved state
class Memento {
public:
  Memento(const string &state) : state(state) {}
  string getState() const { return state; }

private:
  string state;
};

// Originator: Manages the internal state
class Editor {
public:
  void write(const string &text) { content += text; }

  string getContent() const { return content; }

  shared_ptr<Memento> save() const { return make_shared<Memento>(content); }

  void restore(const shared_ptr<Memento> &memento) {
    if (memento) {
      content = memento->getState();
    }
  }

private:
  string content;
};

// Caretaker: Manages the Mementos for undo and redo
class History {
public:
  void pushUndo(const shared_ptr<Memento> &memento) {
    undoHistory.push_back(memento);
    redoHistory.clear(); // Clear redo stack after a new operation
  }

  shared_ptr<Memento> popUndo() {
    if (undoHistory.empty()) {
      return nullptr;
    }
    auto last = undoHistory.back();
    undoHistory.pop_back();
    return last;
  }

  void pushRedo(const shared_ptr<Memento> &memento) {
    redoHistory.push_back(memento);
  }

  shared_ptr<Memento> popRedo() {
    if (redoHistory.empty()) {
      return nullptr;
    }
    auto last = redoHistory.back();
    redoHistory.pop_back();
    return last;
  }

  bool hasUndo() const { return !undoHistory.empty(); }

  bool hasRedo() const { return !redoHistory.empty(); }

private:
  vector<std::shared_ptr<Memento>> undoHistory;
  vector<std::shared_ptr<Memento>> redoHistory;
};

// Main function
int main() {
  Editor editor;
  History history;

  // Write some content
  editor.write("Hello, ");
  history.pushUndo(editor.save());

  editor.write("World!");
  history.pushUndo(editor.save());

  editor.write(" This is a test.");
  cout << "Current Content: " << editor.getContent()
       << endl; // Output: Hello, World! This is a test.

  // Undo last action
  auto lastUndo = history.popUndo();
  if (lastUndo) {
    history.pushRedo(editor.save());
    editor.restore(lastUndo);
  }
  cout << "After Undo: " << editor.getContent()
       << endl; // Output: Hello, World!

  // Undo another action
  lastUndo = history.popUndo();
  if (lastUndo) {
    history.pushRedo(editor.save());
    editor.restore(lastUndo);
  }
  cout << "After Another Undo: " << editor.getContent()
       << endl; // Output: Hello,

  // Redo last undone action
  auto lastRedo = history.popRedo();
  if (lastRedo) {
    history.pushUndo(editor.save());
    editor.restore(lastRedo);
  }
  cout << "After Redo: " << editor.getContent()
       << endl; // Output: Hello, World!

  // Redo another undone action
  lastRedo = history.popRedo();
  if (lastRedo) {
    history.pushUndo(editor.save());
    editor.restore(lastRedo);
  }
  cout << "After Another Redo: " << editor.getContent()
       << endl; // Output: Hello, World! This is a test.

  return 0;
}
```

---

### **Explanation**

- Undo: Pops a Memento from the undoHistory stack, restores the state in the editor, and pushes the current state to the redoHistory.
- Redo: Pops a Memento from the redoHistory stack, restores the state in the editor, and pushes the current state to the undoHistory.
- The code demonstrates the Memento Pattern to implement undo and redo functionality. The `Editor` class manages the content and can save its state in a `Memento`. The `History` class handles storing and retrieving these mementos for undo and redo actions. Undo operations are tracked in an undo stack, while redo actions are stored separately in a redo stack, allowing content restoration in both directions.

---

### **Advantages**

1. **Encapsulation**: The internal state of the originator is not exposed.
2. **Flexibility**: Allows undo/redo functionality without affecting other code.
3. **Separation of Concerns**: The caretaker handles state management, leaving the originator focused on its logic.

---

### **Disadvantages**

1. **Memory Usage**: Large or frequent mementos can increase memory consumption.
2. **Complexity**: Managing mementos may become complicated if the number of states is high.

---

### **When to Use the Memento Pattern?**

- When implementing undo/redo functionality.
- When needing to save checkpoints in a process.
- When preserving an object's state without exposing its details.
