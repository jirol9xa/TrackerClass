#pragma once

#include "StoryTree.hpp"
#include "TreeViewer.hpp"
#include <fstream>
#include <unordered_set>

/// Class for implementing rendering of storyTree with graphViz
class GraphVizViewer : public TreeViewer {
  private:
    const StoryTree &tree_;
    const char *file_name_ = nullptr; // The naem of file where we will write graphviz format graph
    mutable std::ofstream file_;      // It's not const just because second constructor

    // That vector contains indexes of variables, that were already printed
    // FIXME: For a big amount of tracking vars, it is better to do std::unordered_set<>,
    // but it is cost too much memory in conditios of small number of variables.
    // But unordered_set has better interface, so I will use it.
    mutable std::unordered_set<uint_fast32_t> alrdy_printed_idxs_;

  public:
    // FIXME: Add Implementation of that ctor, now it cause memleak
    GraphVizViewer(const StoryTree &tree, const char *file_name)
        : tree_(tree), file_name_(file_name) {
        file_ = std::ofstream(file_name_);
    }

    void drawTree() const override;
    void drawVarHistory(uint_fast32_t var_idx) const override;

    ~GraphVizViewer() { file_.close(); }

  private:
    void drawVarHistory_intrnl(uint_fast32_t var_idx) const;
    void drawVarsInNode(const Node_t &node, uint_fast32_t caller_idx) const;
    void makePrologue() const;
    void makeEpilogue() const;
    void showPic() const;
    bool isPrinted(uint_fast32_t var_idx) const;
    void markPrinted(uint_fast32_t var_idx) const;
};
