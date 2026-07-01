#include "algorithms/BestFirstSearch.h"

BestFirstSearch::BestFirstSearch(GridProblem problem, const Heuristic<State> *heuristic, function<int(int, int)> f)
    : InformedSearchAlgorithm(std::move(problem), heuristic),
      evaluationFunction(std::move(f)),
      reachedCosts(GRID_SIZE, vector<int>(GRID_SIZE, INT_MAX)) {}

shared_ptr<Node<State>> BestFirstSearch::search() {
    generatedNodes = 0;
    visitedNodes = 0;
    reachedCosts = vector<vector<int>>(GRID_SIZE, vector<int>(GRID_SIZE, INT_MAX));
    explored = vector<vector<bool>>(GRID_SIZE, vector<bool>(GRID_SIZE, false));

    State initialState = problem.getInitialState();

    int h = heuristic->calculate(initialState, problem.getObjectiveState());
    int f = evaluationFunction(0, h);

    auto node = make_shared<Node<State>>(initialState, nullptr, 0, h, f);

    reachedCosts[initialState.x][initialState.y] = 0;

    priority_queue<shared_ptr<Node<State>>, vector<shared_ptr<Node<State>>>, NodeComparator<State>> frontier;
    frontier.push(node);

    while (!frontier.empty()) {
        node = frontier.top();
        frontier.pop();
        visitedNodes++;
        explored[node->state.x][node->state.y] = true;

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
        int h = heuristic->calculate(neighbor, problem.getObjectiveState());
        int f = evaluationFunction(cost, h);
        validActions.push_back(make_shared<Node<State>>(neighbor, node, cost, h, f));
    }

    return validActions;
}