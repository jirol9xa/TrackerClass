#pragma once

#include <unordered_map>
#include <vector>

class Tracker;
class Node_t {};

/// Implementation of story tree for the project
/// It made in the form of singleton pattern for not copying history or
/// tear it apart
class StoryTree {
private:
  std::unordered_map<Tracker *, std::vector<Node_t>> _forest;

  StoryTree();

public:
  static StoryTree &getInstance() {
    static StoryTree Tree;

    return Tree;
  }

  StoryTree(const StoryTree &) = delete;
  void operator=(const StoryTree &) = delete;
};
