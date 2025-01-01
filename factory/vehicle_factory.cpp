
#include "vehicle_factory.hpp"
#include <iostream>
using namespace std;

Vehicle *VehicleFactory::getVehicle(string vehicleType) {
  Vehicle *vehicle;
  if (vehicleType == "bike") {
    vehicle = new Bike();
  } else if (vehicleType == "car") {
    vehicle = new Car();
  }
  return vehicle;
}