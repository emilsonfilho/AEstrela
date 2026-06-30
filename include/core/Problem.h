#ifndef AESTRELA_PROBLEM_H
#define AESTRELA_PROBLEM_H

#include <vector>

#define N 15
#define OBSTACLE (-1)

using namespace std;

template <typename StateType>
class Problem {
public:
    virtual ~Problem() = default;

    virtual StateType getInitialState() const = 0;
    virtual StateType getObjectiveState() const = 0;
    virtual bool isGoal(const StateType& state) const = 0;
    virtual vector<StateType> getValidActions(const StateType& state) const = 0;

    virtual int getCost(const StateType& destiny) const = 0;
};

#endif //AESTRELA_PROBLEM_H