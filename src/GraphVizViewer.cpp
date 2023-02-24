#include "GraphVizViewer.hpp"

#include <iostream>

void GraphVizViewer::drawVarsInNode(const Node_t &node, uint_fast32_t caller_idx) const {
    unsigned var_amnt = node.getTrackingVarsAmnt();
    if (var_amnt < 2)
        return;

    for (unsigned i = 0; i < var_amnt; i++) {
        uint_fast32_t var_idx = node.getVarIdxOnPos(i);
        if (i != caller_idx && !isPrinted(var_idx)) {
            // markPrinted(var_idx);
            drawVarHistory_intrnl(var_idx);
        }
    }
}

void GraphVizViewer::markPrinted(uint_fast32_t var_idx) const {
    alrdy_printed_idxs_.insert(var_idx);
}

void GraphVizViewer::drawTree() const {
    makePrologue();

    unsigned var_amnt = tree_.getVarAmnt();
    for (uint_fast32_t i = 0; i < var_amnt; ++i)
        drawVarHistory_intrnl(i);

    makeEpilogue();
    showPic();

    return;
}

void GraphVizViewer::drawVarHistory(uint_fast32_t var_idx) const {
    makePrologue();

    // tree_.sortNodes();
    drawVarHistory_intrnl(var_idx);

    makeEpilogue();
    showPic();

    return;
}

bool GraphVizViewer::isPrinted(uint_fast32_t var_idx) const {
    return alrdy_printed_idxs_.find(var_idx) != alrdy_printed_idxs_.end();
}

void GraphVizViewer::makePrologue() const { file_ << "digraph G {\n"; }

void GraphVizViewer::makeEpilogue() const { file_ << "}\n"; }

void GraphVizViewer::showPic() const {
    file_.close();

    // We need clear set for correct printing next time
    alrdy_printed_idxs_.clear();

    // TODO: Try to find out better implementation of this moment
    std::string system_call = "dot -T png " + std::string(file_name_) + " -o pic.png";
    system(system_call.c_str());
    system("eog pic.png");

    file_.open(file_name_);
}

namespace {
bool isCtor(const Node_t &node, uint_fast32_t var_idx) {
    const EVENT_TYPE event = node.event_;
    // if event is one type of ctor, we need make sure, that we have created
    // element, so we check first position, because we always write *this on first
    // and that on second position.
    return (event == CTOR || event == RVAL_COPY_CNSTR || event == RVAL_OP_ASGN ||
            event == COPY_CNST) &&
           (node.getVarIdxOnPos(0) == var_idx);
}
} // namespace

void GraphVizViewer::drawVarHistory_intrnl(uint_fast32_t var_idx) const {
    if (isPrinted(var_idx))
        return;

    markPrinted(var_idx);
    const auto &history = tree_.getVarHistory(var_idx);

    for (uint_fast32_t i = 0; i < history.size(); ++i) {
        const auto &node = tree_.getNode(history.at(i));

        // If node contains more than one var, it means that the node represent binary operation
        // or function call, so we need to expect the history of outer vars for completeness
        drawVarsInNode(node, var_idx);

        const auto *var = node.findVarInNodeList(var_idx);

        file_ << "    var" << node.idx_ << "[shape = record, label = \""
              << "event: " << printEventName(node.event_);
        if (node.getTrackingVarsAmnt() == 1 || isCtor(node, var->getIdx()))
            file_ << '|' << var->dump();
        file_ << "\"];\n";

        if (i == 0)
            continue;

        auto event = node.event_;
        file_ << "    var" << tree_.getNode(history.at(i - 1)).idx_ << " -> "
              << "var" << node.idx_ << "[color = "
              << ((event == COPY_CNST || event == RVAL_COPY_CNSTR) ? "\"red\"" : "\"black\"")
              << "];\n";
    }
}
