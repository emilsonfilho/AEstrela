#ifndef AESTRELA_BESTFIRSTSEARCH_H
#define AESTRELA_BESTFIRSTSEARCH_H

#include <utility>
#include <vector>
#include <memory>
#include <climits>
#include <queue>
#include <functional>

#include "Heuristic.h"
#include "core/GridProblem.h"
#include "core/State.h"
#include "core/Node.h"

using namespace std;

class BestFirstSearch {
private:
    GridProblem problem;
    const Heuristic<State>* heuristic;
    int generatedNodes;
    int visitedNodes;
    function<int(int, int)> evaluationFunction;

    vector<vector<int>> reachedCosts;
public:
    BestFirstSearch(GridProblem  problem, const Heuristic<State>* heuristic, function<int(int, int)> f)
        : problem(std::move(problem)), heuristic(heuristic), generatedNodes(0), visitedNodes(0), evaluationFunction(std::move(f)) {
        reachedCosts = vector<vector<int>>(15, vector<int>(15, INT_MAX));
    }

    shared_ptr<Node<State>> search();
    vector<shared_ptr<Node<State>>> expand(const shared_ptr<Node<State>> &node) const;

    int getGeneratedNodes() const;
    int getVisitedNodes() const;
};

#endif //AESTRELA_BESTFIRSTSEARCH_H