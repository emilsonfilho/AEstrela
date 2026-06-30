#ifndef AESTRELA_NODE_H
#define AESTRELA_NODE_H

#include <memory>

using namespace std;

template <typename StateType>
struct Node {
    StateType state;
    shared_ptr<Node<StateType>> parent;

    int g; // Custo acumulado
    int h; // Heurística

    Node(StateType state, shared_ptr<Node<StateType>> parent, int g, int h)
        : state(state), parent(parent), g(g), h(h) {}

    int getF() const {
        return g + h;
    }
};

template <typename StateType>
struct NodeComparator {
    bool operator()(const shared_ptr<Node<StateType>>& a, const shared_ptr<Node<StateType>>& b) const {
        int fA = a->getF();
        int fB = b->getF();

        if (fA == fB)
            return a->g < b->g;

        // Usar o operador "maior que" para que o MENOR valor fique no topo do MinHeap
        return fA > fB;
    }
};

#endif //AESTRELA_NODE_H