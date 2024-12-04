#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> goal = {1, 2, 3, 8, 0, 4, 7, 6, 5};
vector<int> initial_state = {2, 8, 3, 1, 6, 4, 7, 0, 5};


// Function to check if the current state is the goal state
bool isGoalState(const vector<int>& state) {
    return state == goal;
}

// Function to print the puzzle
void printPuzzle(const vector<int>& state) {
    for (int i = 0; i < 9; ++i) {
        if (i % 3 == 0) cout << "\n";
        cout << state[i] << " ";
    }
    cout << "\n";
}

// Function to generate possible moves
vector<vector<int>> generateMoves(const vector<int>& state, int empty_index) {
    vector<vector<int>> moves;
    vector<int> directions = {-1, 1, -3, 3}; // Left, Right, Up, Down moves

    for (int direction : directions) {
        int new_index = empty_index + direction;
        if (new_index >= 0 && new_index < 9 &&
            !(empty_index % 3 == 0 && direction == -1) &&
            !(empty_index % 3 == 2 && direction == 1)) {
            vector<int> new_state = state;
            swap(new_state[empty_index], new_state[new_index]);
            moves.push_back(new_state);
        }
    }
    return moves;
}

// Depth-Limited Search function
bool DLS(vector<int> state, int empty_index, int depth_limit, vector<vector<int>>& path, int& nodesExpanded) {    
    if (isGoalState(state)) {
        path.push_back(state);
        return true;
    }

    if (depth_limit <= 0) {
        return false;
    }

    vector<vector<int>> moves = generateMoves(state, empty_index);
    nodesExpanded++;

    for (const auto& move : moves) {
        int new_empty_index = find(move.begin(), move.end(), 0) - move.begin();
        if (DLS(move, new_empty_index, depth_limit - 1, path, nodesExpanded)) {
            path.push_back(state);
            return true;
        }
    }
    return false;
}

// Iterative Deepening Search function
bool IDS(vector<int> initial_state, int initial_empty_index, int max_depth, vector<vector<int>>& path, int& nodesExpanded) {
    for (int depth = 0; depth <= max_depth; ++depth) {
        vector<vector<int>> current_path;
        if (DLS(initial_state, initial_empty_index, depth, current_path, nodesExpanded)) {
            path = current_path;
            return true;
        }
    }
    return false;
}

int main() {
    int initial_empty_index = find(initial_state.begin(), initial_state.end(), 0) - initial_state.begin();
    int max_depth = 20; // Set a maximum depth for IDS
    vector<vector<int>> path;

    int nodesExpanded = 0; 

    if (IDS(initial_state, initial_empty_index, max_depth, path, nodesExpanded)) {
        cout << "Solution found!\n";
        cout << "Number of nodes expanded: " << nodesExpanded << "\n";
        reverse(path.begin(), path.end());
        for (const auto& step : path) {
            printPuzzle(step);
            cout << "----\n";
        }
    } else {
        cout << "No solution found within the depth limit.\n";
        cout << "Number of nodes expanded: " << nodesExpanded << "\n"; 
    }

    return 0;
}
