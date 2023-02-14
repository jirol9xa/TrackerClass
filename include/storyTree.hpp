#pragma once

#include <cstdint>
#include <unordered_map>
#include <vector>

#include "tracker.hpp"

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
  OP_DIV_ASGN,

  PASSED_AS_ARG,
  INTPR_AS_INT,
};

/// Implementation for simple node in StoryTree
struct Node_t {
  // we need explicit say, that node have no a twin with passing true
  Node_t(const Tracker *tracked_var, const EVENT_TYPE event,
         bool is_unique = false)
      : tracked_var_(tracked_var), event_(event) {
    obj_amnt_ += is_unique;
    idx_ = obj_amnt_;

    // We need to copy elementwise, because we don't want to trigger copy
    // constructor
    copy_var_.val_ = tracked_var->val_;
    copy_var_.loc_ = tracked_var->loc_;
    copy_var_.ops_rmnd_ = tracked_var->ops_rmnd_;
  }

  const Tracker *tracked_var_;
  Tracker copy_var_;
  const EVENT_TYPE event_;
  uint_fast32_t idx_;

private:
  static uint_fast32_t obj_amnt_;
};

/// Implementation of story tree for the project
/// It made in the form of singleton pattern for not copying history or
/// tear it apart
class StoryTree {
private:
  std::unordered_map<uint_fast32_t, std::vector<Node_t>> _forest;

  StoryTree(){};

public:
  static StoryTree &getInstance() {
    static StoryTree Tree;
    return Tree;
  }

  StoryTree(const StoryTree &) = delete;
  void operator=(const StoryTree &) = delete;

  void addNode(const Node_t &node);
};

// Name of global var, that should be use as a story tree
extern StoryTree &kTree;
