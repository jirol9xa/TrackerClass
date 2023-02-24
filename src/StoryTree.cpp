#include "StoryTree.hpp"
#include <iostream>

Node_t::~Node_t() {
    for (unsigned i = 0; i < tracking_vars_.size(); ++i)
        delete tracking_vars_.at(i);
}

void StoryTree::addNode(Node_t *node) { nodes_.push_back(node); }

void StoryTree::linkNode(Node_t *node, const Tracker &var) {
    auto &bucket = forest_[var.getIdx()];

    // Here we add node to the history list of variable
    bucket.push_back(node->idx_);

    // Here we add each variable to the tracking variables list of node
    Tracker *copy_var = new Tracker();
    Tracker::elementWiseCopy(copy_var, &var);
    node->tracking_vars_.push_back(copy_var);
}

void StoryTree::addLink2Nodes(const EVENT_TYPE event, const Tracker &first, const Tracker &second) {
    Node_t *node = new Node_t{event};
    addNode(node);

    linkNode(node, first);
    linkNode(node, second);
}

/*void StoryTree::sortNodes() const {
    std::sort(nodes_.begin(), nodes_.end(),
              [](const Node_t &first, const Node_t &second) { return first.idx_ > second.idx_; });
}*/

StoryTree::~StoryTree() {
    for (unsigned i = 0; i < nodes_.size(); ++i)
        delete nodes_.at(i);
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
