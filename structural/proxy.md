The **Proxy Pattern** is a structural design pattern that provides an object representing another object. This "proxy" object controls access to the original object, often adding some additional behavior or functionality.

Here is an example demonstrating the **Proxy Pattern** in C++:

### Problem Scenario:

- You have an `Image` class that is used to load and display large images.
- You want to control the loading of the image only when it's necessary (i.e., lazy loading). Instead of loading the image immediately, a `Proxy` will be used to delay the loading until it is actually required.

### Proxy Pattern Example in C++:

```cpp
#include <iostream>
#include <memory>
#include <string>

using namespace std;

// RealSubject: Image class that represents the real image object
class Image {
public:
  Image(const string &filename) : filename(filename) { loadImage(); }

  void Display() { cout << "Displaying image: " << filename << endl; }

private:
  string filename;

  void loadImage() {
    // Simulate the process of loading a large image
    cout << "Loading image: " << filename << endl;
  }
};

// Proxy: Proxy for Image class
class ImageProxy {
public:
  ImageProxy(const string &filename) : filename(filename), realImage(nullptr) {}

  void Display() {
    // If the image is not loaded yet, load it
    if (!realImage) {
      realImage = make_unique<Image>(filename); // Lazy loading
    }
    realImage->Display();
  }

private:
  string filename;
  unique_ptr<Image> realImage;
};

// Client code
int main() {
  // Proxy for Image
  ImageProxy proxyImage("large_image.jpg");
  // Image is not loaded yet; the proxy will load it when Display() is called
  proxyImage.Display();
  // No need to reload, proxy can use the loaded image
  proxyImage.Display();
  return 0;
}
```

### Explanation of the Code:

1. **Image Class (RealSubject)**:
   - This class represents the actual object that does the heavy lifting. It simulates the loading of a large image and provides a `Display()` function to display the image.
2. **ImageProxy Class (Proxy)**:
   - The `ImageProxy` class controls access to the `Image` class. It contains a `Display()` function that will load the real image only when needed (lazy loading).
   - The `ImageProxy` also ensures that the real image is loaded only once, saving resources by not reloading the image every time `Display()` is called.
3. **Client Code**:
   - In the `main()` function, the client interacts with the proxy (`ImageProxy`) instead of directly using the `Image` class. The proxy ensures that the image is loaded only when `Display()` is called.

### Key Points:

- **Lazy Loading**: The real object (`Image`) is not created until the `Display()` method is called on the proxy.
- **Control Access**: The proxy can add additional behavior, such as logging, access control, or caching, before or after delegating to the real object.

### Types of Proxies:

1. **Virtual Proxy**: Used for lazy initialization (like in the example above). The object is created only when it is actually needed.
2. **Remote Proxy**: Used when the object is located remotely (like a server). It hides the complexity of network communication.
3. **Protective Proxy**: Controls access to the real object based on user permissions.

In this example, the **Proxy** pattern helps to delay the heavy operation of loading the image until it's needed, improving performance by not loading it unnecessarily.
