The **Decorator Pattern** is a structural design pattern that dynamically adds behavior or responsibilities to objects without altering their structure. This pattern uses composition rather than inheritance to extend functionality.

---

### **What is the Decorator Pattern?**

- **Dynamic Behavior**: Enhances objects dynamically at runtime.
- **Composition Over Inheritance**: Wraps an object with additional behavior by embedding it within a decorator.

---

### **Why Use the Decorator Pattern?**

1. **Flexible Extension**: Add features dynamically without modifying existing classes.
2. **Adheres to Open/Closed Principle**: Allows extensions without changing existing code.
3. **Layered Behavior**: Combine multiple decorators for complex behavior.

---

### **Go Implementation**

Go supports the Decorator Pattern effectively using interfaces and composition.

---

#### **Basic Example: Text Formatting**

```c++
#include <iostream>
#include <memory>
using namespace std;

// Component interface
class Text {
public:
  virtual string Render() const = 0;
  virtual ~Text() {}
};

// Concrete Component: PlainText
class PlainText : public Text {
private:
  string content;

public:
  PlainText(const string &content) : content(content) {}

  string Render() const override { return content; }
};

// Decorator: Bold
class BoldText : public Text {
private:
  shared_ptr<Text> text;

public:
  BoldText(shared_ptr<Text> text) : text(text) {}

  string Render() const override { return "<b>" + text->Render() + "</b>"; }
};

// Decorator: Italic
class ItalicText : public Text {
private:
  shared_ptr<Text> text;

public:
  ItalicText(shared_ptr<Text> text) : text(text) {}

  string Render() const override { return "<i>" + text->Render() + "</i>"; }
};

int main() {
  // Create plain text
  shared_ptr<Text> plain = make_shared<PlainText>("Hello, World!");

  // Apply decorators
  shared_ptr<Text> bold = make_shared<BoldText>(plain);
  shared_ptr<Text> italic = make_shared<ItalicText>(bold);

  // Render the final output
  cout << italic->Render() << endl;

  return 0;
}
```

---

### **Advantages**

1. **Dynamic Behavior**: Add or remove features without changing the original class.
2. **Composable**: Stack multiple decorators to create complex behaviors.
3. **Adheres to SOLID**: Particularly the Open/Closed Principle.

---

### **Disadvantages**

1. **Complexity**: Too many decorators can make code harder to read and debug.
2. **Order Dependency**: The behavior of decorators may depend on their stacking order.

---

### **When to Use the Decorator Pattern?**

- When you need to dynamically add functionality to objects.
- When you want to avoid a complex hierarchy of subclasses.
- When features need to be optional and composable (e.g., middleware in web servers).
