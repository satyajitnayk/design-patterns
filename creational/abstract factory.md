## **What is the Abstract Factory Pattern?**

The Abstract Factory Pattern is a creational design pattern that provides an interface for creating families of related or dependent objects without specifying their concrete classes. It helps in encapsulating the creation logic of different products, ensuring that related products are created together.

---

## **Why Use the Abstract Factory Pattern?**

1. **Flexibility**: Allows the creation of objects without being tightly coupled to specific classes.
2. **Consistency**: Ensures that families of related objects are used together (e.g., UI components for a single operating system).
3. **Scalability**: Adding new families of products requires minimal changes to the existing code.
4. **Encapsulation**: Encapsulates object creation logic, making the code cleaner and more modular.

---

### **Step 1: Define Product Interfaces**

```cpp
#include <iostream>
#include <memory>
using namespace std;

// Button interface (Product)
class Button {
public:
  virtual void render() = 0;
  virtual ~Button() {}
};

// Checkbox interface (Product)
class Checkbox {
public:
  virtual void check() = 0;
  virtual ~Checkbox() {}
};
```

---

### **Step 2: Create Concrete Products**

```cpp
class WindowsButton : public Button {
public:
  void render() override { cout << "Rendering Windows Button" << endl; }
};

// MacOS Button
class MacOSButton : public Button {
public:
  void render() override { cout << "Rendering MacOS Button" << endl; }
};

// Windows Checkbox
class WindowsCheckbox : public Checkbox {
public:
  void check() override { cout << "Checking Windows Checkbox" << endl; }
};

// MacOS Checkbox
class MacOSCheckbox : public Checkbox {
public:
  void check() override { cout << "Checking MacOS Checkbox" << endl; }
};
```

---

### **Step 3: Define the Abstract Factory Interface**

```cpp
// Abstract Factory Interface
class GUIFactory {
public:
  virtual unique_ptr<Button> createButton() = 0;
  virtual unique_ptr<Checkbox> createCheckbox() = 0;
  virtual ~GUIFactory() {}
};
```

---

### **Step 4: Create Concrete Factories**

```cpp
class WindowsFactory : public GUIFactory {
public:
  unique_ptr<Button> createButton() override {
    return make_unique<WindowsButton>();
  }
  unique_ptr<Checkbox> createCheckbox() override {
    return make_unique<WindowsCheckbox>();
  }
};

// MacOS Factory
class MacOSFactory : public GUIFactory {
public:
  unique_ptr<Button> createButton() override {
    return make_unique<MacOSButton>();
  }
  unique_ptr<Checkbox> createCheckbox() override {
    return make_unique<MacOSCheckbox>();
  }
};

// Factory Getter
unique_ptr<GUIFactory> getFactory(const string &platform) {
  if (platform == "windows") {
    return make_unique<WindowsFactory>();
  } else if (platform == "macos") {
    return make_unique<MacOSFactory>();
  }
  return nullptr;
}
```

---

### **Step 5: Client Code**

```cpp
int main() {
  // Using smart pointers for automatic memory management
  unique_ptr<GUIFactory> macOsFactory = getFactory("macos");

  // Use the factory to create products
  unique_ptr<Button> button = macOsFactory->createButton();
  unique_ptr<Checkbox> checkbox = macOsFactory->createCheckbox();

  // Render and check components
  button->render();
  checkbox->check();

  // No need to manually delete, smart pointers will handle cleanup
  return 0;
}
```

---

## **Key Points**

1. Abstract Factory ensures platform-specific UI components are created together.
2. Adding a new platform (e.g., Linux) involves creating new product implementations and a new factory, without changing the client code.
3. This pattern decouples object creation from the client, promoting flexibility and scalability.

---

**NOTE:**

> `Factory Method`: One method to create one product.
> `Abstract Factory`: A factory of factories to create families of related products.
