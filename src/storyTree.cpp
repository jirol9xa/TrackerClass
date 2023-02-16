#include "storyTree.hpp"

void StoryTree::addNode(const Node_t &node) {
    auto &bucket = forest_[node.idx_];
    bucket.push_back(node);
}

std::string printEventName(enum EVENT_TYPE event) {
    switch (event) {
#define DEF_EVENT(param)                                                                           \
    case param:                                                                                    \
        return #param;

#include "events.inc"
#undef DEF_EVENT

    default:
        return "invalid event";
    }
}
