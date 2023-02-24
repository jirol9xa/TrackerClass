#pragma once

#include "LocInfo.hpp"
#include <cstdint>
#include <cstdlib>
#include <string>

struct Node_t;

// Implementation for Tracker class
// TODO: Make it template
class Tracker {
  private:
    int_fast32_t ops_rmnd_ = 5;
    LocationInfo loc_; // For containing birth info
    uint_fast32_t idx_;

    int val_; // Value of myOwn int

    static uint_fast32_t obj_amnt_;        // For indexing all Trackers for storyTree
    static uint_fast32_t same_time_alive_; // For counting max amnt simultaneously
                                           // alive objects
  public:
    Tracker() {}
    Tracker(const LocationInfo &birth_info, const int &val = std::rand() % INT32_MAX);
    Tracker(const LocationInfo &birth_info, const Tracker &that);
    Tracker(const LocationInfo &birth_info, Tracker &&that);

    Tracker(const Tracker &that);
    Tracker(Tracker &&that);
    const Tracker &operator=(Tracker &&that);

    // Return a Tracker&, because we should do smt like that a.setLastUseLoc(...)
    // = 10
    Tracker &setLastUseLoc(const LocationInfo &loc) {
        loc_ = loc;
        return *this;
    }
    const Tracker &operator+=(Tracker &that);
    const Tracker &operator-=(Tracker &that);
    const Tracker &operator*=(Tracker &that);
    const Tracker &operator/=(Tracker &that);
    const Tracker &operator=(Tracker &that);
    operator int(); // Operator for implicit casting Tracker val to int

    Tracker operator+(Tracker &that);
    Tracker operator-(Tracker &that);
    Tracker operator*(Tracker &that);
    Tracker operator/(Tracker &that);

    std::string dump() const;
    uint_fast32_t getIdx() const { return idx_; }

    /// This type of copying uses in manipulations, when we don't wont to trigger
    /// copying constructors
    static void elementWiseCopy(Tracker *dst, const Tracker *src);

    ~Tracker() { --same_time_alive_; }
};
