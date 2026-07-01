#ifndef AESTRELA_SEARCHALGORITHM_H
#define AESTRELA_SEARCHALGORITHM_H

#include <memory>

#include "GridProblem.h"
#include "Node.h"

using namespace std;

class SearchAlgorithm {
protected:
    GridProblem problem;
    int generatedNodes;
    int visitedNodes;
    vector<vector<bool>> explored;

    explicit SearchAlgorithm(GridProblem problem);
public:
    virtual ~SearchAlgorithm() = default;

    virtual shared_ptr<Node<State>> search() = 0;

    int getGeneratedNodes() const;
    int getVisitedNodes() const;
    const vector<vector<bool>>& getExplored() const;
};

#endif //AESTRELA_SEARCHALGORITHM_H