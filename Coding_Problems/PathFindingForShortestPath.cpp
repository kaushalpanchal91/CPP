/* Implement A* or Dijkstra’s algorithm for pathfinding in a grid environment.
The grid should represent the road, with some cells as obstacles.
Your program should find the shortest path from a start point to a destination.
*/

/* Learn Vector<>, Pair<>, Priority_queue<> */


#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <utility>

using namespace std;

const int ROW = 5; // Number of rows
const int COL = 5; // Number of columns

// A structure to represent a cell in the grid
struct Cell {
    int x, y;
    int cost; // Cost to reach this cell
};

// Comparator for the priority queue
struct CompareCost {
    bool operator()(const Cell& a, const Cell& b) {
        return a.cost > b.cost;
    }
};

// Function to check if a cell is valid
bool isValid(int row, int col) {
    return (row >= 0 && row < ROW && col >= 0 && col < COL);
}

// Dijkstra's algorithm to find the shortest path
void dijkstra(int grid[ROW][COL], pair<int, int> start, pair<int, int> destination) {
    priority_queue<Cell, vector<Cell>, CompareCost> pq;
    vector<vector<int>> cost(ROW, vector<int>(COL, numeric_limits<int>::max()));
    vector<vector<pair<int, int>>> parent(ROW, vector<pair<int, int>>(COL, {-1, -1}));

    int rowDir[] = {-1, 1, 0, 0}; // Direction vectors for up, down, left, right
    int colDir[] = {0, 0, -1, 1};

    // Starting point
    cost[start.first][start.second] = 0;
    pq.push({start.first, start.second, 0});

    while (!pq.empty()) {
        Cell current = pq.top();
        pq.pop();

        // If we reach the destination, construct the path
        if (current.x == destination.first && current.y == destination.second) {
            vector<pair<int, int>> path;
            pair<int, int> step = destination;

            while (step != make_pair(-1, -1)) {
                path.push_back(step);
                step = parent[step.first][step.second];
            }

            cout << "Shortest Path: ";
            for (auto it = path.rbegin(); it != path.rend(); ++it) {
                cout << "(" << it->first << ", " << it->second << ") ";
            }
            cout << endl;
            return;
        }

        // Explore neighbors
        for (int i = 0; i < 4; ++i) {
            int newX = current.x + rowDir[i];
            int newY = current.y + colDir[i];

            if (isValid(newX, newY) && grid[newX][newY] == 0) { // Check if it's not an obstacle
                int newCost = current.cost + 1; // Cost is 1 for moving to adjacent cell

                // If a cheaper path to the neighbor is found
                if (newCost < cost[newX][newY]) {
                    cost[newX][newY] = newCost;
                    parent[newX][newY] = {current.x, current.y};
                    pq.push({newX, newY, newCost});
                }
            }
        }
    }

    std::cout << "No path found!" << endl;
}

int main() {
    // 0 represents free cell, 1 represents obstacle
    int grid[ROW][COL] = {
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 1},
        {0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 0, 0, 0}
    };

    pair<int, int> start = {0, 0}; // Starting point
    pair<int, int> destination = {4, 4}; // Destination point

    dijkstra(grid, start, destination);

    return 0;
}
