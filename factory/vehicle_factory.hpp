#ifndef vehicle_factory_hpp
#define vehicle_factory_hpp

#include "bike.hpp"
#include "car.hpp"
#include <iostream>
using namespace std;

class VehicleFactory {
public:
  static Vehicle *getVehicle(string vehicleType);
};

#endif