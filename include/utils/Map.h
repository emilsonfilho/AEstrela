#ifndef AESTRELA_MAP_H
#define AESTRELA_MAP_H

#include "configs/Constants.h"

#include <vector>
#include <iostream>
#include <random>

#include "GridProblem.h"
#include "algorithms/BreadthFirstSearch.h"
#include "core/State.h"

using namespace std;

class Map {
public:
    // Cores
    static constexpr auto RESET = "\033[0m";
    static constexpr auto RED = "\033[31m";
    static constexpr auto GREEN = "\033[1;32m";
    static constexpr auto YELLOW = "\033[1;33m";
    static constexpr auto GRAY = "\033[90m";
    static constexpr auto BLUE_BG = "\033[44;1m";

    static inline bool isReachable(const GridProblem& problem) {
        BreadthFirstSearch bfs(problem);
        return bfs.search() != nullptr;
    }

    static inline vector<vector<int>> generateValidMap(double obstaclePercentage, State start, State goal) {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> costDist(3, 6);
        uniform_real_distribution<> obsDist(0.0, 1.0);

        vector<vector<int>> map(GRID_SIZE, vector<int>(GRID_SIZE, 0));
        bool valid = false;

        cout << "Gerando mapa com " << (obstaclePercentage * 100) << "% de obstáculos.\n";

        while (!valid) {
            for (int x = 0; x < GRID_SIZE; x++) {
                for (int y = 0; y < GRID_SIZE; y++) {
                    if ((x == start.x and y == start.y) or (x == goal.x and y == goal.y)) {
                        map[x][y] = costDist(gen);
                        continue;
                    }

                    if (obsDist(gen) < obstaclePercentage) {
                        map[x][y] = OBSTACLE;
                    } else {
                        map[x][y] = costDist(gen);
                    }
                }
            }

            GridProblem tempProblem(map, start, goal);
            valid = isReachable(tempProblem);
        }

        return map;
    }

    static inline void printMap(
        const vector<vector<int>>& map,
        const State start,
        const State goal,
        const vector<State>& path,
        const vector<vector<bool>>& explored = vector<vector<bool>>()
    ) {
        vector<vector<bool>> isPath(GRID_SIZE, vector<bool>(GRID_SIZE, false));
        for (const State& s : path)
            isPath[s.x][s.y] = true;

        bool showExplored = !explored.empty();

        cout << "\n";

        for (int y = GRID_SIZE - 1; y >= 0; y--) {
            for (int x = 0; x < GRID_SIZE; x++) {
                if (x == start.x and y == start.y) {
                    cout << BLUE_BG << " S " << RESET;
                } else if (x == goal.x and y == goal.y) {
                    cout << BLUE_BG << " G " << RESET;
                } else if (map[x][y] == OBSTACLE) {
                    cout << RED << " # " << RESET;
                } else if (isPath[x][y]) {
                    cout << GREEN << " " << map[x][y] << " " << RESET;
                } else if (showExplored and explored[x][y]) {
                    cout << GRAY << " " << map[x][y] << " " << RESET;
                } else {
                    cout << " " << map[x][y] << " ";
                }
            }
            cout << "\n";
        }
        cout << "\n";
    }
};

#endif //AESTRELA_MAP_H