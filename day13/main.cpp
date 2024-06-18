#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <deque>
#include <numeric>
#include "utils_aoc.h"

using namespace std;

int diff(string a, string b) {
    int counter = 0;
    for (int i = 0; i < a.size(); i++) {
        if (a[i] != b[i]) {
            counter++;
        }
    }
    return counter;
}

int reflection_idx(const vector<string> &grid, int smudges = 0) {
    for (int i = 0; i + 1 < grid.size(); i++) {
        int diff_count = 0;
        int j = 0;
        for (; i + 1 + j < grid.size() && i - j >= 0; j++) {
            // diff
            diff_count += diff(grid[i - j], grid[i + 1 + j]);
        }

        if (diff_count == smudges) {
            return i + 1;
        }
    }

    return 0;
}

vector<string> transpose(const vector<string> &grid) {
    vector<string> rotated_grid;
    for (int j = 0; j < grid[0].size(); ++j) {
        rotated_grid.emplace_back();
        for (int i = 0; i < grid.size(); ++i) {
            rotated_grid.back() += grid[i][j];
        }
    }
    return rotated_grid;
}

void part1(ifstream &input) {
    string line;
    vector<vector<string>> grids;
    grids.emplace_back();
    while (getline(input, line)) {
        if (line.empty()) {
            grids.emplace_back();
        } else {
            grids.back().push_back(line);
        }
    }

    int ans = 0;
    for (const auto &grid: grids) {
        int horizontal_line = reflection_idx(grid);

        if (horizontal_line) {
            ans += 100 * horizontal_line;
            continue;
        }
        vector<string> rotated_grid = transpose(grid);

        int vertical_line = reflection_idx(rotated_grid);
        ans += vertical_line;
    }

    cout << ans << endl;


}

void part2(ifstream &input) {
    string line;
    vector<vector<string>> grids;
    grids.emplace_back();
    while (getline(input, line)) {
        if (line.empty()) {
            grids.emplace_back();
        } else {
            grids.back().push_back(line);
        }
    }

    int ans = 0;
    for (const auto &grid: grids) {
        int horizontal_line = reflection_idx(grid, 1);

        if (horizontal_line) {
            ans += 100 * horizontal_line;
            continue;
        }
        vector<string> rotated_grid = transpose(grid);

        int vertical_line = reflection_idx(rotated_grid, 1);
        ans += vertical_line;
    }

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

    input.close();
}
