#include "graphVizViewer.hpp"
#include "macro.hpp"
#include "storyTree.hpp"
#include "tracker.hpp"
#include <fstream>
#include <iostream>

uint_fast32_t Tracker::obj_amnt_ = 0;
uint_fast32_t Tracker::same_time_alive_ = 0;

uint_fast32_t Node_t::obj_amnt_ = 0;

StoryTree &kTree = StoryTree::getInstance();

int main() {
    GraphVizViewer render_viz(kTree, "history.dot");

    CREATE_AND_INIT(A, 100);
    CREATE_AND_INIT(B, 4);

    CREATE_AND_INIT(C, USE(A) + USE(B));
    USE(A) * USE(B);

    render_viz.drawTree();

    return 0;
}
