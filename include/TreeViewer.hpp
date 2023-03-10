#pragma once

#include <cstdint>

// Class, that implement interface for rendering storyTree
class TreeViewer {
  public:
    virtual void drawTree() const = 0;
    virtual void drawVarHistory(uint_fast32_t var_idx) const = 0;
};
