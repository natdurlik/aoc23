#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <deque>
#include <numeric>
#include "utils_aoc.h"

using namespace std;

vector<vector<vector<long long>>> dp;

long long
arrangements_dp(const string &spring, const vector<int> &group_sizes, vector<int> curr_sizes, int spring_i,
                int group_i) {
    int si = spring_i;
    int gi = group_i;
    int curr = curr_sizes[group_i];

    if (spring_i == spring.size()) {
        if (group_i == group_sizes.size()) {
            return 1;
        }
        if (group_i + 1 == group_sizes.size() && group_sizes[group_i] == curr_sizes[group_i]) {
            return 1;
        }
        return 0;
    }

    if (dp[si][gi][curr] != -1) {
        return dp[si][gi][curr];
    }

    if (group_i == group_sizes.size()) {
        if (spring[spring_i] == '#') {
            return 0;
        }

        return dp[si][gi][curr] = arrangements_dp(spring, group_sizes, curr_sizes, spring_i + 1, group_i);
    }

    if (spring[spring_i] == '.') {
        if (curr_sizes[group_i] != 0) {
            if (curr_sizes[group_i] != group_sizes[group_i]) {
                return 0;
            }
            group_i++;
        }

        return dp[si][gi][curr] = arrangements_dp(spring, group_sizes, curr_sizes, spring_i + 1, group_i);
    }

    if (spring[spring_i] == '#') {
        curr_sizes[group_i]++;
        if (group_sizes[group_i] < curr_sizes[group_i]) {
            return 0;
        }

        return dp[si][gi][curr] = arrangements_dp(spring, group_sizes, curr_sizes, spring_i + 1, group_i);
    }

    if (spring[spring_i] == '?') {
        if (curr_sizes[group_i] != 0) {
            if (curr_sizes[group_i] == group_sizes[group_i]) {
                group_i++;
            } else if (curr_sizes[group_i] < group_sizes[group_i]) {
                curr_sizes[group_i]++;
            }
            return dp[si][gi][curr] = arrangements_dp(spring, group_sizes, curr_sizes, spring_i + 1, group_i);
        }

        long long part = arrangements_dp(spring, group_sizes, curr_sizes, spring_i + 1, group_i);
        curr_sizes[group_i]++;
        return dp[si][gi][curr] = part + arrangements_dp(spring, group_sizes, curr_sizes, spring_i + 1, group_i);
    }

    return 0;
}


long long
arrangements(const string &spring, const vector<int> &group_sizes, vector<int> curr_sizes, int spring_i, int group_i) {
    if (spring_i == spring.size()) {
        if (group_i == group_sizes.size()) {
            return 1;
        }
        if (group_i + 1 == group_sizes.size() && group_sizes[group_i] == curr_sizes[group_i]) {
            return 1;
        }
        return 0;
    }

    if (group_i == group_sizes.size()) {
        if (spring[spring_i] == '#') {
            return 0;
        }

        return arrangements(spring, group_sizes, curr_sizes, spring_i + 1, group_i);
    }

    if (spring[spring_i] == '.') {
        if (curr_sizes[group_i] != 0) {
            if (curr_sizes[group_i] != group_sizes[group_i]) {
                return 0;
            }
            group_i++;
        }

        return arrangements(spring, group_sizes, curr_sizes, spring_i + 1, group_i);
    }

    if (spring[spring_i] == '#') {
        curr_sizes[group_i]++;
        if (group_sizes[group_i] < curr_sizes[group_i]) {
            return 0;
        }

        return arrangements(spring, group_sizes, curr_sizes, spring_i + 1, group_i);
    }

    if (spring[spring_i] == '?') {
        if (curr_sizes[group_i] != 0) {
            if (curr_sizes[group_i] == group_sizes[group_i]) {
                group_i++;
            } else if (curr_sizes[group_i] < group_sizes[group_i]) {
                curr_sizes[group_i]++;
            }
            return arrangements(spring, group_sizes, curr_sizes, spring_i + 1, group_i);
        }

        long long part = arrangements(spring, group_sizes, curr_sizes, spring_i + 1, group_i);
        curr_sizes[group_i]++;
        return part + arrangements(spring, group_sizes, curr_sizes, spring_i + 1, group_i);
    }

    cout << "err - function end" << endl;
    return 0;
}

void part1(ifstream &input) {
    string line;
    vector<string> springs;
    vector<vector<int>> group_sizes;
    while (getline(input, line)) {
        auto sp = filter(split(line, " "));
        springs.push_back(sp[0]);
        vector<int> tmp = stoi(filter(split(sp[1], ",")));
        group_sizes.push_back(tmp);
    }

    int maxs = 0;
    for (int i = 0; i < springs.size(); i++) {
        maxs = std::max((int) springs[i].size(), maxs);
        cout << springs[i] << " ";
        for (int j: group_sizes[i]) {
            cout << j << " ";
        }
        cout << endl;
    }
    cout << "max input size: " << maxs << endl;
    cout << endl;

    long long ans = 0;
    for (int i = 0; i < springs.size(); ++i) {
        vector<int> curr_sizes(group_sizes[i].size(), 0);
        long long ways = arrangements(springs[i], group_sizes[i], curr_sizes, 0, 0);
        cout << ways << endl;
        ans += ways;
    }
    cout << ans << endl;

}

void part2(ifstream &input) {
    string line;
    vector<string> springs;
    vector<vector<int>> group_sizes;
    while (getline(input, line)) {
        auto sp = filter(split(line, " "));

        springs.push_back(sp[0]);
        for (int i = 0; i < 4; ++i) {
            springs.back() += '?';
            springs.back() += sp[0];
        }

        vector<int> tmp = stoi(filter(split(sp[1], ",")));
        group_sizes.push_back(tmp);

        for (int i = 0; i < 4; ++i) {
            group_sizes.back().insert(group_sizes.back().end(), tmp.begin(), tmp.end());
        }


    }

    int maxs = 0;
    for (int i = 0; i < springs.size(); i++) {
        maxs = std::max((int) springs[i].size(), maxs);
        cout << springs[i] << " ";
        for (int j: group_sizes[i]) {
            cout << j << " ";
        }
        cout << endl;
    }
    cout << "max input size: " << maxs << endl;
    cout << endl;

    long long ans = 0;
//    vector<int> curr_sizes(group_sizes[1].size(), 0);
//    long long way = arrangements(springs[1], group_sizes[1], curr_sizes, 0, 0);
//    cout << "arr: " << way << endl;
    for (int i = 0; i < springs.size(); ++i) {
        vector<int> curr_sizes(group_sizes[i].size() + 1, 0);
        int maxi_group_length = *max_element(group_sizes[i].begin(), group_sizes[i].end());

        vector<vector<vector<long long>>> newdp(springs[i].size() + 1,
                                                vector<vector<long long>>(group_sizes[i].size() + 1,
                                                                          vector<long long>(maxi_group_length * 2,
                                                                                            -1)));
        dp = newdp;

        long long ways = arrangements_dp(springs[i], group_sizes[i], curr_sizes, 0, 0);
        cout << ways << endl;
        ans += ways;
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
