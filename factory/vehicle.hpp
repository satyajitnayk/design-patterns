// When a header file is included in multiple files, the compiler might process
// it multiple times, leading to redefinition errors. Include guards ensure the
// file is included only once in the compilation process.

#ifndef vehicle_hpp // If vehicle_hpp is not defined
#define vehicle_hpp

class Vehicle {
public:
  virtual void createVehicle() = 0;
};

#endif // End of conditional inclusion

// How it Works?
// First Inclusion:

// The #ifndef VEHICLE_HPP checks if the macro VEHICLE_HPP is not defined.
// Since it’s not defined, the code inside the #ifndef block is included.
// The macro VEHICLE_HPP is then defined to mark that this file has been
// processed. Subsequent Inclusions:

// The #ifndef VEHICLE_HPP now finds that VEHICLE_HPP is already defined.
// The content inside the block is skipped, avoiding redefinitions.
