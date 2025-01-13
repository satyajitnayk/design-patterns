## Start by SOLID principles

![SOLID PRINCIPLES](solid-principles.md)

# design-patterns

### complie:

```shell
g++ file1.cpp file2.cpp
```

### archive object files:

```shell
ar ru vehicle_library.a car.o bike.o
```

### use package to run client file:

```shell
g++ client.cpp vehicle_library.a -o out && ./out
```

### Short Notes on Design Patterns

1. **Importance of Design Patterns**

- Simplify solving common software problems.
- Help create scalable, reliable, and maintainable code.
- Proven, reusable, and language-independent.
- Useful for daily work and interviews (e.g., low-level design).

2. **Types of Design Patterns**

- **Creational**: Solve object creation problems.
  - Examples: Factory, Abstract Factory, Singleton.
- **Structural**: Organize and structure classes.
  - Examples: Bridge, Adapter, Composite.
- **Behavioral**: Manage interaction and communication between classes.
  - Examples: Strategy, Observer, Interpreter.

3. **Applications**
   - Simplify designing systems.
   - Enhance collaboration through a common vocabulary (e.g., Factory Pattern).
   - Expected knowledge for interviews and practical work.
