The **State Pattern** allows an object to alter its behavior when its internal state changes. The object will appear to change its class. This pattern is used when an object can have many states and the behavior of the object depends on its current state.

## Use Case

This pattern is useful when:

- An object needs to change its behavior based on its state.
- An object has a large number of states and state-specific behavior.
- You want to make state transitions explicit in your code and avoid complex conditionals.

## Structure

1. **Context**: Maintains an instance of a `State` subclass that defines the current state.
2. **State**: Interface or abstract class that declares methods that concrete states implement.
3. **Concrete State**: Implementations of the `State` interface. Each state has its own behavior.

## Example: Traffic Light

In this example, we have a traffic light system that changes its behavior (i.e., light color) based on its current state.

---

```cpp
#include <iostream>
#include <memory>
using namespace std;

// Abstract State class
class TrafficLightState {
public:
  virtual ~TrafficLightState() {}
  virtual void handle(class TrafficLight *light) = 0;
};

class TrafficLight {
public:
  void setState(shared_ptr<TrafficLightState> state) { this->state = state; }

  void change() { state->handle(this); }

private:
  shared_ptr<TrafficLightState> state;
};

// Concrete states
class RedLight : public TrafficLightState {
public:
  void handle(TrafficLight *light) override;
};

class YellowLight : public TrafficLightState {
public:
  void handle(TrafficLight *light) override {
    cout << "Yellow Light - Get Ready!" << endl;
    light->setState(make_shared<RedLight>());
  }
};

class GreenLight : public TrafficLightState {
public:
  void handle(TrafficLight *light) override {
    cout << "Green Light - Go!" << endl;
    light->setState(make_shared<YellowLight>());
  }
};

void RedLight::handle(TrafficLight *light) {
  cout << "Red Light - Stop!" << endl;
  light->setState(make_shared<GreenLight>());
}

// Main function
int main() {
  TrafficLight trafficLight;

  // Start with red light
  trafficLight.setState(make_shared<RedLight>());
  trafficLight.change(); // Red -> Green
  trafficLight.change(); // Green -> Yellow
  trafficLight.change(); // Yellow -> Red

  return 0;
}
```

### Explanation

- **State Interface**: `State` defines the interface for handling state transitions.
- **Concrete States**: `RedState`, `GreenState`, and `YellowState` are the concrete states implementing the `State` interface, each with a `handleRequest` method.
- **TrafficLight (Context)**: The `TrafficLight` class holds the current state and delegates state changes to the concrete state classes.

---

## Benefits of the State Pattern

- **Avoids Conditional Statements**: Instead of having complex conditionals to check states, the State Pattern encapsulates state-specific behavior in state classes.
- **Ease of Adding States**: New states can be added easily without modifying the context or existing states.
- **Improved Code Maintainability**: State transitions are explicit and well-defined.

---

## Conclusion

The State Pattern is useful when an object has several states and its behavior needs to change based on its state. It promotes code maintainability and reduces the complexity of conditional logic in the application.
