#include "algorithms/BreadthFirstSearch.h"

BreadthFirstSearch::BreadthFirstSearch(GridProblem problem)
    : SearchAlgorithm(std::move(problem)), visited(GRID_SIZE, vector<bool>(GRID_SIZE, false)) {}

shared_ptr<Node<State>> BreadthFirstSearch::search() {
    generatedNodes = 0;
    visitedNodes = 0;
    visited = vector<vector<bool>>(GRID_SIZE, vector<bool>(GRID_SIZE, false));
    explored = vector<vector<bool>>(GRID_SIZE, vector<bool>(GRID_SIZE, false));

    State initialState = problem.getInitialState();
    auto node = make_shared<Node<State>>(initialState, nullptr, 0, 0, 0);
    visited[initialState.x][initialState.y] = true;

    queue<shared_ptr<Node<State>>> frontier;
    frontier.push(node);

    while (!frontier.empty()) {
        node = frontier.front(); frontier.pop();
        visitedNodes++;
        explored[node->state.x][node->state.y] = true;

        if (problem.isGoal(node->state))
            return node;

        for (const shared_ptr<Node<State>>& child : expand(node)) {
            generatedNodes++;
            const State s = child->state;
            if (!visited[s.x][s.y]) {
                visited[s.x][s.y] = true;
                frontier.push(child);
            }
        }
    }

    return nullptr;
}

vector<shared_ptr<Node<State>>> BreadthFirstSearch::expand(const shared_ptr<Node<State> > &node) const {
    vector<shared_ptr<Node<State>>> children;

    for (const State& neighbor : problem.getValidActions(node->state))
        children.push_back(make_shared<Node<State>>(neighbor, node, node->g + 1, 0, 0));

    return children;
}
