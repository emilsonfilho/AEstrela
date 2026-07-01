#ifndef AESTRELA_BREADTHFIRSTSEARCH_H
#define AESTRELA_BREADTHFIRSTSEARCH_H
#include "SearchAlgorithm.h"

#include <queue>

class BreadthFirstSearch : public SearchAlgorithm {
private:
    vector<vector<bool>> visited;

public:
    explicit BreadthFirstSearch(GridProblem problem);

    shared_ptr<Node<State>> search() override;
    vector<shared_ptr<Node<State>>> expand(const shared_ptr<Node<State>>& node) const;
};

#endif //AESTRELA_BREADTHFIRSTSEARCH_H