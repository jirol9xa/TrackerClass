#include "storyTree.hpp"

void StoryTree::addNode(const Node_t &node) {
    auto &bucket = _forest[node.idx_];
    bucket.push_back(node);
}
