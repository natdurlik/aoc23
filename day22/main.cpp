#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <deque>
#include <numeric>
#include <sstream>
#include "utils_aoc.h"

using namespace std;

struct coord {
    int x;
    int y;
    int z;

    bool operator<(const coord &rhs) const {
        if (this->z != rhs.z) return this->z < rhs.z;
        if (this->x != rhs.x) return this->x < rhs.x;
        return this->y < rhs.y;
    }
};

using brick = pair<coord, coord>;

map<int, vector<brick>> fall_down(map<int, vector<brick>> levels) {
    for (auto [level, bricks]: levels) {

    }
    return levels;
}


void part1(ifstream &input) {
    string input_line;

//    map<int, vector<brick>> levels;
    vector<brick> bricks;
    int n = 0;
    int m = 0;
    while (getline(input, input_line)) {
        auto ends = split(input_line, "~");
        auto end1 = stoi(split(ends[0], ","));
        auto end2 = stoi(split(ends[1], ","));
        coord c1{end1[0], end1[1], end1[2]};
        coord c2{end2[0], end2[1], end2[2]};
        if (c2 < c1) {
            swap(c1, c2);
        }
//        levels[min(c1.z, c2.z)].emplace_back(c1, c2);
        bricks.emplace_back(c1, c2);
        n = max(c2.x, n);
        m = max(c2.y, m);
    }
    sort(bricks.begin(), bricks.end());
    n++;
    m++;
    cout << n << " " << m << endl;

    for (const auto &brick: bricks) {
        cout << brick.first.x << " " << brick.first.y << " " << brick.first.z << " ~ ";
        cout << brick.second.x << " " << brick.second.y << " " << brick.second.z << endl;
    }

    vector<vector<pair<int, int>>> top_view(n, vector<pair<int, int>>(m, {0, -1})); // height, brick idx
    unordered_set<int> undisintegratable;
    for (int bidx = 0; bidx < bricks.size(); bidx++) {
        auto brick = bricks[bidx];
        int height = -1;
        unordered_set<int> brick_idxs;
        for (int i = brick.first.x; i <= brick.second.x; i++) {
            for (int j = brick.first.y; j <= brick.second.y; j++) {
                if (top_view[i][j].first >= height) {
                    if (top_view[i][j].first > height) {
                        brick_idxs.clear();
                        height = top_view[i][j].first;
                    }
                    if (top_view[i][j].second != -1) {
                        brick_idxs.insert(top_view[i][j].second);
                    }
                }
            }
        }

        if (brick_idxs.size() == 1) {
            undisintegratable.insert(*brick_idxs.begin());
            cout << (*brick_idxs.begin()) << endl;
        }


        height += abs(brick.first.z - brick.second.z) + 1;
        for (int i = brick.first.x; i <= brick.second.x; i++) {
            for (int j = brick.first.y; j <= brick.second.y; j++) {
                top_view[i][j].first = height;
                top_view[i][j].second = bidx;
            }
        }

//        cout << endl;
//        cout << height << endl;
//        for (int i = 0; i < top_view.size(); i++) {
//            for (int j = 0; j < top_view[0].size(); ++j) {
//                cout << top_view[i][j].first << " ";
//            }
//            cout << endl;
//        }

    }

    cout << endl;
    cout << bricks.size() << endl;
    cout << undisintegratable.size() << endl;
    cout << bricks.size() - undisintegratable.size() << endl;
}

int top_sort(int start, const vector<vector<int>> &adj, vector<int> inputs) {
    inputs[start] = 0;
    queue<int> que;
    que.push(start);

    int disintegrated = 0;
    while (!que.empty()) {
        int curr = que.front();
        que.pop();

        for (int next: adj[curr]) {
            inputs[next]--;
            if (inputs[next] == 0) {
                disintegrated++;
                que.push(next);
            }
        }
    }

    return disintegrated;
}

void part2(ifstream &input) {
    string input_line;

//    map<int, vector<brick>> levels;
    vector<brick> bricks;
    int n = 0;
    int m = 0;
    while (getline(input, input_line)) {
        auto ends = split(input_line, "~");
        auto end1 = stoi(split(ends[0], ","));
        auto end2 = stoi(split(ends[1], ","));
        coord c1{end1[0], end1[1], end1[2]};
        coord c2{end2[0], end2[1], end2[2]};
        if (c2 < c1) {
            swap(c1, c2);
        }
//        levels[min(c1.z, c2.z)].emplace_back(c1, c2);
        bricks.emplace_back(c1, c2);
        n = max(c2.x, n);
        m = max(c2.y, m);
    }
    sort(bricks.begin(), bricks.end());
    n++;
    m++;
    cout << n << " " << m << endl;

    for (const auto &brick: bricks) {
        cout << brick.first.x << " " << brick.first.y << " " << brick.first.z << " ~ ";
        cout << brick.second.x << " " << brick.second.y << " " << brick.second.z << endl;
    }

    vector<vector<pair<int, int>>> top_view(n, vector<pair<int, int>>(m, {0, -1})); // height, brick idx
    vector<vector<int>> adj(bricks.size());
    vector<int> inputs(bricks.size());

    for (int bidx = 0; bidx < bricks.size(); bidx++) {
        auto brick = bricks[bidx];
        int height = -1;
        unordered_set<int> brick_idxs;
        for (int i = brick.first.x; i <= brick.second.x; i++) {
            for (int j = brick.first.y; j <= brick.second.y; j++) {
                if (top_view[i][j].first >= height) {
                    if (top_view[i][j].first > height) {
                        brick_idxs.clear();
                        height = top_view[i][j].first;
                    }
                    if (top_view[i][j].second != -1) {
                        brick_idxs.insert(top_view[i][j].second);
                    }
                }
            }
        }

        for (int prev_idx: brick_idxs) {
            adj[prev_idx].push_back(bidx);
            inputs[bidx]++;
        }

        height += abs(brick.first.z - brick.second.z) + 1;
        for (int i = brick.first.x; i <= brick.second.x; i++) {
            for (int j = brick.first.y; j <= brick.second.y; j++) {
                top_view[i][j].first = height;
                top_view[i][j].second = bidx;
            }
        }

//        cout << endl;
//        cout << height << endl;
//        for (int i = 0; i < top_view.size(); i++) {
//            for (int j = 0; j < top_view[0].size(); ++j) {
//                cout << top_view[i][j].first << " ";
//            }
//            cout << endl;
//        }

    }

    int ans=0;
    for (int i = 0; i < bricks.size(); ++i) {
        int disintegrated = top_sort(i, adj, inputs);
        cout<<disintegrated<<endl;
        ans+=disintegrated;
    }

    cout << endl;
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

