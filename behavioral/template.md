The **Template Method** pattern defines the skeleton of an algorithm in a base class, allowing subclasses to override specific steps without changing the overall structure.

Here’s a practical example: **Online Order Processing**.

### Problem Statement:

You want to create an order processing system where different types of orders (e.g., Store Pickup, Online Delivery) follow the same high-level steps but have variations in specific parts of the process.

---

### C++ Code Example

```cpp
#include <iostream>
#include <string>
using namespace std;

// Abstract Base Class (Template)
class OrderProcessor {
public:
  // Template Method: defines the skeleton of the algorithm
  void processOrder() {
    selectItem();
    if (isGift()) { // Hook to customize behavior
      wrapGift();
    }
    makePayment();
    deliver();
  }

  virtual ~OrderProcessor() = default;

protected:
  virtual void selectItem() = 0;  // Step to be defined by subclasses
  virtual void makePayment() = 0; // Step to be defined by subclasses
  virtual void deliver() = 0;     // Step to be defined by subclasses

  virtual bool isGift() { return false; } // Hook: Subclasses can override
  virtual void wrapGift() {               // Default implementation
    cout << "Wrapping the item as a gift." << endl;
  }
};

// Concrete Class 1: Store Pickup Order
class StorePickupOrder : public OrderProcessor {
protected:
  void selectItem() override {
    cout << "Customer selects an item from the store." << endl;
  }

  void makePayment() override {
    cout << "Customer pays at the store counter." << endl;
  }

  void deliver() override {
    cout << "Customer picks up the item from the store." << endl;
  }
};

// Concrete Class 2: Online Delivery Order
class OnlineDeliveryOrder : public OrderProcessor {
protected:
  void selectItem() override {
    cout << "Customer selects an item from the online catalog." << endl;
  }

  void makePayment() override {
    cout << "Customer pays online using a credit card." << endl;
  }

  void deliver() override {
    cout << "Item is delivered to the customer's address." << endl;
  }

  bool isGift() override {
    return true; // Online orders allow gift wrapping
  }
};

int main() {
  cout << "Processing Store Pickup Order:" << endl;
  StorePickupOrder storeOrder;
  storeOrder.processOrder();

  cout << "\nProcessing Online Delivery Order:" << endl;
  OnlineDeliveryOrder onlineOrder;
  onlineOrder.processOrder();

  return 0;
}
```

---

### Explanation of the Code

1. **Abstract Base Class (`OrderProcessor`)**:

   - Defines the **template method** `processOrder()`, which outlines the high-level steps of the order process.
   - Provides hooks (`isGift()` and `wrapGift()`) for optional customization.
   - Declares pure virtual methods (`selectItem()`, `makePayment()`, and `deliver()`) that must be implemented by subclasses.

2. **Concrete Classes**:

   - `StorePickupOrder`: Implements steps specific to store pickup.
   - `OnlineDeliveryOrder`: Implements steps specific to online delivery and overrides the `isGift()` hook to enable gift wrapping.

3. **Template Method (`processOrder()`)**:
   - Executes the steps in a predefined order, calling subclass-specific implementations for certain steps.
   - Uses hooks like `isGift()` to allow subclasses to customize behavior.

---

### Output

```
Processing Store Pickup Order:
Customer selects an item from the store.
Customer pays at the store counter.
Customer picks up the item from the store.

Processing Online Delivery Order:
Customer selects an item from the online catalog.
Wrapping the item as a gift.
Customer pays online using a credit card.
Item is delivered to the customer's address.
```

---

### Key Points

- **Reusability**: The high-level structure (`processOrder()`) is reused across different implementations.
- **Customization**: Subclasses define their own behavior for specific steps, allowing flexibility.
- **Hooks**: Optional customization points (`isGift()` and `wrapGift()`) let subclasses modify behavior without overriding the entire template method.
