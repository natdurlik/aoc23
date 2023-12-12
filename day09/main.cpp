#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <deque>
#include <numeric>
#include "utils_aoc.h"

using namespace std;

long long get_next(const vector<long long> &seq) {
    if (std::all_of(seq.begin(), seq.end(), [](long long x) { return x == 0; })) {
        return 0;
    }

    vector<long long> diffs;
    for (int i = 1; i < seq.size(); i++) {
        diffs.push_back(seq[i] - seq[i - 1]);
    }

    long long diff = get_next(diffs);
    return seq.back() + diff;
}

void part1(ifstream &input) {

    string line;
    vector<vector<long long>> lines;
    while (getline(input, line)) {
        lines.push_back(stoi(filter(split(line, " "))));
    }

    long long ans = 0;

    for (const auto &nums: lines) {
        long long next = get_next(nums);
        cout << next << " ";
        ans += next;
    }
    cout << endl;

    cout << ans << endl;

}

long long get_prev(const vector<long long> &seq) {
    if (std::all_of(seq.begin(), seq.end(), [](long long x) { return x == 0; })) {
        return 0;
    }

    vector<long long> diffs;
    for (int i = 1; i < seq.size(); i++) {
        diffs.push_back(seq[i] - seq[i - 1]);
    }

    long long diff = get_prev(diffs);
    return seq.front() - diff;
}

void part2(ifstream &input) {

    string line;
    vector<vector<long long>> lines;
    while (getline(input, line)) {
        lines.push_back(stoi(filter(split(line, " "))));
    }

    long long ans = 0;

    for (const auto &nums: lines) {
        long long next = get_prev(nums);
        cout << next << " ";
        ans += next;
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

    input.close();
}
