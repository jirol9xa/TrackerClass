#include "tracker.hpp"
#include "macro.hpp"
#include "storyTree.hpp"

Tracker::Tracker(const LocationInfo &birth_info, const int &val) : loc_(birth_info), val_(val) {
            ++obj_amnt_;
    ++same_time_alive_;

    kTree.addNode({this, CTOR, true});
}

const Tracker &Tracker::operator+=(const Tracker &that) {
    kTree.addNode({this, OP_ADD_ASGN, true});
    kTree.addNode({&that, OP_ADD_ASGN});

    val_ += that.val_;
    ops_rmnd_--;

    return *this;
}
const Tracker &Tracker::operator-=(const Tracker &that) {
    kTree.addNode({this, OP_SUB_ASGN, true});
    kTree.addNode({&that, OP_SUB_ASGN});

    val_ -= that.val_;
    ops_rmnd_--;

    return *this;
}
const Tracker &Tracker::operator*=(const Tracker &that) {
    kTree.addNode({this, OP_MUL_ASGN, true});
    kTree.addNode({&that, OP_MUL_ASGN});

    val_ *= that.val_;
    ops_rmnd_--;

    return *this;
}
const Tracker &Tracker::operator/=(const Tracker &that) {
    kTree.addNode({this, OP_DIV_ASGN, true});
    kTree.addNode({&that, OP_DIV_ASGN});

    val_ /= that.val_;
    ops_rmnd_--;

    return *this;
}

// We will call simply constructors, but it may leed to confusions, mb should do
// hidden constructors
Tracker Tracker::operator+(const Tracker &that) {
    kTree.addNode({this, OP_ADD, true});
    kTree.addNode({&that, OP_ADD});

    ops_rmnd_--;

    CREATE_AND_INIT(result, val_ + that.val_);
    return result;
}

Tracker Tracker::operator-(const Tracker &that) {
    kTree.addNode({this, OP_SUB, true});
    kTree.addNode({&that, OP_SUB});

    ops_rmnd_--;

    CREATE_AND_INIT(result, val_ - that.val_);
    return result;
}

Tracker Tracker::operator*(const Tracker &that) {
    kTree.addNode({this, OP_MUL, true});
    kTree.addNode({&that, OP_MUL});

    ops_rmnd_--;

    CREATE_AND_INIT(result, val_ * that.val_);
    return result;
}

Tracker Tracker::operator/(const Tracker &that) {
    kTree.addNode({this, OP_DIV, true});
    kTree.addNode({&that, OP_DIV});

    ops_rmnd_--;

    CREATE_AND_INIT(result, val_ / that.val_);
    return result;
}

Tracker::operator int() {
    kTree.addNode({this, INTPR_AS_INT, true});

    return val_;
}

std::string Tracker::dump() const {
    return "ops_rmnd_ = " + std::to_string(ops_rmnd_) + " val_ = " + std::to_string(val_) + '\n' +
           '|' + loc_.dump();
}
