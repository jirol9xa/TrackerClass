#pragma once

#include "locInfo.hpp"
#include <cstdint>
#include <cstdlib>

// Implementation for Tracker class
// TODO: Make it template
class Tracker {
private:
  int_fast32_t _ops_rmnd = 5;
  struct VarInfo // Class for containing birth info
  {
    uint_fast32_t idx;
    LocationInfo loc;
  } _info;

  int _val; // Value of myOwn int

  static uint_fast32_t _obj_amnt; // For indexing all Trackers for storyTree
  static uint_fast32_t _same_time_alive; // For counting max amnt simultaneously
                                         // alive objects
public:
  Tracker(const VarInfo &birth_info, const int &val = std::rand() % INT32_MAX)
      : _info(birth_info), _val(val) {
    ++_obj_amnt;
    ++_same_time_alive;
  }

  // Return a Tracker&, because we should do smt like that a.setLastUseLoc(...)
  // = 10
  Tracker &setLastUseLoc(const LocationInfo &loc) {
    _info.loc = loc;
    return *this;
  }

  const Tracker &operator+=(const Tracker &that) {}
  const Tracker &operator-=(const Tracker &that) {}
  const Tracker &operator*=(const Tracker &that) {}
  const Tracker &operator/=(const Tracker &that) {}
  operator int() // Operator for implicit casting Tracker val to int
  {}

  Tracker operator+(const Tracker &that) {}
  Tracker operator-(const Tracker &that) {}
  Tracker operator*(const Tracker &that) {}
  Tracker operator/(const Tracker &that) {}

  ~Tracker() { --_same_time_alive; }
};
