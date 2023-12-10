#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <deque>
#include <numeric>
#include "utils_aoc.h"

using namespace std;

//
//int get_size_loop(const pair<int, int> &start, const vector<string> &grid,
//                  unordered_map<char, vector<vector<int>>> &sign_to_moves, int half = -1) {
//    int loop_size = 0;
//    int start_visits = 0;
//    pair<int, int> curr = start;
//    pair<int, int> prev = {-1, -1};
//    while (loop_size < 1000) {
//        if (curr.first == start.first && curr.second == start.second) {
//            start_visits++;
//            if (start_visits > 1) {
//                cout << "starts" << start_visits << endl;
//                break;
//            }
//        }
//        loop_size++;
////        if (loop_size == half) {
////            break;
////        }
//
//        auto moves = sign_to_moves[grid[curr.first][curr.second]];
//        for (const auto &move: moves) {
//            int row = curr.first + move[0];
//            int col = curr.second + move[1];
//            if (row < 0 || col < 0 || row >= grid.size() || col >= grid[0].size()) {
//                cout << "err: " << row << " " << col << endl;
//                return 0;
//            }
//            if (pair<int, int>{row, col} != prev) {
//                prev = curr;
//                curr = {row, col};
//                break;
//            }
//        }
//        cout << "curr: " << curr.first << " " << curr.second << " " << grid[curr.first][curr.second] << endl;
//
//    }
//}

void part1(ifstream &input) {
    string line;
    vector<string> grid;
    while (getline(input, line)) {
        grid.push_back(line);
    }

    pair<int, int> start;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid.size(); j++) {
            if (grid[i][j] == 'S') {
                start = {i, j};
                break;
            }
        }
    }

    unordered_map<char, vector<vector<int>>> sign_to_moves{
            {'|', {{-1, 0},  {1, 0}}},
            {'-', {{0,  -1}, {0, 1}}},
            {'L', {{-1, 0},  {0, 1}}},
            {'J', {{-1, 0},  {0, -1}}},
            {'7', {{0,  -1}, {1, 0}}},
            {'F', {{1,  0},  {0, 1}}},
            {'.', {}}
    };

    long long ans = 0;


    char start_sign = '|'; // fixme
    grid[start.first][start.second] = start_sign;
    cout << start.first << " " << start.second << " " << start_sign << endl;

    // get size of loop
//    int loop_size = get_size_loop(start, grid, sign_to_moves);

    int loop_size = 0;
    int start_visits = 0;
    pair<int, int> curr = start;
    pair<int, int> prev = {-1, -1};
    while (true) {
        if (curr.first == start.first && curr.second == start.second) {
            start_visits++;
            if (start_visits > 1) {
                cout << "starts" << start_visits << endl;
                break;
            }
        }
        loop_size++;
//        if (loop_size == half) {
//            break;
//        }

        auto moves = sign_to_moves[grid[curr.first][curr.second]];
        for (const auto &move: moves) {
            int row = curr.first + move[0];
            int col = curr.second + move[1];
            if (row < 0 || col < 0 || row >= grid.size() || col >= grid[0].size()) {
                cout << "err: " << row << " " << col << endl;
                return;
            }
            if (pair<int, int>{row, col} != prev) {
                prev = curr;
                curr = {row, col};
                break;
            }
        }
        cout << "curr: " << curr.first << " " << curr.second << " " << grid[curr.first][curr.second] << endl;

    }

    cout << "loop_size: " << loop_size << endl;

    int half = loop_size / 2;
    if (loop_size % 2 == 1) {
        half++;
    }
    cout << "half: " << half << endl;
}

void part2(ifstream &input) {
    string line;
    vector<string> grid;
    while (getline(input, line)) {
        grid.push_back(line);
    }

    pair<int, int> start = {-1, -1};
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            if (grid[i][j] == 'S') {
                start = {i, j};
                break;
            }
        }
    }
    if (start.first < 0) {
        cout << " err: " << start.first << " " << start.second << endl;
        return;
    }

    unordered_map<char, vector<vector<int>>> sign_to_moves{
            {'|', {{-1, 0},  {1, 0}}},
            {'-', {{0,  -1}, {0, 1}}},
            {'L', {{-1, 0},  {0, 1}}},
            {'J', {{-1, 0},  {0, -1}}},
            {'7', {{0,  -1}, {1, 0}}},
            {'F', {{1,  0},  {0, 1}}},
            {'.', {{-1, 0},  {1, 0}, {0, -1}, {0, 1}}}
    };

    long long ans = 0;


    char start_sign = '|'; // fixme
    grid[start.first][start.second] = start_sign;
    cout << start.first << " " << start.second << " " << start_sign << endl;

    // mark pipe
    vector<vector<bool>> pipes(grid.size(), vector<bool>(grid[0].size()));
    int loop_size = 0;
    int start_visits = 0;
    pair<int, int> curr = start;
    pair<int, int> prev = {-1, -1};
    while (true) {
        if (curr.first == start.first && curr.second == start.second) {
            start_visits++;
            if (start_visits > 1) {
                cout << "starts" << start_visits << endl;
                break;
            }
        }
        loop_size++;

        auto moves = sign_to_moves[grid[curr.first][curr.second]];
        for (const auto &move: moves) {
            int row = curr.first + move[0];
            int col = curr.second + move[1];
            if (row < 0 || col < 0 || row >= grid.size() || col >= grid[0].size()) {
                cout << "err: " << row << " " << col << endl;
                return;
            }
            if (pair<int, int>{row, col} != prev) {
                prev = curr;
                curr = {row, col};
                pipes[row][col] = true;
                break;
            }
        }
//        cout << "curr: " << curr.first << " " << curr.second << " " << grid[curr.first][curr.second] << endl;

    }
    cout << "loop_size: " << loop_size << endl;


    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            if (!pipes[i][j]) {
                grid[i][j] = '.';
            }
            if (grid[i][j] == '7' || grid[i][j] == 'F') {
//            if (grid[i][j] != '.' && grid[i][j] != '|' && grid[i][j] != '-') {
                grid[i][j] = '|';
            }
        }
    }

    int counter = 0;
    for (int i = 0; i < grid.size(); i++) {
        int pipe_count = 0;
        for (int j = 0; j < grid[0].size(); j++) {
            if (grid[i][j] == '|') {
                pipe_count++;
            } else if (grid[i][j] == '.') {
                if (pipe_count % 2 == 1) {
                    cout << i << " " << j << endl;
                    counter++;
                }
            }
        }
    }


    int grid_total_size = grid.size() * grid[0].size();
    cout << "total: " << grid_total_size << endl;
    cout << "counter: " << counter << endl;
//    cout << "enclosed: " << grid_total_size - counter << endl;
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
