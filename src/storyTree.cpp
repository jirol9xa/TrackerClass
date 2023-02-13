#include "storyTree.hpp"

void StoryTree::addNode(const Node_t &node) {
  auto &bucket = _forest[node._idx];
  bucket.push_back(node);
}
