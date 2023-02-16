#include "tracker.hpp"
#include "macro.hpp"
#include "storyTree.hpp"

const Tracker &Tracker::operator+=(const Tracker &that) {
    kTree.addNode({this, OP_ADD_ASGN});
    kTree.addNode({&that, OP_ADD_ASGN});

    val_ += that.val_;
    ops_rmnd_--;

    return *this;
}
const Tracker &Tracker::operator-=(const Tracker &that) {
    kTree.addNode({this, OP_SUB_ASGN});
    kTree.addNode({&that, OP_SUB_ASGN});

    val_ -= that.val_;
    ops_rmnd_--;

    return *this;
}
const Tracker &Tracker::operator*=(const Tracker &that) {
    kTree.addNode({this, OP_MUL_ASGN});
    kTree.addNode({&that, OP_MUL_ASGN});

    val_ *= that.val_;
    ops_rmnd_--;

    return *this;
}
const Tracker &Tracker::operator/=(const Tracker &that) {
    kTree.addNode({this, OP_DIV_ASGN});
    kTree.addNode({&that, OP_DIV_ASGN});

    val_ /= that.val_;
    ops_rmnd_--;

    return *this;
}

// We will call simply constructors, but it may leed to confusions, mb should do
// hidden constructors
Tracker Tracker::operator+(const Tracker &that) {
    kTree.addNode({this, OP_ADD});
    kTree.addNode({&that, OP_ADD});

    ops_rmnd_--;

    CREATE_AND_INIT(result, val_ + that.val_);
    return result;
}

Tracker Tracker::operator-(const Tracker &that) {
    kTree.addNode({this, OP_SUB});
    kTree.addNode({&that, OP_SUB});

    ops_rmnd_--;

    CREATE_AND_INIT(result, val_ - that.val_);
    return result;
}

Tracker Tracker::operator*(const Tracker &that) {
    kTree.addNode({this, OP_MUL});
    kTree.addNode({&that, OP_MUL});

    ops_rmnd_--;

    CREATE_AND_INIT(result, val_ * that.val_);
    return result;
}

Tracker Tracker::operator/(const Tracker &that) {
    kTree.addNode({this, OP_DIV});
    kTree.addNode({&that, OP_DIV});

    ops_rmnd_--;

    CREATE_AND_INIT(result, val_ / that.val_);
    return result;
}

Tracker::operator int() {
    kTree.addNode({this, INTPR_AS_INT});

    return val_;
}
