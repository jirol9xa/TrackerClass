#pragma once

#include "Tracker.hpp"
#include <algorithm>
#include <boost/core/noncopyable.hpp>
#include <cstdint>
#include <unordered_map>
#include <vector>

/// Enumeration for events, which my occur
enum EVENT_TYPE {
#define DEF_EVENT(param) param,
#include "Events.inc"
#undef DEF_EVENT

};

std::string printEventName(enum EVENT_TYPE event);

/// Implementation for simple node in StoryTree
struct Node_t : private boost::noncopyable {
    // we need explicit say, that node have no a twin with passing true
    Node_t(const EVENT_TYPE event, bool is_unique = false) : event_(event) {
        obj_amnt_ += is_unique;
        idx_ = obj_amnt_;

        // We need to copy elementwise, because we don't want to trigger copy
        // constructor
        /*
        copy_var_.val_ = tracked_var->val_;
        copy_var_.loc_ = tracked_var->loc_;
        copy_var_.ops_rmnd_ = tracked_var->ops_rmnd_;
        copy_var_.idx_ = tracked_var->idx_;
        */
    }

    Node_t(const Node_t &that) = delete;
    const Node_t &operator=(const Node_t &that) = delete;

    EVENT_TYPE event_;
    uint_fast32_t idx_;

    // That vector used, while showing history of obj, because if the value of var was bornn from
    // values of two vars, we need to show that values too
    std::vector<Tracker *> tracking_vars_;

    ~Node_t();

  private:
    static uint_fast32_t obj_amnt_;
};

/// Implementation of story tree for the project
/// It made in the form of singleton pattern for not copying history or
/// tear it apart
class StoryTree {
  private:
    mutable std::unordered_map<uint_fast32_t, std::vector<uint_fast32_t>> forest_;
    mutable std::vector<Node_t *> nodes_;

    StoryTree(){};

  public:
    static StoryTree &getInstance() {
        static StoryTree Tree;
        return Tree;
    }

    StoryTree(const StoryTree &) = delete;
    void operator=(const StoryTree &) = delete;

    /// That method just insert node into std::vector<>, but don't add anything in forest_ map
    /// we have non const Node_t *, because we will link that node on the next step, so we will
    /// modify it
    void addNode(Node_t *node);
    /// That method don't add anything in std::vector<>, but link nodes_ with history in forest_ map
    void linkNode(Node_t *node, const Tracker &var);

    void addLink2Nodes(const EVENT_TYPE node, const Tracker &first, const Tracker &second);

    std::vector<uint_fast32_t> getVarHistory(uint_fast32_t idx) const { return forest_[idx]; }
    const Node_t &getNode(uint_fast32_t idx) const { return *nodes_[idx]; }

    uint_fast32_t getVarAmnt() const { return forest_.size(); }

    // void sortNodes() const;

    ~StoryTree();
};

// Name of global var, that should be use as a story tree
extern StoryTree &kTree;
