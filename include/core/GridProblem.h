#ifndef AESTRELA_GRIDPROBLEM_H
#define AESTRELA_GRIDPROBLEM_H

#include <vector>

#include "core/Problem.h"
#include "core/State.h"

#define N 15
#define OBSTACLE (-1)

using namespace std;

class GridProblem : public Problem<State> {
private:
    vector<vector<int>> map;
    State initialState;
    State objectiveState;
public:
    GridProblem(const vector<vector<int>>& generateMap, const State& start, const State& goal);

    State getInitialState() const override;
    State getObjectiveState() const override;
    bool isGoal(const State& state) const override;
    vector<State> getValidActions(const State& state) const override;
    int getCost(const State& destiny) const override;
};

#endif //AESTRELA_GRIDPROBLEM_H
