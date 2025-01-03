### Builder Design Pattern Notes:

#### Definition:
The Builder Design Pattern is a **creational design pattern** used to construct complex objects step by step. It separates the construction process from the representation, allowing the same construction process to create different representations.

---

### Key Points:
1. **Purpose**:
   - To construct complex objects with multiple configurations in a controlled manner.
   - Decouples the object construction process from the actual object representation.

2. **When to Use**:
   - When an object requires multiple steps to be constructed.
   - When an object can have different representations or configurations.
   - To avoid a "telescoping constructor" problem (overloaded constructors with too many parameters).

3. **Benefits**:
   - **Readability**: Step-by-step object construction makes code easier to understand.
   - **Reusability**: The same builder can create different objects with varying configurations.
   - **Flexibility**: Adding new parameters or configurations doesn’t require modifying the client code.

4. **Drawbacks**:
   - Adds complexity by requiring additional classes (builder and director).
   - May be overkill for simple objects.


### Common Interview Questions:
1. **What problem does the Builder Pattern solve?**
   - It provides a way to build complex objects step-by-step, avoiding constructors with too many arguments.

2. **What is the role of the Director?**
   - The Director manages the construction process and ensures that the steps are executed in a specific order.

3. **Real-world examples of Builder Pattern?**
   - **C++**: `std::ostringstream` to construct strings.
   - **UI Frameworks**: Building GUI components (e.g., HTML builders in web frameworks).

4. **How does it differ from Factory Pattern?**
   - Builder focuses on constructing complex objects step by step.
   - Factory focuses on creating objects without exposing instantiation logic.

5. **How does the Builder Pattern promote the Single Responsibility Principle?**
   - The construction logic is handled by the builder, and the product (object) is only responsible for its representation.

---

### Variations:
1. **Fluent Interface**:
   - A chained API style where methods return the builder itself for method chaining.
   - Example:
     ```cpp
     HouseBuilder& builder = HouseBuilder().addWalls("Brick").addRoof("Tile").addWindows("Glass");
     House house = builder.build();
     ```

2. **Without Director**:
   - Sometimes the builder itself orchestrates the construction steps.

