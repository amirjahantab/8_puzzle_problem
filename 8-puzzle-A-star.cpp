/*
#include <iostream> // input-output operations
#include <vector> // similar to python list
#include <queue> // FIFO data structure
#include <map> // similar to pyhton's dictionary 
#include <algorithm> // Provides general algorithms
using namespace std;

vector<int> goal = {1, 2, 3, 4, 5, 6, 7, 8, 0};
vector<int> initial_state = {1, 2, 3, 4, 0, 6, 7, 5, 8}; 

// Defines the structure for each state of the puzzle.
struct PuzzleState {
    // self.state = []
    vector<int> state; // Stores the current puzzle configuration, where each integer represents a tile
    int empty_index; // Index of the empty  (zero) tile
    int g; // Cost from start to current state
    int h; // Heuristic cost (Manhattan distance)
    // self.path = []
    vector<vector<int>> path; // Path from initial state to current state

    // Comparator for priority queue (min-heap)
    bool operator>(PuzzleState other) const {
        return (g + h) > (other.g + other.h);
    }
};

// Function to calculate Manhattan distance heuristic
int calculateHeuristic(vector<int> state) {
    
    int distance = 0;
    int gridSize = 3; // For a 3x3 grid

    for (int i = 0; i < state.size(); i++) {
        if (state[i] == 0) continue; // Skip the empty tile

        // Find the target position of the current tile in the goal state
        int targetIndex = -1;
        for (int j = 0; j < goal.size(); j++) {
            if (goal[j] == state[i]) {
                targetIndex = j;
                break;
            }
        }
        int currentRow = i / gridSize;
        int currentCol = i % gridSize;
        int targetRow = targetIndex / gridSize;
        int targetCol = targetIndex % gridSize;

        // Add the Manhattan distance for this tile to the total distance
        distance += abs(currentRow - targetRow) + abs(currentCol - targetCol);
    }

    return distance;
}

// Function to generate possible moves
vector<PuzzleState> generateMoves(const PuzzleState current) {
    vector<PuzzleState> moves; // moves = []
    int empty_index = current.empty_index;
    vector<int> directions = {-1, 1, -3, 3}; // Left, Right, Up, Down moves

    for (int direction : directions) {
        int new_index = empty_index + direction;
        if (new_index >= 0 && new_index < 9 &&
            !(empty_index % 3 == 0 && direction == -1) &&
            !(empty_index % 3 == 2 && direction == 1)) {
            vector<int> new_state = current.state;
            swap(new_state[empty_index], new_state[new_index]);
            vector<vector<int>> new_path = current.path;
            new_path.push_back(new_state); // new_path.append(new_state)
            moves.push_back({new_state, new_index, current.g + 1, calculateHeuristic(new_state), new_path});
        }
    }
    return moves;
}

// Function to print the puzzle
void printPuzzle(const vector<int>& state) {
    for (int i = 0; i < 9; ++i) {
        if (i % 3 == 0) cout << "\n";
        cout << state[i] << " ";
    }
    cout << "\n";
}

// Function to solve the puzzle using A* algorithm
void solvePuzzle(const vector<int>& initial_state) {
    priority_queue<PuzzleState, vector<PuzzleState>, greater<PuzzleState>> open_list; // open_list = []
    map<vector<int>, bool> visited; // visited = dict()

    // initial_state.index(0)
    int initial_empty_index = find(initial_state.begin(), initial_state.end(), 0) - initial_state.begin();
    open_list.push({initial_state, initial_empty_index, 0, calculateHeuristic(initial_state), {initial_state}});

    while (!open_list.empty()) {
        PuzzleState current = open_list.top();
        open_list.pop();

        if (current.h == 0) {
            cout << "Solution found!\n";
            for (const auto& step : current.path) {
                printPuzzle(step);
                cout << "----\n";
            }
            return;
        }

        visited[current.state] = true;

        vector<PuzzleState> moves = generateMoves(current);
        for (const auto& move : moves) {
            if (visited.find(move.state) == visited.end()) {
                open_list.push(move);
            }
        }
    }

    cout << "No solution found.\n";
}

int main() {
    cout << "Initial puzzle state:\n";
    printPuzzle(initial_state);

    solvePuzzle(initial_state);

    return 0;
}
*/
// A*
#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>

using namespace std;

struct PuzzleState {
    vector<int> state;
    int empty_index;
    int g;
    int h; 
    vector<vector<int>> path;

    bool operator>(const PuzzleState& other) const {
        return (g + h) > (other.g + other.h);
    }
};

vector<int> goal = {1, 2, 3, 8, 0, 4, 7, 6, 5};
vector<int> initial_state = {2, 8, 3, 1, 6, 4, 7, 0, 5};



int calculateHeuristic(const vector<int>& state) {
    int distance = 0;
    int gridSize = 3;
    for (int i = 0; i < state.size(); i++) {
        if (state[i] == 0) continue;
        int targetIndex = find(goal.begin(), goal.end(), state[i]) - goal.begin();
        int currentRow = i / gridSize;
        int currentCol = i % gridSize;
        int targetRow = targetIndex / gridSize;
        int targetCol = targetIndex % gridSize;
        distance += abs(currentRow - targetRow) + abs(currentCol - targetCol);
    }
    return distance;
}

vector<PuzzleState> generateMoves(const PuzzleState& current) {
    vector<PuzzleState> moves;
    int empty_index = current.empty_index;
    vector<int> directions = {-1, 1, -3, 3}; 

    for (int direction : directions) {
        int new_index = empty_index + direction;
        if (new_index >= 0 && new_index < 9 &&
            !(empty_index % 3 == 0 && direction == -1) &&
            !(empty_index % 3 == 2 && direction == 1)) {
            vector<int> new_state = current.state;
            swap(new_state[empty_index], new_state[new_index]);
            vector<vector<int>> new_path = current.path;
            new_path.push_back(new_state);
            moves.push_back({new_state, new_index, current.g + 1, calculateHeuristic(new_state), new_path});
        }
    }
    return moves;
}

void printPuzzle(const vector<int>& state) {
    for (int i = 0; i < 9; ++i) {
        if (i % 3 == 0) cout << "\n";
        cout << state[i] << " ";
    }
    cout << "\n";
}

bool isGoalState(const vector<int>& state) {
    return state == goal;
}

void solvePuzzleAStar(const vector<int>& initial_state) {
    priority_queue<PuzzleState, vector<PuzzleState>, greater<PuzzleState>> open_list;
    map<vector<int>, bool> visited;
    int initial_empty_index = find(initial_state.begin(), initial_state.end(), 0) - initial_state.begin();
    open_list.push({initial_state, initial_empty_index, 0, calculateHeuristic(initial_state), {initial_state}});

    int nodesExpanded = 0; 

    while (!open_list.empty()) {
        PuzzleState current = open_list.top();
        open_list.pop();

        

        if (isGoalState(current.state)) {
            cout << "Solution found (A*)!\n";
            cout << "Number of nodes expanded: " << nodesExpanded << "\n"; 
            for (const auto& step : current.path) {
                printPuzzle(step);
                cout << "----\n";
            }
            return;
        }

        visited[current.state] = true;
        vector<PuzzleState> moves = generateMoves(current);
        nodesExpanded++; 
        for (const auto& move : moves) {
            if (visited.find(move.state) == visited.end()) {
                open_list.push(move);
            }
        }
    }

    cout << "No solution found (A*).\n";
    cout << "Number of nodes expanded: " << nodesExpanded << "\n"; 
}

int main() {
    cout << "Initial puzzle state:\n";
    printPuzzle(initial_state);
    solvePuzzleAStar(initial_state);
    return 0;
}
