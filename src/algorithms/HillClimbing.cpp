#include "algorithms/HillClimbing.h"

shared_ptr<Node<State>> HillClimbing::search() {
    generatedNodes = 0;
    visitedNodes = 0;

    State current = problem.getInitialState();
    int h = heuristic->calculate(current, problem.getObjectiveState());

    auto node = make_shared<Node<State>>(current, nullptr, 0, h, h);

    while (true) {
        visitedNodes++;

        if (problem.isGoal(node->state))
            return node;

        vector<shared_ptr<Node<State>>> neighbors = expand(node);

        const shared_ptr<Node<State>> best = strategy(node, neighbors);

        if (!best)
            return nullptr;

        node = best;
    }
}

vector<shared_ptr<Node<State>>> HillClimbing::expand(const shared_ptr<Node<State>>& node) {
    vector<shared_ptr<Node<State>>> neighbors;

    for (const State& neighbor : problem.getValidActions(node->state)) {
        generatedNodes++;

        int h = heuristic->calculate(neighbor, problem.getObjectiveState());
        int g = node->g + problem.getCost(neighbor);

        neighbors.push_back(make_shared<Node<State>>(neighbor, node, g, h, h));
    }

    return neighbors;
}

int HillClimbing::getVisitedNodes() const {
    return visitedNodes;
}

int HillClimbing::getGeneratedNodes() const {
    return generatedNodes;
}
