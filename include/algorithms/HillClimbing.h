#ifndef AESTRELA_HILLCLIMBING_H
#define AESTRELA_HILLCLIMBING_H
#include "GridProblem.h"
#include "Heuristic.h"

#include <functional>
#include <memory>
#include <utility>

#include "Node.h"

using namespace std;
using HCStrategy =
    function<shared_ptr<Node<State>>(const shared_ptr<Node<State>>&, const vector<shared_ptr<Node<State>>>&)>;

class HillClimbing {
private:
    GridProblem problem;
    const Heuristic<State>* heuristic;
    HCStrategy strategy;
    int generatedNodes;
    int visitedNodes;
public:
    HillClimbing(GridProblem problem, const Heuristic<State>* heuristic, HCStrategy strategy)
        : problem(std::move(problem)), heuristic(heuristic), strategy(std::move(strategy)), generatedNodes(0), visitedNodes(0) {}

    shared_ptr<Node<State>> search();
    vector<shared_ptr<Node<State>>> expand(const shared_ptr<Node<State>>& node);

    int getGeneratedNodes() const;
    int getVisitedNodes() const;
};

#endif //AESTRELA_HILLCLIMBING_H