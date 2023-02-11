#pragma once

#include <cstdint>
#include <cstdlib>
#include "locInfo.hpp"

// Implementation for Tracker class
// TODO: Make it template 
class Tracker {
private:
  int_fast32_t _ops_rmnd = 5;
  struct VarInfo // Class for containing birth info
  {
    uint_fast64_t addr;
    LocationInfo loc; 
  } info;

  int _val; // Value of myOwn int
public:
  Tracker(const VarInfo &birth_info, const int &val = std::rand() % INT32_MAX)
      : info(birth_info), _val(val) {}
  
  const Tracker &operator+=(const Tracker &that) {
    
  }
  const Tracker &operator-=(const Tracker &that) {
    
  }
  const Tracker &operator*=(const Tracker &that) {
  
  }
  const Tracker &operator/=(const Tracker &that) {

  }
  operator int()  // Operator for implicit casting Tracker val to int
  {

  }

  Tracker operator+(const Tracker &that) {
  
  }
  Tracker operator-(const Tracker &that) {

  }
};
