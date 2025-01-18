The **Flyweight** design pattern is a structural design pattern that aims to minimize memory usage by sharing common data across multiple objects, instead of creating new objects for each instance with similar data. It is particularly useful when working with large numbers of objects that have some common state, reducing memory footprint and improving performance.

### Key Concepts of the Flyweight Pattern:

- **Intrinsic State**: The state that is shared among all instances. This state is independent of the object’s context and can be stored once and reused.
- **Extrinsic State**: The state that can vary between objects. This is passed to the object from the outside as needed, often by the client.
- **Flyweight Factory**: The object responsible for managing the shared instances and ensuring that no duplicate objects are created.

### When to Use Flyweight Pattern:

- When an application needs to create a large number of objects that have similar data.
- When memory usage needs to be optimized by sharing common data across many instances.
- When object creation overhead is high due to the duplication of common data.

### Problem Statement:

- Imagine a system that manages a large number of cars. Each car has a model, color, and position. The model and engine type are shared across many cars, but the color and position are unique to each individual car.

- We'll apply the Flyweight pattern to avoid creating duplicate objects for the model and engine, sharing these common properties across multiple car objects.

#### Step 1: Define the Flyweight

```cpp
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
using namespace std;

// Flyweight Interface
class ICarModel {
public:
  virtual void display(const string &color, const string &position) = 0;
  virtual ~ICarModel() {}
};

//  Flyweight
class CarModel : public ICarModel {
private:
  string model;
  string engineType;

public:
  CarModel(const string &model, const string &engineType)
      : model(model), engineType(engineType) {}

  void display(const string &color, const string &position) override {
    cout << "Car Model: " << model << " | Engine Type: " << engineType
         << " | Color: " << color << " | Position: " << position << endl;
  }
};

// Flyweight Factory
class CarModelFactory {
private:
  unordered_map<string, shared_ptr<ICarModel>> carModels;

public:
  shared_ptr<ICarModel> getCarModel(const string &model,
                                    const string &engineType) {
    string key = model + engineType;

    // If car model already exists, return the shared instance
    if (carModels.find(key) != carModels.end()) {
      return carModels[key];
    }

    // Otherwise, create a new model and store it in the map
    shared_ptr<ICarModel> newCarModel =
        make_shared<CarModel>(model, engineType);
    carModels[key] = newCarModel;
    return newCarModel;
  }
};

// Client Class
class Car {
private:
  shared_ptr<ICarModel> carModel;
  string color;
  string position;

public:
  Car(const shared_ptr<ICarModel> &carModel, const string &color,
      const string &position)
      : carModel(carModel), color(color), position(position) {}

  void display() { carModel->display(color, position); }
};

int main() {
  CarModelFactory carFactory;

  // Creating shared CarModels
  auto carModel1 = carFactory.getCarModel("Sedan", "V8");
  auto carModel2 = carFactory.getCarModel("SUV", "V6");
  auto carModel3 = carFactory.getCarModel(
      "Sedan", "V8"); // Reuses the same model as carModel1

  // Creating unique cars with different colors and positions
  Car car1(carModel1, "Red", "Parking Lot A");
  Car car2(carModel2, "Blue", "Parking Lot B");
  Car car3(carModel1, "Green", "Parking Lot C");

  // Displaying car details
  car1.display();
  car2.display();
  car3.display();

  return 0;
}
```

### Explanation of the Code:

1. **CarModel (Flyweight Interface)**:

   - This is the interface that defines the `display()` method, which is used to show car details like color and position.

2. **ConcreteCarModel (Flyweight)**:

   - This class implements the `CarModel` interface and holds the intrinsic state of the car — the `model` and `engineType`.
   - These properties are shared across all cars with the same model and engine type.

3. **CarModelFactory**:

   - This is the factory that manages the shared `CarModel` objects. It checks if the `CarModel` already exists in a map (`unordered_map`). If it does, it returns the existing instance; otherwise, it creates a new one and stores it for future use.

4. **Car**:
   - This class holds the extrinsic state — the car's `color` and `position`, which are unique to each instance.
   - It uses a shared `CarModel` object and adds the extrinsic state to it via the `display()` method.

### Why the Flyweight Pattern is Useful Here:

- **Memory Efficiency**: The `CarModel` objects are shared across multiple `Car` instances. For instance, the `Sedan` model with a `V8` engine is shared between `car1` and `car3`, which saves memory and avoids duplication.
- **Performance**: Instead of creating a new `CarModel` for every car, the factory pattern ensures that common car models are reused, which reduces object creation overhead.
- **Scalability**: If the system needed to manage thousands or millions of cars, the **Flyweight** pattern would ensure that only unique attributes (color, position) consume memory, while shared properties (model, engine) are reused.

### Benefits of Flyweight Pattern:

- **Memory efficiency**: Flyweight pattern helps reduce memory usage by sharing common data between objects.
- **Performance optimization**: Reduces the overhead of creating duplicate objects with the same intrinsic state.

### When Not to Use:

- If objects do not share common data, applying the Flyweight pattern will be an unnecessary complexity.
- If the extrinsic state is complex and frequently changes, it might be difficult to maintain and use the Flyweight pattern effectively.

In summary, the **Flyweight Pattern** is beneficial when dealing with large numbers of objects that share similar data, allowing you to optimize memory usage and improve performance by sharing common state across instances.

## few real-world examples of the **Flyweight** pattern and its practical applications:

### 1. **Text Rendering (Font Rendering in Word Processors)**

When rendering large amounts of text, especially when using different fonts, sizes, and styles, there can be significant repetition of the font data (e.g., font family, style, size, etc.). Instead of creating a new object for each occurrence of the same font, the **Flyweight** pattern can be used to share the font objects across different pieces of text.

#### Example:

- A word processor has hundreds or thousands of characters on the screen. The intrinsic state (the font family, size, and style) can be shared across all characters that use the same font, rather than creating a separate object for each character.

### 2. **Game Development (Sprites)**

In video games, the **Flyweight** pattern is commonly used for representing game entities that share common properties, such as enemy NPCs or objects. For example, in a 2D game, all enemies might have the same appearance (sprite), but they differ in position, health, and state (e.g., alive, dead, or damaged).

#### Example:

- Suppose a game has hundreds of identical enemy NPCs. Instead of creating separate objects for each NPC's appearance (sprite), the game can store one sprite (intrinsic state) and have each NPC share this sprite, only differing by their position, health, and behavior (extrinsic state).

### 3. **Database Connection Pools**

In large-scale applications, database connections might need to be reused to avoid the overhead of creating new connections for every request. The **Flyweight** pattern can be used to share database connections where the intrinsic state of the connection (e.g., the database server IP, username, password) is shared, and only the extrinsic state (e.g., the client request or transaction) varies.

#### Example:

- A database connection pool might manage a set of shared database connections. When a client needs to access the database, it will use a connection from the pool, and when it’s done, it will return the connection to the pool. This reduces the overhead of opening new connections repeatedly.

### 4. **Graphics/Images (Textures in 3D Rendering)**

In 3D rendering or graphics-heavy applications, textures (such as images) are often used across multiple objects. Instead of storing a separate texture for each object, the **Flyweight** pattern allows the reuse of a single texture for multiple objects. The position, scale, and other attributes are kept as extrinsic state, while the texture itself is shared as intrinsic state.

#### Example:

- A game with many characters, each having the same shirt design or texture. Instead of loading the texture for every character, the game loads the texture once and shares it across all characters that use that same design.

### 5. **Document Editing (Shared Styles)**

In document editing applications, such as Microsoft Word or Google Docs, there are many parts of a document that share similar styles (e.g., fonts, headings, paragraphs). Instead of storing each style in every text element, **Flyweight** allows the use of shared style objects, where only the content of the text differs.

#### Example:

- A document with multiple sections, each having the same header style (font, size, color). Instead of creating a new style object for each header, the editor can reuse the same style object for all headers, reducing memory usage.

### 6. **Network Protocol Handling**

In networking applications, the **Flyweight** pattern can be used to share the common state of a network protocol (such as header information or protocol types), while the extrinsic state could be the specific data for each message or packet being transmitted.

#### Example:

- When handling many packets of the same protocol type (such as HTTP requests), instead of creating a new protocol handler object for each packet, a shared object for the protocol handler can be used, with each packet only differing by its payload and other extrinsic data.

### 7. **Real-time Analytics (Metric Calculation)**

In data analytics applications that compute metrics (such as web analytics), the **Flyweight** pattern can be used to share the common logic for computing similar types of metrics across different data sources.

#### Example:

- For tracking user behavior on a website, the calculation logic for common metrics like “page views” or “click-through rate” can be shared across multiple pages or events. Each page or event only needs to provide the extrinsic state (e.g., page ID or user ID), while the common calculation logic is shared.

---

### Summary of Real-world Use Cases for Flyweight:

1. **Text Rendering**: Reuse font and style objects in a word processor.
2. **Game Development**: Share sprite data for identical objects in games.
3. **Database Connection Pools**: Share database connections to avoid creating new ones.
4. **3D Rendering/Graphics**: Share texture data across multiple objects in 3D games.
5. **Document Editing**: Share text formatting and style data across multiple sections in documents.
6. **Network Protocol Handling**: Share protocol objects for handling common network requests.
7. **Real-time Analytics**: Reuse calculation logic for common metrics across multiple data points.

In each of these cases, the **Flyweight** pattern helps save memory by sharing common intrinsic state across many objects and reducing the overhead of storing duplicate data.
