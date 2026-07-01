#include "algorithms/SearchAlgorithm.h"

SearchAlgorithm::SearchAlgorithm(GridProblem problem)
    : problem(std::move(problem)), generatedNodes(0), visitedNodes(0), explored(GRID_SIZE,
        vector<bool>(GRID_SIZE, false)) {}

int SearchAlgorithm::getGeneratedNodes() const {
    return generatedNodes;
}

int SearchAlgorithm::getVisitedNodes() const {
    return visitedNodes;
}

const vector<vector<bool> > &SearchAlgorithm::getExplored() const {
    return explored;
}
