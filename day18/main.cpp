#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <deque>
#include <numeric>
#include <sstream>
#include "utils_aoc.h"

using namespace std;

struct digger {
    char dir;
    int size;
    string color;
};

int fill(vector<string> &grid, const unordered_map<char, vector<int>> &moves, pair<int, int> start) {
    vector<vector<bool>> visited(grid.size(), vector<bool>(grid[0].size()));
    int lagoon_size = 1;
    visited[start.first][start.second] = true;
    grid[start.first][start.second] = '#';
    queue<pair<int, int>> que;
    que.push(start);

    while (!que.empty()) {
        auto curr = que.front();
        que.pop();

        for (auto [dir, move]: moves) {
            int row = curr.first + move[0];
            int col = curr.second + move[1];

            if (row >= 0 && col >= 0 && row < grid.size() && col < grid[0].size() && !visited[row][col] &&
                grid[row][col] == '.') {
                grid[row][col] = '#';
                visited[row][col] = true;
                lagoon_size++;
                que.emplace(row, col);
            }
        }
    }

    return lagoon_size;
}

void part1(ifstream &input) {
    string input_line;
    vector<digger> plan;
    while (getline(input, input_line)) {
        auto splitted = split(input_line, " ");
        char dir = input_line[0];
        int size = stoi(input_line.substr(2));
        string color = splitted[2];

        cout << dir << " " << size << " " << color << endl;
        plan.push_back({dir, size, color});
    }


    int grid_size = 1000;
    vector<string> grid(grid_size, string(grid_size, '.'));
    pair<int, int> curr{grid.size() / 2, grid.size() / 2};
    grid[curr.first][curr.second] = '#';

//    for (const auto &row: grid) {
//        cout << row << endl;
//    }

    unordered_map<char, vector<int>> moves{
            {'R', {0,  1}},
            {'L', {0,  -1}},
            {'U', {-1, 0}},
            {'D', {1,  0}}
    };

    int min_row = grid_size;
    int max_row = 0;
    int min_col = grid_size;
    int max_col = 0;

    int border_size = 0;
    for (const auto &dig: plan) {
        for (int i = 0; i < dig.size; ++i) {
            border_size++;
            curr.first += moves[dig.dir][0];
            curr.second += moves[dig.dir][1];
//            cout << curr.first << " " << curr.second << endl;
            min_row = min(min_row, curr.first);
            max_row = max(max_row, curr.first);
            min_col = min(min_col, curr.second);
            max_col = max(max_col, curr.second);

            if (curr.first >= grid_size || curr.first < 0 || curr.second >= grid_size || curr.second < 0) {
                cout << curr.first << " " << curr.second << endl;
                cout << "out of board! break" << endl;
                break;
            }
            if (grid[curr.first][curr.second] == '#') {
                cout << curr.first << " " << curr.second << endl;
                cout << "digged!" << endl;
            }
            grid[curr.first][curr.second] = '#';
        }
    }
    cout << "border: " << border_size << endl;
    cout << endl;

    cout << min_row << " " << max_row << endl;
    cout << min_col << " " << max_col << endl;

    for (int i = min_row; i <= max_row; i++) {
        for (int j = min_col; j <= max_col; j++) {
            cout << grid[i][j];
        }
        cout << endl;
    }

    int lagoon_size = border_size;
    lagoon_size += fill(grid, moves, {curr.first + 1, curr.second + 1});

    cout << endl;
    for (int i = min_row; i <= max_row; i++) {
        for (int j = min_col; j <= max_col; j++) {
            cout << grid[i][j];
        }
        cout << endl;
    }

//    int ans = 0;
    cout << lagoon_size << endl;
}


void part2(ifstream &input) {
    string input_line;
    vector<digger> plan;
    while (getline(input, input_line)) {
        auto splitted = split(input_line, "#");

        string hex = splitted[1].substr(0, 5);
        int size;
        std::stringstream ss;
        ss << std::hex << hex;
        ss >> size;

        char dir = splitted[1][5];

        cout << dir << " " << size << " " << "" << endl;
        plan.push_back({dir, size, ""});
    }

    unordered_map<char, vector<int>> moves{
            {'0', {0,  1}},
            {'2', {0,  -1}},
            {'3', {1,  0}},
            {'1', {-1, 0}}
    };

    vector<pair<long long, long long>> points;
    pair<long long, long long> curr{0, 0};
    points.push_back(curr);
    long long perimeter = 0;
    for (const auto &dig: plan) {
        curr.first += moves[dig.dir][0] * dig.size;
        curr.second += moves[dig.dir][1] * dig.size;
        perimeter += dig.size;
        points.push_back(curr);
    }
    cout << "perimeter: " << perimeter << endl;

    long long picks_area = 0;
    for (int i = 0; i + 1 < points.size(); i++) {

        if (points[i].first != points[i + 1].first && points[i].second != points[i + 1].second) {
            cout << "failed!" << endl;
        }

        long long area = points[i].first * (points[i + 1].second - points[i].second);

//        cout << "(" << points[i].first << "," << points[i].second << ") " << "(" << points[i + 1].first << ","
//             << points[i + 1].second << ") " << area << endl;
        picks_area += area;
    }

    cout << picks_area + perimeter / 2 + 1 << endl;

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

