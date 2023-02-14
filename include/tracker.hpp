#pragma once

#include "locInfo.hpp"
#include <cstdint>
#include <cstdlib>

struct Node_t;

// Implementation for Tracker class
// TODO: Make it template
class Tracker {
  friend struct Node_t;

private:
  int_fast32_t ops_rmnd_ = 5;
  LocationInfo loc_; // For containing birth info

  int val_; // Value of myOwn int

  static uint_fast32_t obj_amnt_; // For indexing all Trackers for storyTree
  static uint_fast32_t same_time_alive_; // For counting max amnt simultaneously
                                         // alive objects
public:
  Tracker() {}
  Tracker(const LocationInfo &birth_info,
          const int &val = std::rand() % INT32_MAX)
      : loc_(birth_info), val_(val) {
    ++obj_amnt_;
    ++same_time_alive_;
  }

  // Return a Tracker&, because we should do smt like that a.setLastUseLoc(...)
  // = 10
  Tracker &setLastUseLoc(const LocationInfo &loc) {
    loc_ = loc;
    return *this;
  }
  const Tracker &operator+=(const Tracker &that);
  const Tracker &operator-=(const Tracker &that);
  const Tracker &operator*=(const Tracker &that);
  const Tracker &operator/=(const Tracker &that);
  operator int(); // Operator for implicit casting Tracker val to int

  Tracker operator+(const Tracker &that);
  Tracker operator-(const Tracker &that);
  Tracker operator*(const Tracker &that);
  Tracker operator/(const Tracker &that);

  ~Tracker() { --same_time_alive_; }
};
