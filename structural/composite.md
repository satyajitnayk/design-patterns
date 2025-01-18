The **Composite Pattern** is a structural design pattern used to compose objects into tree structures, representing part-whole hierarchies. It allows clients to treat individual objects and compositions of objects uniformly.

---

### **What is the Composite Pattern?**

- **Part-Whole Hierarchies**: Represents hierarchical structures like file systems, organization charts, etc.
- **Uniform Treatment**: Treat individual objects and groups of objects the same way using a common interface.

---

### **Why Use the Composite Pattern?**

- **Simplifies Client Code**: Clients can work with single objects or collections uniformly.
- **Hierarchical Structures**: Ideal for scenarios like directories containing files or other directories.

---

### **Go Implementation**

Go supports the Composite Pattern using interfaces and recursive compositions.

---

#### **Basic Example: File System**

```c++
#include <iostream>
#include <memory>
#include <vector>
using namespace std;

// IComponent interface
class IComponent {
public:
  virtual void display(const string &indent) = 0;
  virtual ~IComponent() {}
};

// Leaf: File
class File : public IComponent {
private:
  string name;

public:
  File(const string &name) : name(name) {}

  void display(const string &indent) override {
    cout << indent << name << endl;
  }
};

// Composite: Directory
class Directory : public IComponent {
private:
  string name;
  vector<shared_ptr<IComponent>> components;

public:
  Directory(const string &name) : name(name) {}

  void add(shared_ptr<IComponent> component) {
    components.push_back(component);
  }

  void display(const string &indent) override {
    cout << indent << name << endl;
    for (const auto &component : components) {
      component->display(indent + "  ");
    }
  }
};

int main() {
  // Create leaf components
  shared_ptr<File> file1 = make_shared<File>("File1.txt");
  shared_ptr<File> file2 = make_shared<File>("File2.txt");
  shared_ptr<File> file3 = make_shared<File>("File3.txt");

  // Create composite components
  shared_ptr<Directory> folder1 = make_shared<Directory>("Folder1");
  shared_ptr<Directory> folder2 = make_shared<Directory>("Folder2");
  shared_ptr<Directory> root = make_shared<Directory>("Root");

  // Build the hierarchy
  folder1->add(file1);
  folder1->add(file2);
  folder2->add(file3);
  root->add(folder1);
  root->add(folder2);

  // display the structure
  root->display("");

  return 0;
}
```

---

### **Output**

```
Root
  Folder1
    File1.txt
    File2.txt
  Folder2
    File3.txt
```

### **Advantages**

1. **Scalability**: Easily compose objects into complex structures.
2. **Uniformity**: Treat individual and composite objects uniformly.
3. **Extensibility**: Add new types of components without modifying existing code.

---

### **Disadvantages**

1. **Complexity**: Can introduce unnecessary complexity for simple structures.
2. **Overhead**: Managing parent-child relationships can increase resource usage.

---

### **When to Use the Composite Pattern?**

- When dealing with tree structures like file systems, menus, or organizational charts.
- When you want to treat individual and composite objects uniformly.
- When you need to recursively process hierarchical data.
