#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <deque>
#include <numeric>
#include <sstream>
#include "utils_aoc.h"

using namespace std;

void part1(ifstream &input) {
    string input_line;

    pair<int, int> start;
    vector<string> grid;
    while (getline(input, input_line)) {
        grid.push_back(input_line);
        for (int i = 0; i < grid.back().size(); ++i) {
            if (grid.back()[i] == 'S') {
                start = {(int) grid.size() - 1, i};
            }
        }
        cout << grid.back() << endl;
    }

    cout << start.first << " " << start.second << " " << grid[start.first][start.second] << endl;

    vector<vector<int>> moves{
            {1,  0},
            {-1, 0},
            {0,  1},
            {0,  -1}
    };

    int steps = 64; //fixme
    set<pair<int, int>> que;
    que.insert(start);
    for (int step = 0; step < steps; ++step) {
        set<pair<int, int>> next_que;

        for (auto [i, j]: que) {
            for (auto move: moves) {
                int row = i + move[0];
                int col = j + move[1];

                if (row >= 0 && col >= 0 && row < grid.size() && col < grid[0].size() && grid[row][col] != '#') {
                    next_que.insert({row, col});
                }
            }
        }

        que = next_que;
    }

    cout << que.size() << endl;


//    long long ans = 0;
//    cout << ans << endl;
}

long long modulo(long long n, long long m) {
    return (n % m + m) % m;
}

int garden_plots(int steps, pair<int, int> start, const vector<vector<int>> &moves, vector<string> grid) {
    set<pair<int, int>> que;
    que.insert(start);
    for (int step = 0; step < steps; ++step) {
        set<pair<int, int>> next_que;

        for (auto [i, j]: que) {
            for (auto move: moves) {
                int row = i + move[0];
                int rowmod = modulo(i + move[0], grid.size());
                int col = j + move[1];
                int colmod = modulo(j + move[1], grid[0].size());

                if (grid[rowmod][colmod] != '#') {
                    next_que.insert({row, col});
                }
            }
        }

        que = next_que;
//        cout << "{"<<step+1 << ", " << que.size()<<"}, ";
    }

    return que.size();
}

void part2(ifstream &input) {
    string input_line;

    pair<int, int> start;
    vector<string> grid;
    while (getline(input, input_line)) {
        grid.push_back(input_line);
        for (int i = 0; i < grid.back().size(); ++i) {
            if (grid.back()[i] == 'S') {
                start = {(int) grid.size() - 1, i};
            }
        }
//        cout << grid.back() << endl;
    }

    cout << start.first << " " << start.second << " " << grid[start.first][start.second] << endl;

    vector<vector<int>> moves{
            {1,  0},
            {-1, 0},
            {0,  1},
            {0,  -1}
    };

//    for (int i = 6; i < 500; i++) {
    int ans = garden_plots(0, start, moves, grid);
//    int ans = garden_plots(1, start, moves, grid);
//    int ans = garden_plots(2, start, moves, grid);
    cout << garden_plots(65, start, moves, grid)<<endl;
    cout << garden_plots(65+131, start, moves, grid)<<endl;
    cout << garden_plots(65+2*131, start, moves, grid)<<endl;
//    }
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

