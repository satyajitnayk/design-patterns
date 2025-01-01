#include "bike.hpp"
#include "car.hpp"
#include <iostream>
using namespace std;

int main() {
  string vehicleType;
  cin >> vehicleType;
  Vehicle *vehicle;
  if (vehicleType == "bike") {
    vehicle = new Bike();
  } else if (vehicleType == "car") {
    vehicle = new Car();
  } else {
    cout << "vechile type " << vehicle << " not supported\n";
    exit(0);
  }
  vehicle->createVehicle();
  return 0;
}