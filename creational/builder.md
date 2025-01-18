# Builder Design Pattern in C++

## Overview

The Builder Design Pattern is a creational design pattern used to construct complex objects step by step. It allows for the creation of different representations of the same object using the same construction process.

### Why Use the Builder Pattern?

- To construct complex objects with many configurable options.
- To separate the construction logic from the representation.
- To provide better control over the object creation process.

---

## Practical Example: Building a Custom Computer

Imagine a scenario where you need to configure and build a custom computer with options for the CPU, GPU, RAM, and storage. The Builder Pattern helps create a clean and modular approach to building such objects.

### Implementation

#### Step 1: Define the Product

```cpp
#include <iostream>
#include <memory>
using namespace std;

class Computer {
private:
  string cpu;
  string gpu;
  int ram;
  int storage;

public:
  void setCPU(const string &cpu) { this->cpu = cpu; }
  void setGPU(const string &gpu) { this->gpu = gpu; }
  void setRAM(int ram) { this->ram = ram; }
  void setStorage(int storage) { this->storage = storage; }

  void showSpecifications() const {
    cout << "Computer Specifications:" << endl;
    cout << "CPU: " << cpu << endl;
    cout << "GPU: " << gpu << endl;
    cout << "RAM: " << ram << " GB" << endl;
    cout << "Storage: " << storage << " GB" << endl;
    cout << "-------------------------------\n";
  }
};
```

#### Step 2: Define the Builder Interface

```cpp
class IComputerBuilder {
public:
  virtual ~IComputerBuilder() = default;
  virtual void buildCPU() = 0;
  virtual void buildGPU() = 0;
  virtual void buildRAM() = 0;
  virtual void buildStorage() = 0;
  virtual shared_ptr<Computer> getComputer() = 0;
};
```

#### Step 3: Implement Concrete Builders

```cpp
class GamingComputerBuilder : public IComputerBuilder {
private:
  shared_ptr<Computer> computer;

public:
  GamingComputerBuilder() { computer = make_shared<Computer>(); }

  void buildCPU() override { computer->setCPU("Intel i9"); }
  void buildGPU() override { computer->setGPU("NVIDIA RTX 4090"); }
  void buildRAM() override { computer->setRAM(32); }
  void buildStorage() override { computer->setStorage(2000); }

  shared_ptr<Computer> getComputer() override { return computer; }
};

class OfficeComputerBuilder : public IComputerBuilder {
private:
  shared_ptr<Computer> computer;

public:
  OfficeComputerBuilder() { computer = make_shared<Computer>(); }

  void buildCPU() override { computer->setCPU("Intel i5"); }
  void buildGPU() override { computer->setGPU("Integrated Graphics"); }
  void buildRAM() override { computer->setRAM(16); }
  void buildStorage() override { computer->setStorage(512); }

  shared_ptr<Computer> getComputer() override { return computer; }
};
```

#### Step 4: Create the Director

```cpp
class ComputerDirector {
private:
  IComputerBuilder *builder;

public:
  void setBuilder(IComputerBuilder *b) { builder = b; }

  void constructComputer() {
    builder->buildCPU();
    builder->buildGPU();
    builder->buildRAM();
    builder->buildStorage();
  }
};
```

#### Step 5: Use the Builder Pattern

```cpp
int main() {
  ComputerDirector director;

  // Build a Gaming Computer using shared_ptr for the builder
  // `shared_ptr`: A smart pointer that manages shared ownership of dynamically
  // allocated objects.
  // `make_shared` : A function that efficiently creates a shared pointer,
  // allocating memory for both the object and its reference count in one
  // operation, and offering better exception safety and performance than using
  // new manually.
  shared_ptr<GamingComputerBuilder> gamingBuilder =
      make_shared<GamingComputerBuilder>();
  director.setBuilder(gamingBuilder.get()); // Use raw pointer for setting
  director.constructComputer();
  shared_ptr<Computer> gamingComputer = gamingBuilder->getComputer();
  gamingComputer->showSpecifications();

  // Build an Office Computer using shared_ptr for the builder
  shared_ptr<OfficeComputerBuilder> officeBuilder =
      make_shared<OfficeComputerBuilder>();
  director.setBuilder(officeBuilder.get()); // Use raw pointer for setting
  director.constructComputer();
  shared_ptr<Computer> officeComputer = officeBuilder->getComputer();
  officeComputer->showSpecifications();

  return 0;
}
```

---

### Benefits of the Builder Pattern

1. **Modularity**: Separate object construction logic from the object itself.
2. **Reusability**: Use the same construction process for different representations.
3. **Flexibility**: Easy to add new builders without modifying existing code.

### Applicability

- When creating complex objects with multiple configurations.
- When you want to avoid large constructors with many parameters.
- When you want a clear and step-by-step construction process.
