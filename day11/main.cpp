#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <deque>
#include <numeric>
#include "utils_aoc.h"

using namespace std;

long long manhattan_distance(pair<int, int> start, pair<int, int> stop, const unordered_set<int> &empty_rows,
                             const unordered_set<int> &empty_cols) {
    long long dist = abs(start.first - stop.first) + abs(start.second - stop.second);
    long long expansion = 0;
    for (int i: empty_rows) {
        if (i >= min(start.first, stop.first) && i <= max(start.first, stop.first)) {

        }
    }
    return 0;
}

long long get_shortest_path(pair<int, int> start, pair<int, int> stop, const vector<string> &grid,
                            const unordered_set<int> &empty_rows,
                            const unordered_set<int> &empty_cols, long long expanse = 1) {
    vector<vector<int>> moves{
            {-1, 0},
            {1,  0},
            {0,  1},
            {0,  -1}
    };
    queue<pair<int, int>> que;
    vector<vector<long long>> dist(grid.size(), vector<long long>(grid[0].size(), -1));
    que.push(start);
    dist[start.first][start.second] = 0;

    while (!que.empty()) {
        auto curr = que.front();
        que.pop();

        int i = curr.first;
        int j = curr.second;

        if (curr == stop) {
            break;
        }

        for (const auto &move: moves) {
            int row = i + move[0];
            int col = j + move[1];

            if (row >= 0 && col >= 0 && row < grid.size() && col < grid[row].size() && dist[row][col] == -1) {
                dist[row][col] = dist[i][j] + 1;
                if (row != i && empty_rows.contains(i)) {
                    dist[row][col] += expanse;
                }
                if (col != j && empty_cols.contains(j)) {
                    dist[row][col] += expanse;
                }
                que.emplace(row, col);
            }

        }
    }

    return dist[stop.first][stop.second];

}

void part1(ifstream &input) {
    string line;
    vector<string> grid;
    vector<pair<int, int>> galaxies;
    unordered_set<int> empty_rows;
    while (getline(input, line)) {
        grid.push_back(line);

        bool f = false;
        for (int j = 0; j < grid.back().size(); j++) {
            if (grid.back()[j] == '#') {
                f = true;
                galaxies.emplace_back(grid.size() - 1, j);
            }
        }
        if (!f) {
            empty_rows.insert(grid.size() - 1);
        }
    }


    unordered_set<int> empty_cols;
    for (int j = 0; j < grid[0].size(); j++) {
        bool f = false;
        for (int i = 0; i < grid.size(); i++) {
            if (grid[i][j] == '#') {
                f = true;
            }
        }
        if (!f) {
            empty_cols.insert(j);
        }
    }


    long long ans = 0;
    int g_count = galaxies.size();
    cout << "galaxies: " << g_count << endl;
    cout << "galaxies: " << g_count * (g_count - 1) / 2 << endl;
    cout << "empty_rows: " << empty_rows.size() << endl;
    cout << "empty_cols: " << empty_cols.size() << endl;

    for (int i = 0; i < galaxies.size(); i++) {
        for (int j = i + 1; j < galaxies.size(); j++) {
            auto start = galaxies[i];
            auto stop = galaxies[j];
//            cout << "start: " << start.first << " " << start.second << endl;
//            cout << "stop: " << stop.first << " " << stop.second << endl;

            int sp = get_shortest_path(start, stop, grid, empty_rows, empty_cols);
            ans += sp;
//            cout << "shortest path: " << sp << endl;

        }
    }

    cout << ans << endl;
}

void part2(ifstream &input) {
    string line;
    vector<string> grid;
    vector<pair<int, int>> galaxies;
    unordered_set<int> empty_rows;
    while (getline(input, line)) {
        grid.push_back(line);

        bool f = false;
        for (int j = 0; j < grid.back().size(); j++) {
            if (grid.back()[j] == '#') {
                f = true;
                galaxies.emplace_back(grid.size() - 1, j);
            }
        }
        if (!f) {
            empty_rows.insert(grid.size() - 1);
        }
    }


    unordered_set<int> empty_cols;
    for (int j = 0; j < grid[0].size(); j++) {
        bool f = false;
        for (int i = 0; i < grid.size(); i++) {
            if (grid[i][j] == '#') {
                f = true;
            }
        }
        if (!f) {
            empty_cols.insert(j);
        }
    }


    long long ans = 0;
    int g_count = galaxies.size();
    cout << "galaxies: " << g_count << endl;
    cout << "galaxies: " << g_count * (g_count - 1) / 2 << endl;
    cout << "empty_rows: " << empty_rows.size() << endl;
    cout << "empty_cols: " << empty_cols.size() << endl;

    for (int i = 0; i < galaxies.size(); i++) {
        for (int j = i + 1; j < galaxies.size(); j++) {
            auto start = galaxies[i];
            auto stop = galaxies[j];

            ans += get_shortest_path(start, stop, grid, empty_rows, empty_cols, 1000000 - 1);

        }
    }

    cout << ans << endl;
}

int main() {
    ifstream input("/home/leartsura/Documents/projects/aoc23/input");
    if (input.fail()) {
        cout << "cant open input file" << endl;
        exit(0);
    }
    part1(input);
//    part2(input);

    input.close();
}
