#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <deque>
#include <numeric>
#include "utils_aoc.h"

using namespace std;


struct beam {
    int i;
    int j;
    char dir;
};

bool in_grid(int row, int col, const vector<string> &grid) {
    return row >= 0 && col >= 0 && row < grid.size() && col < grid[0].size();
}

bool is_visited(beam curr, int row, int col, const vector<vector<vector<bool>>> &visited) {
    return visited[curr.dir][row][col];
}

void part1(ifstream &input) {
    string line;
    vector<string> grid;
    while (getline(input, line)) {
        grid.push_back(line);
    }

//    unordered_map<char, unordered_map<char, vector<vector<int>>>> moves;
//    moves.insert({'.', {{'R', {{0, 1}}}}});
//    moves.insert({'.', {{'L', {{0, -1}}}}});
//    moves.insert({'.', {{'U', {{-1, 0}}}}});
//    moves.insert({'.', {{'D', {{1, 0}}}}});
//    moves.insert({'|', {{'R', {{0, -1}, {0, 1}}}}});
//    moves.insert({'|', {{'L', {{0, -1}, {0, 1}}}}});
//    moves.insert({'|', {{'U', {}}}});
//    moves.insert({'|', {{'D', {}}}});
//    moves.insert({'-', {{'R', {}}}});
//    moves.insert({'-', {{'L', {}}}});
//    moves.insert({'-', {{'U', {{0, -1}, {0, 1}}}}});
//    moves.insert({'-', {{'D', {{0, -1}, {0, 1}}}}});
//    moves.insert({'/', {{'R', {{-1, 0}}}}});
//    moves.insert({'/', {{'L', {{-1, 0}}}}});
//    moves.insert({'/', {{'L', {{-1, 0}}}}});

    unordered_map<char, vector<vector<int>>> moves{
            {'R', {{0,  1}}},
            {'L', {{0,  -1}}},
            {'U', {{-1, 0}}},
            {'D', {{1,  0}}},
            {'|', {{-1, 0},  {1, 0}}},
            {'-', {{0,  -1}, {0, 1}}}
    };
//            {'|',  {}},
//            {'-',  {}},
//            {'/',  {}},
//            {'\\', {}}



// R D L U
    vector<vector<vector<bool>>> visited(256, vector<vector<bool>>(grid.size(), vector<bool>(grid[0].size())));

    beam start{0, 0, 'R'};
    queue<beam> bfs;
    bfs.push(start);
    visited[start.dir][start.i][start.j] = true;

    while (!bfs.empty()) {
        beam curr = bfs.front();
        cout << curr.i << " " << curr.j << endl;
        bfs.pop();

        char tile = grid[curr.i][curr.j];
        if (tile == '.' ||
            tile == '|' && (curr.dir == 'U' || curr.dir == 'D') ||
            tile == '-' && (curr.dir == 'L' || curr.dir == 'R')) {
            int row = curr.i + moves[curr.dir][0][0];
            int col = curr.j + moves[curr.dir][0][1];
            char dir = curr.dir;
            if (in_grid(row, col, grid) && !visited[dir][row][col]) {
                visited[dir][row][col] = true;
                bfs.push({row, col, dir});
            }
        } else if (tile == '|' || tile == '-') {
            for (auto move: moves[tile]) {
                int row = curr.i + move[0];
                int col = curr.j + move[1];
                char dir;
                if (row == curr.i - 1) {
                    dir = 'U';
                } else if (row == curr.i + 1) {
                    dir = 'D';
                } else if (col == curr.j - 1) {
                    dir = 'L';
                } else {
                    dir = 'R';
                }


                if (in_grid(row, col, grid) && !visited[dir][row][col]) {
                    visited[dir][row][col] = true;
                    bfs.push({row, col, dir});
                }
            }
        } else if (tile == '/') {
            int row = curr.i;
            int col = curr.j;
            char dir;
            if (curr.dir == 'R') {
                row--;
                dir = 'U';
            } else if (curr.dir == 'L') {
                row++;
                dir = 'D';
            } else if (curr.dir == 'U') {
                col++;
                dir = 'R';
            } else {
                col--;
                dir = 'L';
            }
            if (in_grid(row, col, grid) && !visited[dir][row][col]) {
                visited[dir][row][col] = true;
                bfs.push({row, col, dir});
            }
        } else if (tile == '\\') {
            int row = curr.i;
            int col = curr.j;
            char dir;
            if (curr.dir == 'R') {
                row++;
                dir = 'D';
            } else if (curr.dir == 'L') {
                row--;
                dir = 'U';
            } else if (curr.dir == 'U') {
                col--;
                dir = 'L';
            } else {
                col++;
                dir = 'R';
            }
            if (in_grid(row, col, grid) && !visited[dir][row][col]) {
                visited[dir][row][col] = true;
                bfs.push({row, col, dir});
            }
        }

    }
    // 9 5

    int ans = 0;
    cout << endl;
    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[0].size(); ++j) {
            if (visited['L'][i][j] || visited['R'][i][j] || visited['U'][i][j] || visited['D'][i][j]) {
                ans++;
                cout << '#';
            } else {
                cout << '.';
            }
        }
        cout << endl;
    }


    cout << ans << endl;
}


int count_energised(beam start, const vector<string> &grid) {
    unordered_map<char, vector<vector<int>>> moves{
            {'R', {{0,  1}}},
            {'L', {{0,  -1}}},
            {'U', {{-1, 0}}},
            {'D', {{1,  0}}},
            {'|', {{-1, 0},  {1, 0}}},
            {'-', {{0,  -1}, {0, 1}}}
    };
//            {'|',  {}},
//            {'-',  {}},
//            {'/',  {}},
//            {'\\', {}}



// R D L U
    vector<vector<vector<bool>>> visited(256, vector<vector<bool>>(grid.size(), vector<bool>(grid[0].size())));

    queue<beam> bfs;
    bfs.push(start);
    visited[start.dir][start.i][start.j] = true;

    while (!bfs.empty()) {
        beam curr = bfs.front();
//        cout << curr.i << " " << curr.j << endl;
        bfs.pop();

        char tile = grid[curr.i][curr.j];
        if (tile == '.' ||
            tile == '|' && (curr.dir == 'U' || curr.dir == 'D') ||
            tile == '-' && (curr.dir == 'L' || curr.dir == 'R')) {
            int row = curr.i + moves[curr.dir][0][0];
            int col = curr.j + moves[curr.dir][0][1];
            char dir = curr.dir;
            if (in_grid(row, col, grid) && !visited[dir][row][col]) {
                visited[dir][row][col] = true;
                bfs.push({row, col, dir});
            }
        } else if (tile == '|' || tile == '-') {
            for (auto move: moves[tile]) {
                int row = curr.i + move[0];
                int col = curr.j + move[1];
                char dir;
                if (row == curr.i - 1) {
                    dir = 'U';
                } else if (row == curr.i + 1) {
                    dir = 'D';
                } else if (col == curr.j - 1) {
                    dir = 'L';
                } else {
                    dir = 'R';
                }


                if (in_grid(row, col, grid) && !visited[dir][row][col]) {
                    visited[dir][row][col] = true;
                    bfs.push({row, col, dir});
                }
            }
        } else if (tile == '/') {
            int row = curr.i;
            int col = curr.j;
            char dir;
            if (curr.dir == 'R') {
                row--;
                dir = 'U';
            } else if (curr.dir == 'L') {
                row++;
                dir = 'D';
            } else if (curr.dir == 'U') {
                col++;
                dir = 'R';
            } else {
                col--;
                dir = 'L';
            }
            if (in_grid(row, col, grid) && !visited[dir][row][col]) {
                visited[dir][row][col] = true;
                bfs.push({row, col, dir});
            }
        } else if (tile == '\\') {
            int row = curr.i;
            int col = curr.j;
            char dir;
            if (curr.dir == 'R') {
                row++;
                dir = 'D';
            } else if (curr.dir == 'L') {
                row--;
                dir = 'U';
            } else if (curr.dir == 'U') {
                col--;
                dir = 'L';
            } else {
                col++;
                dir = 'R';
            }
            if (in_grid(row, col, grid) && !visited[dir][row][col]) {
                visited[dir][row][col] = true;
                bfs.push({row, col, dir});
            }
        }

    }

    int ans = 0;
//    cout << endl;
    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[0].size(); ++j) {
            if (visited['L'][i][j] || visited['R'][i][j] || visited['U'][i][j] || visited['D'][i][j]) {
                ans++;
//                cout << '#';
            } else {
//                cout << '.';
            }
        }
//        cout << endl;
    }

    return ans;
}

void part2(ifstream &input) {
    string line;
    vector<string> grid;
    while (getline(input, line)) {
        grid.push_back(line);
    }

    cout << count_energised({0, 0, 'R'}, grid) << endl;

    vector<beam> starts;
    for (int i = 0; i < grid.size(); ++i) {
        starts.push_back({i, 0, 'R'});
        starts.push_back({i, (int) grid[0].size() - 1, 'L'});
    }
    for (int j = 0; j < grid[0].size(); ++j) {
        starts.push_back({0, j, 'D'});
        starts.push_back({(int) grid.size() - 1, j, 'U'});
    }

    int maxi = 0;
    for (auto start: starts) {
        int energised = count_energised(start, grid);
        cout << energised << endl;
        maxi = max(maxi, energised);
    }

    cout << maxi << endl;
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
