#ifndef AESTRELA_HEURISTIC_H
#define AESTRELA_HEURISTIC_H

template <typename StateType>
class Heuristic {
public:
    virtual ~Heuristic() = default;

    virtual int calculate(const StateType& current, const StateType& goal) const = 0;
};

#endif //AESTRELA_HEURISTIC_H