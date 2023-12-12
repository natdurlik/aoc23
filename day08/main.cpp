#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <deque>
#include <numeric>
#include "utils_aoc.h"


using namespace std;


void part1(ifstream &input) {
    string moves;
    getline(input, moves);
    cout << moves << endl;

    string line;
    unordered_map<string, pair<string, string>> node_to_nexts;
    while (getline(input, line)) {
        if (line.empty()) continue;
        string node = line.substr(0, 3);
        string lnext = line.substr(7, 3);
        string rnext = line.substr(12, 3);
        node_to_nexts[node] = {lnext, rnext};
        cout << node << " " << lnext << " " << rnext << endl;
    }

//    string start = "AAA";
    string curr = "AAA";
    string stop = "ZZZ";

    long long ans = 0;

    int idx = 0;
    while (true) {
//        cout<<curr<<endl;
        if (idx >= moves.size()) {
            idx = 0;
        }

        if (curr == stop) {
            break;
        }

        if (moves[idx] == 'L') {
            curr = node_to_nexts[curr].first;
        } else {
            curr = node_to_nexts[curr].second;
        }
        ans++;

        idx++;
    }

    cout << ans << endl;

}

long long
get_moves(string start, string moves, unordered_map<string, pair<string, string>> &node_to_nexts) {
    string curr = start;

    int idx = 0;
    long long ans = 0;
    while (true) {
        if (idx >= moves.size()) {
            idx = 0;
        }

        if (curr[2] == 'Z') {
            break;
        }

        if (moves[idx] == 'L') {
            curr = node_to_nexts[curr].first;
        } else {
            curr = node_to_nexts[curr].second;
        }
        ans++;

        idx++;
    }
    return ans;
}

void part2(ifstream &input) {
    string moves;
    getline(input, moves);
//    cout << moves << endl;

    string line;
    unordered_map<string, pair<string, string>> node_to_nexts;
    vector<string> currs;
    while (getline(input, line)) {
        if (line.empty()) continue;
        string node = line.substr(0, 3);
        string lnext = line.substr(7, 3);
        string rnext = line.substr(12, 3);
        node_to_nexts[node] = {lnext, rnext};
        if (node[2] == 'A') {
            currs.push_back(node);
        }
    }
    cout << node_to_nexts.size() << endl;
    cout << endl;

    long long ans = get_moves(currs[0], moves, node_to_nexts);

    for (const string &curr: currs) {
        ans = std::lcm(ans, get_moves(curr, moves, node_to_nexts));
//        cout << ans << endl;
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
