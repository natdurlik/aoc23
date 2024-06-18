#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <deque>
#include <numeric>
#include <sstream>
#include "utils_aoc.h"

using namespace std;

int
dfs(const vector<string> &grid, const pair<int, int> &curr,
    unordered_map<char, vector<vector<int>>> &trail_to_moves,
    const pair<int, int> &stop, vector<vector<bool>>& visited) {
    if (curr == stop) {
        return 0;
    }
    int i = curr.first;
    int j = curr.second;

    int max_path = -1;
    for (const auto &move: trail_to_moves[grid[i][j]]) {
        int row = i + move[0];
        int col = j + move[1];

        if (row >= 0 && col >= 0 && row < grid.size() && col < grid[0].size() && !visited[row][col] &&
            grid[row][col] != '#') {

            visited[row][col] = true;
            int path = dfs(grid, {row, col}, trail_to_moves, stop, visited);
            visited[row][col] = false;
            if (path != -1) {
                max_path = max(max_path, path + 1);
            }
        }
    }

    return max_path;
}

void part1(ifstream &input) {
    string input_line;

    vector<string> grid;
    while (getline(input, input_line)) {
        grid.push_back(input_line);
    }

    vector<vector<bool>> visited(grid.size(), vector<bool>(grid[0].size()));
    unordered_map<char, vector<vector<int>>> trail_to_moves{
            {'.', {{1,  0}, {-1, 0}, {0, 1}, {0, -1}}},
            {'>', {{0,  1}}},
            {'<', {{0,  -1}}},
            {'v', {{1,  0}}},
            {'^', {{-1, 0}}} // fixme
    };

    pair<int, int> start{0, 1};
    pair<int, int> stop{(int) grid.size() - 1, (int) grid[0].size() - 2};

    cout << grid[start.first][start.second] << endl;
    cout << grid[stop.first][stop.second] << endl;

    visited[start.first][start.second] = true;

    int ans = dfs(grid, start, trail_to_moves, stop, visited);

    cout << ans << endl;
}


void part2(ifstream &input) {

    string input_line;

    vector<string> grid;
    while (getline(input, input_line)) {
        grid.push_back(input_line);
    }

    vector<vector<bool>> visited(grid.size(), vector<bool>(grid[0].size()));
    unordered_map<char, vector<vector<int>>> trail_to_moves{
            {'.', {{1, 0}, {-1, 0}, {0, 1}, {0, -1}}},
            {'>', {{1, 0}, {-1, 0}, {0, 1}, {0, -1}}},
            {'<', {{1, 0}, {-1, 0}, {0, 1}, {0, -1}}},
            {'v', {{1, 0}, {-1, 0}, {0, 1}, {0, -1}}},
            {'^', {{1, 0}, {-1, 0}, {0, 1}, {0, -1}}} // fixme
    };

    pair<int, int> start{0, 1};
    pair<int, int> stop{(int) grid.size() - 1, (int) grid[0].size() - 2};

    cout << grid[start.first][start.second] << endl;
    cout << grid[stop.first][stop.second] << endl;

    visited[start.first][start.second] = true;

    int ans = dfs(grid, start, trail_to_moves, stop, visited);

    cout << ans << endl;
}

int main() {
    ifstream input("/home/leartsura/Documents/projects/aoc23/input");
    if (input.fail()) {
        cout << "cant open input file" << endl;
        exit(0);
    }

//    part1(input);
    part2(input);
//
    input.close();
}

