#include <iostream>
#include <list>
using namespace std;

class ISubscriber {
public:
  virtual void notify(string message) = 0;
};

class User : public ISubscriber {
private:
  int userId;

public:
  User(int id) : userId(id) {}
  void notify(string message) {
    cout << "User " << userId << " received message " << message << "\n";
  }
};

class Group {
private:
  list<ISubscriber *> users;

public:
  void subscribe(ISubscriber *user) { users.push_back(user); }
  void unsubscribe(ISubscriber *user) { users.remove(user); }
  void notify(string message) {
    for (auto &user : users) {
      user->notify(message);
    }
  }
};

int main() {
  Group *group = new Group();

  User *user1 = new User(1);
  User *user2 = new User(2);
  User *user3 = new User(3);

  group->subscribe(user1);
  group->subscribe(user2);
  group->subscribe(user3);

  group->notify("message1");

  group->unsubscribe(user1);
  group->notify("message2");

  return 0;
}