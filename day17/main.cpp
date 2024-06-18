#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <deque>
#include <numeric>
#include "utils_aoc.h"

using namespace std;

struct crucible {
    int i;
    int j;
    char dir;
    int line;
    int loss;
};

bool in_grid(int i, int j, const vector<string> &grid) {
    return i >= 0 && j >= 0 && i < grid.size() && j < grid[0].size();
}

bool is_turnaround(char prev_dir, char dir) {
    if (prev_dir == 'L') return dir == 'R';
    if (prev_dir == 'R') return dir == 'L';
    if (prev_dir == 'U') return dir == 'D';
    if (prev_dir == 'D') return dir == 'U';
}

void part1(ifstream &input) {
    string input_line;
    vector<string> grid;
    while (getline(input, input_line)) {
        grid.push_back(input_line);
//        cout << grid.back() << endl;
    }

    unordered_map<char, vector<int>> moves{
            {'R', {{0,  1}}},
            {'L', {{0,  -1}}},
            {'U', {{-1, 0}}},
            {'D', {{1,  0}}}
    };

    vector<vector<vector<vector<int>>>> heat_loss(
            grid.size(), vector<vector<vector<int>>>(
                    grid[0].size(), vector<vector<int>>(
                            256, vector<int>(
                                    4, INT_MAX))));

//    auto comp = [](crucible &a, crucible &b) -> bool { return a.loss < b.loss; };
    priority_queue<crucible, vector<crucible>,
            decltype([](crucible &lhs, crucible &rhs) -> bool { return lhs.loss > rhs.loss; })> pque;

    for (auto &[dir, move]: moves) {
        pque.push({0, 0, dir, 1, 0});
        heat_loss[0][0][dir][1] = 0;
    }
//    crucible start{0, 0, 'R', 1, 0};


    while (!pque.empty()) {
        crucible curr = pque.top();
        pque.pop();
//        cout << curr.i << " " << curr.j << " " << curr.dir << " " << curr.line << " " << curr.loss << endl;
//        heat_loss[curr.i][curr.j][curr.dir][curr.line] = curr.loss;
//        pque.pop();

        for (const auto &[dir, move]: moves) {
            int row = curr.i + move[0];
            int col = curr.j + move[1];
            int line = curr.line + 1;
            if (curr.dir != dir) {
                line = 1;
            }

            if (in_grid(row, col, grid) && !is_turnaround(curr.dir, dir) && line <= 3) {
                int loss = curr.loss + grid[row][col] - '0';
//                int loss = heat_loss[curr.i][curr.j][curr.dir][curr.line] + (grid[row][col] - '0');
                if (heat_loss[row][col][dir][line] > loss) {
                    heat_loss[row][col][dir][line] = loss;
//                    cout << row << " " << col << " " << loss << endl;
                    pque.push({row, col, dir, line, loss});
                }
            }
        }
    }



//    int n = grid.size();
//    int m = grid[0].size();
//    cout << grid.size() << endl;
//    cout << grid[0].size() << endl;
    int min_loss = INT_MAX;
    for (auto [d, move]: moves) {
        for (int i = 1; i <= 3; i++) {
            min_loss = min(heat_loss[(int) grid.size() - 1][(int) grid[0].size() - 1][d][i], min_loss);
        }
    }

    // 1133 - too low
    // 1138 - ans
    cout << min_loss << endl;
//    cout << INT_MAX << endl;
}

#include <bits/stdc++.h>

using namespace std;
#define F0R(i, a) for (int i=0; i<(a); i++)
#define all(x) x.begin(), x.end()

template<class T>
bool ckmin(T &a, const T &b) { return b < a ? a = b, 1 : 0; }

const int dx[] = {0, 1, 0, -1};
const int dy[] = {1, 0, -1, 0};
using VI = vector<int>;
using VVI = vector<VI>;
using VVVI = vector<VVI>;
using VVVVI = vector<VVVI>;

void sol2(const vector<string> &grid) {
    int N = grid.size(), M = grid[0].size();

    auto dijkstra = [&]() -> VVVVI {
        const int INF = 2e9;
        VVVVI dist(N, VVVI(M, VVI(4, VI(11, INF))));

        using T = array<int, 4>;
        priority_queue<pair<int, T>, vector<pair<int, T>>, greater<pair<int, T>>> pq;
        F0R(d, 4) {
            dist[0][0][d][0] = 0;
            pq.push({0, {0, 0, d, 0}});
        }

        auto valid = [&](int x, int y) {
            return 0 <= x && x < N && 0 <= y && y < M;
        };

        auto getAdj = [&](int x, int y, int d, int s) -> vector<T> {
            vector<T> ret;

            unordered_map<int, vector<int>> moves{
                    {0, {{0,  1}}},
                    {2, {{0,  -1}}},
                    {3, {{-1, 0}}},
                    {1, {{1,  0}}}
            };
//            for (auto [dir, move]: moves) {
//                int row = x + move[0];
//                int col = y + move[1];
//                int line = s + 1;
//                if (d != dir) {
//                    line = 1;
//                }
//
//                if (in_grid(row, col, grid) && !is_prev(x, y, row, col) && line <= 3) {
//                    ret.push_back({row, col, d, line});
//                }
//            }
//            int d1 = (d + 3) % 4;
//            auto move1 = moves[d1];
//            int d2 = (d + 1) % 4;
//            auto move2 = moves[d2];
//            ret.push_back({x + move1[0], y + move1[1], d1, 1});
//            ret.push_back({x + move2[0], y + move2[1], d2, 1});
//            if (s < 3) {
//                ret.push_back({x + dx[d], y + dy[d], d, s + 1});
//            }
//

            if (s >= 4) {
                int d1 = (d + 3) % 4;
                ret.push_back({x + dx[d1], y + dy[d1], d1, 1});
            }
            if (s >= 4) {
                int d2 = (d + 1) % 4;
                ret.push_back({x + dx[d2], y + dy[d2], d2, 1});
            }
            if (s < 10)
                ret.push_back({x + dx[d], y + dy[d], d, s + 1});

//            ret.push_back({x + dx[d1], y + dy[d1], d1, 1});
//            int d2 = (d + 1) % 4;
//            ret.push_back({x + dx[d2], y + dy[d2], d2, 1});
//            if (s < 3)
//                ret.push_back({x + dx[d], y + dy[d], d, s + 1});

            return ret;
        };

        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            auto [x, y, dir, s] = u;
            if (d > dist[x][y][dir][s]) continue;
            for (auto [nx, ny, nd, ns]: getAdj(x, y, dir, s)) {
                if (!valid(nx, ny)) continue;
                int weight = grid[nx][ny] - '0';
                if (dist[nx][ny][nd][ns] > dist[x][y][dir][s] + weight) {
                    dist[nx][ny][nd][ns] = dist[x][y][dir][s] + weight;
                    pq.push({dist[nx][ny][nd][ns], {nx, ny, nd, ns}});
                }
            }
        }
        return dist;
    };

    auto dist = dijkstra();
    int ans = 2e9;
    F0R(d, 4) {
        for (int s = 0; s <= 10; s++) {
            ckmin(ans, dist[N - 1][M - 1][d][s]);
        }
    }
    cout << ans << endl;
}

void part2(ifstream &input) {
    string input_line;
    vector<string> grid;
    while (getline(input, input_line)) {
        grid.push_back(input_line);
//        cout << grid.back() << endl;
    }

    unordered_map<char, vector<int>> moves{
            {'R', {{0,  1}}},
            {'L', {{0,  -1}}},
            {'U', {{-1, 0}}},
            {'D', {{1,  0}}}
    };

    vector<vector<vector<vector<int>>>> heat_loss(
            grid.size(), vector<vector<vector<int>>>(
                    grid[0].size(), vector<vector<int>>(
                            256, vector<int>(
                                    11, INT_MAX))));

//    auto comp = [](crucible &a, crucible &b) -> bool { return a.loss < b.loss; };
    priority_queue<crucible, vector<crucible>,
            decltype([](crucible &lhs, crucible &rhs) -> bool { return lhs.loss > rhs.loss; })> pque;

    for (auto &[dir, move]: moves) {
        pque.push({0, 0, dir, 1, 0});
        heat_loss[0][0][dir][1] = 0;
    }
//    crucible start{0, 0, 'R', 1, 0};


    while (!pque.empty()) {
        crucible curr = pque.top();
        pque.pop();
//        cout << curr.i << " " << curr.j << " " << curr.dir << " " << curr.line << " " << curr.loss << endl;
//        heat_loss[curr.i][curr.j][curr.dir][curr.line] = curr.loss;
//        pque.pop();

        for (const auto &[dir, move]: moves) {
            int row = curr.i + move[0];
            int col = curr.j + move[1];
            if (curr.line < 4) {
                if (dir != curr.dir) continue;
            }
            int line = curr.line + 1;
            if (curr.dir != dir) {
                line = 1;
            }

            if (in_grid(row, col, grid) && !is_turnaround(curr.dir, dir) && line <= 10) {
                int loss = curr.loss + grid[row][col] - '0';
//                int loss = heat_loss[curr.i][curr.j][curr.dir][curr.line] + (grid[row][col] - '0');
                if (heat_loss[row][col][dir][line] > loss) {
                    heat_loss[row][col][dir][line] = loss;
//                    cout << row << " " << col << " " << loss << endl;
                    pque.push({row, col, dir, line, loss});
                }
            }
        }
    }

//    int n = grid.size();
//    int m = grid[0].size();
//    cout << grid.size() << endl;
//    cout << grid[0].size() << endl;
    int min_loss = INT_MAX;
    for (auto [d, move]: moves) {
        for (int i = 1; i <= 10; i++) {
            min_loss = min(heat_loss[(int) grid.size() - 1][(int) grid[0].size() - 1][d][i], min_loss);
        }
    }

    // 1310 - ans
    cout << min_loss << endl;
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

