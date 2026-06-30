#ifndef AESTRELA_STATE_H
#define AESTRELA_STATE_H

struct State {
    int x;
    int y;

    State();
    State(int x, int y);

    bool operator==(const State& other) const;
    bool operator!=(const State& other) const;
};

#endif //AESTRELA_STATE_H