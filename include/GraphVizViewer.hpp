#pragma once

#include "treeViewer.hpp"
#include <fstream>

/// Class for implementing rendering of storyTree with graphViz
class GraphVizViewer : public TreeViewer {
  private:
    const StoryTree &tree_;
    const char *file_name_ = nullptr; // The naem of file where we will write graphviz format graph
    mutable std::ofstream file_;      // It's not const just because second constructor

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
    void makePrologue() const;
    void makeEpilogue() const;
    void showPic() const;
};
