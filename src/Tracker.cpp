#include "Tracker.hpp"
#include "Macro.hpp"
#include "StoryTree.hpp"

#define ADD_BIN_OP_NODE(event_type) kTree.addLink2Nodes(event_type, *this, that);

Tracker::Tracker(const LocationInfo &birth_info, const int &val) : loc_(birth_info), val_(val) {
    idx_ = obj_amnt_++;
    ++same_time_alive_;

    Node_t *ctor = new Node_t{CTOR};
    kTree.addNode(ctor);
    kTree.linkNode(ctor, *this);
}

Tracker::Tracker(const Tracker &that) {
    ops_rmnd_ = that.ops_rmnd_;
    loc_ = that.loc_;
    val_ = that.val_;

    idx_ = ++obj_amnt_;
    same_time_alive_++;

    ADD_BIN_OP_NODE(CTOR);
}

Tracker::Tracker(const LocationInfo &birth_info, const Tracker &that) {
    ops_rmnd_ = that.ops_rmnd_;
    val_ = that.val_;

    idx_ = ++obj_amnt_;
    same_time_alive_++;

    loc_ = birth_info;

    ADD_BIN_OP_NODE(RVAL_COPY_CNSTR);
}

Tracker::Tracker(Tracker &&that) {
    ops_rmnd_ = that.ops_rmnd_;
    loc_ = that.loc_;
    val_ = that.val_;

    idx_ = ++obj_amnt_;
    same_time_alive_++;

    ADD_BIN_OP_NODE(RVAL_COPY_CNSTR);
}

Tracker::Tracker(const LocationInfo &birth_info, Tracker &&that) {
    ops_rmnd_ = that.ops_rmnd_;
    val_ = that.val_;

    idx_ = ++obj_amnt_;
    same_time_alive_++;

    loc_ = birth_info;

    ADD_BIN_OP_NODE(RVAL_COPY_CNSTR);
}

const Tracker &Tracker::operator=(Tracker &&that) {
    ops_rmnd_ = that.ops_rmnd_;
    loc_ = that.loc_;
    val_ = that.val_;

    idx_ = ++obj_amnt_;
    same_time_alive_++;

    ADD_BIN_OP_NODE(RVAL_OP_ASGN);

    return *this;
}

const Tracker &Tracker::operator+=(Tracker &that) {
    val_ += that.val_;
    ops_rmnd_--;
    that.ops_rmnd_--;

    ADD_BIN_OP_NODE(OP_ADD_ASGN);

    return *this;
}
const Tracker &Tracker::operator-=(Tracker &that) {
    val_ -= that.val_;
    ops_rmnd_--;
    that.ops_rmnd_--;

    ADD_BIN_OP_NODE(OP_SUB_ASGN);

    return *this;
}
const Tracker &Tracker::operator*=(Tracker &that) {
    val_ *= that.val_;
    ops_rmnd_--;
    that.ops_rmnd_--;

    ADD_BIN_OP_NODE(OP_MUL_ASGN);

    return *this;
}
const Tracker &Tracker::operator/=(Tracker &that) {
    val_ /= that.val_;
    ops_rmnd_--;
    that.ops_rmnd_--;

    ADD_BIN_OP_NODE(OP_DIV_ASGN);

    return *this;
}

// We will call simply constructors, but it may leed to confusions, mb should do
// hidden constructors
Tracker Tracker::operator+(Tracker &that) {
    ops_rmnd_--;
    that.ops_rmnd_--;

    ADD_BIN_OP_NODE(OP_ADD);

    CREATE_AND_INIT(result, val_ + that.val_);
    return result;
}

Tracker Tracker::operator-(Tracker &that) {
    ops_rmnd_--;
    that.ops_rmnd_--;

    ADD_BIN_OP_NODE(OP_SUB);

    CREATE_AND_INIT(result, val_ - that.val_);
    return result;
}

Tracker Tracker::operator*(Tracker &that) {
    ops_rmnd_--;
    that.ops_rmnd_--;

    ADD_BIN_OP_NODE(OP_MUL);

    CREATE_AND_INIT(result, val_ * that.val_);
    return result;
}

Tracker Tracker::operator/(Tracker &that) {
    ops_rmnd_--;
    that.ops_rmnd_--;

    ADD_BIN_OP_NODE(OP_DIV);

    CREATE_AND_INIT(result, val_ / that.val_);
    return result;
}

Tracker::operator int() {
    Node_t *node = new Node_t{INTPR_AS_INT};
    kTree.addNode(node);
    kTree.linkNode(node, *this);

    return val_;
}

void Tracker::elementWiseCopy(Tracker *dst, const Tracker *src) {
    dst->ops_rmnd_ = src->ops_rmnd_;
    dst->loc_ = src->loc_;
    dst->idx_ = src->idx_;
    dst->val_ = src->val_;
}

std::string Tracker::dump() const {
    return "ops_rmnd_ = " + std::to_string(ops_rmnd_) + " val_ = " + std::to_string(val_) + '\n' +
           '|' + loc_.dump();
}
