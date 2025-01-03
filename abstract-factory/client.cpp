#include <iostream>
using namespace std;

class IButton {
public:
  virtual void press() = 0;
};

class MacButton : public IButton {
public:
  void press() { cout << "Mac button is pressed\n"; }
};

class WindowsButton : public IButton {
public:
  void press() { cout << "Windows button is pressed\n"; }
};

class ITextBox {
public:
  virtual void showText() = 0;
};

class MacTextBox : public ITextBox {
public:
  void showText() { cout << "Mac textbox\n"; }
};

class WindowsTextBox : public ITextBox {
public:
  void showText() { cout << "Windows textbox\n"; }
};

class IFactory {
public:
  virtual IButton *CreateButton() = 0;
  virtual ITextBox *CreateTextBox() = 0;
};

class MacFactory : public IFactory {
public:
  IButton *CreateButton() { return new MacButton(); }
  ITextBox *CreateTextBox() { return new MacTextBox(); }
};

class WindowsFactory : public IFactory {
public:
  IButton *CreateButton() { return new WindowsButton(); }
  ITextBox *CreateTextBox() { return new WindowsTextBox(); }
};

class GUIAbstractFactory {
public:
  static IFactory *CreateFactory(string osType) {
    if (osType == "windows") {
      return new WindowsFactory();
    } else if (osType == "mac") {
      return new MacFactory();
    } else {
      return new MacFactory();
    }
  }
};

int main() {
  cout << "Enter the OS type "
       << "\n";
  string osType;
  cin >> osType;

  IFactory *fact = GUIAbstractFactory::CreateFactory(osType);

  IButton *button = fact->CreateButton();
  button->press();

  ITextBox *textBox = fact->CreateTextBox();
  textBox->showText();

  return 0;
}