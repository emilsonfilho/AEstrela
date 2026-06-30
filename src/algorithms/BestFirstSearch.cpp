#include "algorithms/BestFirstSearch.h"

shared_ptr<Node<State>> BestFirstSearch::search() {
    generatedNodes = 0;
    visitedNodes = 0;
    reachedCosts = vector<vector<int>>(15, vector<int>(15, INT_MAX));

    State initialState = problem.getInitialState();
    auto node = make_shared<Node<State>>(
        initialState,
        nullptr,
        0,
        heuristic->calculate(initialState, problem.getObjectiveState())
    );

    reachedCosts[initialState.x][initialState.y] = 0;

    priority_queue<shared_ptr<Node<State>>, vector<shared_ptr<Node<State>>>, NodeComparator<State>> frontier;
    frontier.push(node);

    while (!frontier.empty()) {
        node = frontier.top();
        frontier.pop();
        visitedNodes++;

        if (problem.isGoal(node->state))
            return node;

        for (const shared_ptr<Node<State>>& child : expand(node)) {
            generatedNodes++;
            const State s = child->state;
            if (reachedCosts[s.x][s.y] == INT_MAX or child->g < reachedCosts[s.x][s.y]) {
                reachedCosts[s.x][s.y] = child->g; // Already computed in expand function
                frontier.push(child);
            }
        }
    }

    return nullptr;
}

vector<shared_ptr<Node<State>>> BestFirstSearch::expand(const shared_ptr<Node<State>> &node) const {
    vector<shared_ptr<Node<State>>> validActions;
    const State s = node->state;

    for (auto neighbor : problem.getValidActions(s)) {
        int cost = node->g + problem.getCost(neighbor);
        validActions.push_back(
            make_shared<Node<State>>(
                neighbor,
                node,
                cost,
                heuristic->calculate(neighbor, problem.getObjectiveState())
            )
        );
    }

    return validActions;
}

int BestFirstSearch::getGeneratedNodes() const {
    return generatedNodes;
}

int BestFirstSearch::getVisitedNodes() const {
    return visitedNodes;
}
