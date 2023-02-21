#include "StoryTree.hpp"

Node_t::Node_t(const Node_t &that)
    : tracked_var_(that.tracked_var_), event_(that.event_), idx_(that.idx_) {
    // We need to copy elementwise, because we don't want to trigger copy
    // constructor
    copy_var_.val_ = that.copy_var_.val_;
    copy_var_.loc_ = that.copy_var_.loc_;
    copy_var_.ops_rmnd_ = that.copy_var_.ops_rmnd_;
    copy_var_.idx_ = that.copy_var_.idx_;
}

void StoryTree::addNode(const Node_t &node) {
    auto &bucket = forest_[node.copy_var_.getIdx()];
    bucket.push_back(node);
}

std::string printEventName(enum EVENT_TYPE event) {
    switch (event) {
#define DEF_EVENT(param)                                                                           \
    case param:                                                                                    \
        return #param;

#include "Events.inc"
#undef DEF_EVENT

    default:
        return "invalid event";
    }
}
