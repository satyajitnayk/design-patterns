# Design Patterns

This repository contains various design patterns categorized by their type. Below you'll find a list of behavioral, creational, and structural design patterns with links to their respective Markdown files for detailed explanations and examples.

## SOLID Principles

[SOLID PRINCIPLES](solid-principles.md)

The SOLID principles are a set of five design principles that help to create more understandable, flexible, and maintainable code:

1. **S** - Single Responsibility Principle (SRP): A class should have only one reason to change, meaning it should only have one job or responsibility.
2. **O** - Open/Closed Principle (OCP): Software entities should be open for extension but closed for modification.
3. **L** - Liskov Substitution Principle (LSP): Objects of a superclass should be replaceable with objects of a subclass without affecting the correctness of the program.
4. **I** - Interface Segregation Principle (ISP): No client should be forced to depend on methods it does not use.
5. **D** - Dependency Inversion Principle (DIP): High-level modules should not depend on low-level modules. Both should depend on abstractions.

## Design Patterns

This section lists common design patterns categorized into behavioral, creational, and structural types. Each pattern is linked to its respective explanation and example code.

### Behavioral Patterns

1. [Chain of Responsibility](behavioral/chain%20of%20responsibility.md) - Allows passing requests through a chain of handlers.
2. [Mediator](behavioral/mediator.md) - Defines an object that controls the communication between other objects.
3. [State](behavioral/state.md) - Allows an object to change its behavior when its internal state changes.
4. [Command](behavioral/command.md) - Encapsulates a request as an object, allowing parameterization and queuing of requests.
5. [Memento](behavioral/memento.md) - Captures and restores an object's internal state without exposing its details.
6. [Strategy](behavioral/strategy.md) - Defines a family of algorithms, encapsulates each one, and makes them interchangeable.
7. [Iterator](behavioral/iterator.md) - Provides a way to access the elements of an aggregate object sequentially without exposing its underlying representation.
8. [Observer](behavioral/observer.md) - Defines a dependency relationship between objects so that when one changes, all its dependents are notified.
9. [Template](behavioral/template.md) - Defines the skeleton of an algorithm in a method, deferring some steps to subclasses.

### Creational Patterns

1. [Abstract Factory](creational/abstract%20factory.md) - Provides an interface for creating families of related or dependent objects without specifying their concrete classes.
2. [Builder](creational/builder.md) - Separates the construction of a complex object from its representation, allowing the same construction process to create different representations.
3. [Factory](creational/factory.md) - Defines an interface for creating an object but lets subclasses decide which class to instantiate.
4. [Singleton](creational/singleton.md) - Ensures a class has only one instance and provides a global point of access to it.

### Structural Patterns

1. [Adapter](structural/adapter.md) - Converts one interface to another expected by the client.
2. [Composite](structural/composite.md) - Composes objects into tree structures to represent part-whole hierarchies.
3. [Facade](structural/facade.md) - Provides a simplified interface to a complex subsystem.
4. [Proxy](structural/proxy.md) - Provides a surrogate or placeholder for another object to control access.
5. [Bridge](structural/bridge.md) - Decouples an abstraction from its implementation so that the two can vary independently.
6. [Decorator](structural/decorator.md) - Adds new behavior to an object dynamically without affecting its existing functionality.
7. [Flyweight](structural/flyweight.md) - Reduces the number of objects created by sharing objects that are similar in nature.

---
