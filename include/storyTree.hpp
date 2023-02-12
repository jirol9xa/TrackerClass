#pragma once

#include <unordered_map>
#include <vector>
#include <cstdint>

/// Enumeration for events, which my occur
enum EVENT_TYPE {
  CNSTR,
  DSTR,
  COPY_CNST,
  RVAL_COPY_CNSTR,
  OP_ASGN,
  RVAL_OP_ASGN,

  OP_ADD,
  OP_SUB,
  OP_MUL,
  OP_DIV,

  OP_SUB_ASGN,
  OP_ADD_ASGN,
  OP_MUL_ASGN,
  OP_DIV_SGN,

  PASSED_AS_ARG,
};

class Tracker;

/// Implementation for simple node in StoryTree
struct Node_t {
  Tracker *_tracked_var;
  EVENT_TYPE _type;

  // Mb not enough
  Node_t *_prev;
  Node_t *_next;
};

/// Implementation of story tree for the project
/// It made in the form of singleton pattern for not copying history or
/// tear it apart
class StoryTree {
private:
  std::unordered_map<uint_fast32_t, std::vector<Node_t>> _forest;

  StoryTree();

public:
  static StoryTree &getInstance() {
    static StoryTree Tree;

    return Tree;
  }

  StoryTree(const StoryTree &) = delete;
  void operator=(const StoryTree &) = delete;

  //void addNode(Node)
};
