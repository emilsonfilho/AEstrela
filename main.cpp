#include <iostream>
#include <vector>
#include <algorithm>

#include "core/GridProblem.h"
#include "algorithms/BestFirstSearch.h"
#include "heuristics/ManhattanDistance.h"

using namespace std;

int main() {
    vector<vector<int>> map(15, vector<int>(15, 1));

    // Alguns obstáculos
    map[1][0] = OBSTACLE;
    map[1][1] = OBSTACLE;
    map[1][2] = OBSTACLE;
    map[1][3] = OBSTACLE;

    const State start(0, 0);
    const State goal(4, 4);

    const GridProblem problem(map, start, goal);
    const ManhattanDistance heuristic;

    BestFirstSearch aStar(problem, &heuristic, [](const int g, const int h) {
        return g + h;
    });

    BestFirstSearch greedy(problem, &heuristic, [](const int g, const int h) {
        return h;
    });

    BestFirstSearch aStarH3(problem, &heuristic, [](const int g, const int h) {
        return g + 3 * h;
    });


    const auto solution = greedy.search();

    if (solution == nullptr) {
        cout << "Nenhum caminho encontrado.\n";
        return 0;
    }

    cout << "Caminho encontrado!\n";
    cout << "Custo total: " << solution->g << "\n";
    cout << "Nos visitados: " << greedy.getVisitedNodes() << "\n";
    cout << "Nos gerados: " << greedy.getGeneratedNodes() << "\n\n";

    vector<State> path;

    for (auto current = solution; current != nullptr; current = current->parent) {
        path.push_back(current->state);
    }

    reverse(path.begin(), path.end());

    cout << "Caminho:\n";

    for (const State& s : path) {
        cout << "(" << s.x << ", " << s.y << ")\n";
    }

    return 0;
}