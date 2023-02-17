#include "graphVizViewer.hpp"

void GraphVizViewer::drawTree() const {
    makePrologue();

    for (uint_fast32_t i = 0; i < tree_.getVarAmnt(); ++i)
        drawVarHistory_intrnl(i);

    makeEpilogue();
    showPic();

    return;
}

void GraphVizViewer::drawVarHistory(uint_fast32_t var_idx) const {
    makePrologue();

    drawVarHistory_intrnl(var_idx);

    makeEpilogue();
    showPic();

    return;
}

void GraphVizViewer::makePrologue() const { file_ << "digraph G {\n"; }

void GraphVizViewer::makeEpilogue() const { file_ << "}\n"; }

void GraphVizViewer::showPic() const {
    file_.close();

    // TODO: Try to find out better implementation of this moment
    std::string system_call = "dot -T png " + std::string(file_name_) + " -o pic.png";
    system(system_call.c_str());
    system("eog pic.png");

    file_.open(file_name_);
}

void GraphVizViewer::drawVarHistory_intrnl(uint_fast32_t var_idx) const {
    auto &history = const_cast<StoryTree &>(tree_).getVarHistory(var_idx);

    for (uint_fast32_t i = 0; i < history.size(); ++i) {
        const Node_t &node = history[i];

        file_ << "    var" << node.idx_ << "[shape = record, label = \""
              << "event: " << printEventName(node.event_) << '|' << node.copy_var_.dump();
        file_ << "\"];\n";

        if (i == 0)
            continue;

        auto event = history[i].event_;
        file_ << "    var" << history[i - 1].idx_ << " -> "
              << "var" << node.idx_ << "[color = "
              << ((event == COPY_CNST || event == RVAL_COPY_CNSTR) ? "\"red\"" : "\"black\"")
              << "];\n";
    }
}
