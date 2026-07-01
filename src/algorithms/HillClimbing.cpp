#include "algorithms/HillClimbing.h"

HillClimbing::HillClimbing(GridProblem problem, const Heuristic<State> *heuristic, HCStrategy strategy)
    : InformedSearchAlgorithm(std::move(problem), heuristic), strategy(std::move(strategy)) {}

shared_ptr<Node<State>> HillClimbing::search() {
    generatedNodes = 0;
    visitedNodes = 0;
    explored = vector<vector<bool>>(GRID_SIZE, vector<bool>(GRID_SIZE, false));

    State current = problem.getInitialState();
    int h = heuristic->calculate(current, problem.getObjectiveState());

    auto node = make_shared<Node<State>>(current, nullptr, 0, h, h);

    while (true) {
        visitedNodes++;
        explored[node->state.x][node->state.y] = true;

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