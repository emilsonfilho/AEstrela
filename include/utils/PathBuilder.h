#ifndef AESTRELA_PATHBUILDER_H
#define AESTRELA_PATHBUILDER_H

#include <memory>
#include <vector>
#include <algorithm>

#include "Node.h"

using namespace std;

template <typename T>
vector<T> buildPath(const shared_ptr<Node<T>>& goalNode) {
    vector<T> path;

    for (auto current = goalNode; current != nullptr; current = current->parent)
        path.push_back(current->state);

    reverse(path.begin(), path.end());
    return path;
}

#endif //AESTRELA_PATHBUILDER_H
