#include "core/GridProblem.h"

GridProblem::GridProblem(const vector<vector<int>>& generateMap, const State& start, const State& goal)
    : map(generateMap), initialState(start), objectiveState(goal) {}

State GridProblem::getInitialState() const {
    return initialState;
}

State GridProblem::getObjectiveState() const {
    return objectiveState;
}

bool GridProblem::isGoal(const State& state) const {
    return state == objectiveState;
}

vector<State> GridProblem::getValidActions(const State& state) const {
    vector<State> validActions;

    int x = state.x;
    int y = state.y;

    // North
    if (y + 1 < GRID_SIZE and map[x][y + 1] != OBSTACLE)
        validActions.emplace_back(x, y + 1);
    // East
    if (x + 1 < GRID_SIZE and map[x + 1][y] != OBSTACLE)
        validActions.emplace_back(x + 1, y);
    // South
    if (y - 1 >= 0 and map[x][y - 1] != OBSTACLE)
        validActions.emplace_back(x, y - 1);
    // West
    if (x - 1 >= 0 and map[x - 1][y] != OBSTACLE)
        validActions.emplace_back(x - 1, y);

    return validActions;
}

int GridProblem::getCost(const State& destiny) const {
    return map[destiny.x][destiny.y];
}