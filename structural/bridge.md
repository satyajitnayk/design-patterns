The **Bridge Pattern** is a structural design pattern that separates the abstraction from its implementation so that both can evolve independently. It is useful when you need to decouple tightly bound abstractions and their implementations.

---

### **What is the Bridge Pattern?**

The pattern introduces two hierarchies:

1. **Abstraction**: Represents the high-level logic.
2. **Implementation**: Handles the low-level details.

These hierarchies are connected via a "bridge" (interface), allowing changes to one hierarchy without affecting the other.

---

### **Why Use the Bridge Pattern?**

1. **Decoupling**: Separates abstraction from implementation.
2. **Flexibility**: Changes to abstraction or implementation are independent.
3. **Scalability**: Makes it easier to extend either hierarchy without modifying existing code.
4. **Avoid Explosion of Classes**: Prevents combinatorial growth of subclasses for multiple dimensions of variation.

---

### **Practical Example: Notification System**

Imagine you’re designing a system for drawing shapes on different platforms (like Windows and macOS), and you want to draw shapes like circles and rectangles. Without the Bridge pattern, you'd need separate classes for each combination (e.g., WindowsCircle, MacOSCircle, WindowsRectangle, MacOSRectangle), leading to an explosion of classes.

Using the Bridge pattern:

- Shape becomes the abstraction that defines common operations (like draw()).
- DrawingAPI becomes the implementation that defines how to draw on each platform (e.g., WindowsDrawingAPI and MacOSDrawingAPI).
- Both the Shape and DrawingAPI can evolve independently.

```c++
#include <iostream>
#include <memory>
using namespace std;

// Implementor (Platform-specific drawing API)
class IDrawingAPI {
public:
  virtual void drawCircle(int x, int y, int radius) = 0;
  virtual ~IDrawingAPI() {}
};

// Concrete Implementor 1 (Windows Drawing)
class WindowsDrawingAPI : public IDrawingAPI {
public:
  void drawCircle(int x, int y, int radius) override {
    cout << "Drawing circle on Windows at (" << x << ", " << y
         << ") with radius " << radius << endl;
  }
};

// Concrete Implementor 2 (MacOS Drawing)
class MacOSDrawingAPI : public IDrawingAPI {
public:
  void drawCircle(int x, int y, int radius) override {
    cout << "Drawing circle on MacOS at (" << x << ", " << y << ") with radius "
         << radius << endl;
  }
};

// Abstraction (Shape)
class IShape {
protected:
  unique_ptr<IDrawingAPI> drawingAPI; // The Implementor reference

public:
  IShape(unique_ptr<IDrawingAPI> drawingAPI)
      : drawingAPI(std::move(drawingAPI)) {}
  virtual void draw() = 0;             // High-level operation
  virtual void resize(int radius) = 0; // Another high-level operation
  virtual ~IShape() {}
};

// Refined Abstraction (Circle)
class Circle : public IShape {
private:
  int x, y, radius;

public:
  Circle(int x, int y, int radius, unique_ptr<IDrawingAPI> drawingAPI)
      : IShape(std::move(drawingAPI)), x(x), y(y), radius(radius) {}

  void draw() override {
    drawingAPI->drawCircle(
        x, y, radius); // Delegate the drawing to the Implementation
  }

  void resize(int radius) override { this->radius = radius; }
};

// Client code
int main() {
  // Create a Circle object with a Windows drawing API using unique_ptr
  auto windowsAPI = make_unique<WindowsDrawingAPI>();
  unique_ptr<IShape> shape =
      make_unique<Circle>(5, 10, 20, std::move(windowsAPI));

  shape->draw(); // Drawing on Windows

  // Switch to MacOS drawing API without modifying the Shape class
  auto macAPI = make_unique<MacOSDrawingAPI>();
  shape = make_unique<Circle>(5, 10, 20, std::move(macAPI));
  shape->draw(); // Drawing on MacOS

  // No need to manually delete objects, unique_ptr takes care of cleanup
  return 0;
}
```

---

### **When to Use the Bridge Pattern?**

- When you want to decouple an abstraction from its implementation.
- When you have multiple dimensions of variation (e.g., notification types and communication channels).
- When changes to one hierarchy (e.g., senders) should not affect the other (e.g., notification types).

### Summary:

The Bridge Pattern allows you to separate the abstraction and implementation so that both can evolve independently. It’s particularly useful when you have multiple types of abstractions that can work with multiple implementations, like in systems requiring platform-specific behavior (e.g., drawing on different devices).
