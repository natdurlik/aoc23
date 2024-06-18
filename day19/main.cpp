#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <deque>
#include <numeric>
#include <sstream>
#include "utils_aoc.h"

using namespace std;


struct part {
    int x;
    int m;
    int a;
    int s;
};

bool check_condition(string condition, part part) {
    char cat = condition[0];
    char op = condition[1];
    int val = stoi(condition.substr(2));

    if (cat == 'x') {
        if (op == '>') {
            return part.x > val;
        } else return part.x < val;
    }
    if (cat == 'm') {
        if (op == '>') {
            return part.m > val;
        } else return part.m < val;
    }
    if (cat == 'a') {
        if (op == '>') {
            return part.a > val;
        } else return part.a < val;
    }
    if (cat == 's') {
        if (op == '>') {
            return part.s > val;
        } else return part.s < val;
    }

    cout << "err, bad category" << endl;
    return false;
}

bool process_part(unordered_map<string, vector<std::string>> &workflows, part part, const string &curr) {
    if (curr == "R") {
        return false;
    }
    if (curr == "A") {
        return true;
    }

    vector<string> rules = workflows.at(curr);
    string finally = rules.back();
    rules.pop_back();

    for (const auto &rule: rules) {
        vector<string> splitted = split(rule, ":");
        string condition = splitted[0];
        string val = splitted[1];

        if (check_condition(condition, part)) {
            return process_part(workflows, part, val);
        }
    }

    return process_part(workflows, part, finally);
}

void part1(ifstream &input) {
    string input_line;

    unordered_map<string, vector<string>> workflows;
    while (getline(input, input_line)) {
        if (input_line.empty()) break;

        auto splitted = split(input_line, "{");
        string name = splitted[0];
        splitted = trim(split(splitted[1], ","), "}");

        cout << name << " ";
        for (const auto &rule: splitted) {
            cout << rule << " ";
        }
        cout << endl;
        workflows[name] = splitted;
    }
    cout << endl;
    vector<part> parts;
    while (getline(input, input_line)) {

        auto splitted = trim(split(input_line, ","), "{}");

        int x = stoi(splitted[0].substr(2));
        int m = stoi(splitted[1].substr(2));
        int a = stoi(splitted[2].substr(2));
        int s = stoi(splitted[3].substr(2));

        cout << x << " " << m << " " << a << " " << s << endl;
        parts.push_back({x, m, a, s});
    }
    cout << endl;
    cout << endl;

    long long ans = 0;
    string start = "in";
    for (auto part: parts) {
        bool accepted = process_part(workflows, part, start);
        if (accepted) {
            long long sum = part.x + part.m + part.a + part.s;
            cout << part.x << " " << part.m << " " << part.a << " " << part.s << " " << sum << endl;
            ans += sum;
        }
    }


    cout << ans << endl;
}


using part_range = map<char, pair<int, int>>;
//struct part_range {
////    unordered_map<char,vector<int>> type;
//    vector<int> x;
//    vector<int> m;
//    vector<int> a;
//    vector<int> s;
//};

long long get_combinations(const part_range &pr) {
    long long ans = 1;
    for (auto [_, range]: pr) {
        ans *= (long long) (range.second - range.first);
    }
    return ans;
}

bool is_valid_not_empty(const part_range &pr) {
    for (auto [_, range]: pr) {
        if (range.first > range.second) {
            return false;
        }
    }
    return true;
}

part_range reduce_range(string condition, part_range pr, part_range &rest) {
    char cat = condition[0];
    char op = condition[1];
    int val = stoi(condition.substr(2));

    if (op == '>') {
        pr[cat].first = max(pr[cat].first, (val + 1));
        rest[cat].second = min(rest[cat].second, val + 1);
    } else {
        pr[cat].second = min(pr[cat].second, val);
        rest[cat].first = max(rest[cat].first, val);
    }
    return pr;
}

long long count_parts(const unordered_map<string, vector<string>> &workflows, part_range pr, const string &curr) {
    if (!is_valid_not_empty(pr)) {
        return 0;
    }
    if (curr == "R") {
        return 0;
    }
    if (curr == "A") {
        for (auto [cat, range]: pr) {
            cout << cat << ":" << range.first << "," << range.second << "; ";
        }
        cout << endl;
        return get_combinations(pr);
    }

    vector<string> rules = workflows.at(curr);
    string finally = rules.back();
    rules.pop_back();

    part_range rest = pr;
    long long ans = 0;
    for (const auto &rule: rules) {
        vector<string> splitted = split(rule, ":");
        string condition = splitted[0];
        string val = splitted[1];

        part_range next_pr = reduce_range(condition, pr, rest);
        ans += count_parts(workflows, next_pr, val);
        pr = rest;
    }

    ans += count_parts(workflows, rest, finally);

    return ans;
}

void part2(ifstream &input) {
    string input_line;

    unordered_map<string, vector<string>> workflows;
    while (getline(input, input_line)) {
        if (input_line.empty()) break;

        auto splitted = split(input_line, "{");
        string name = splitted[0];
        splitted = trim(split(splitted[1], ","), "}");

        cout << name << " ";
        for (const auto &rule: splitted) {
            cout << rule << " ";
        }
        cout << endl;
        workflows[name] = splitted;
    }
    cout << endl;
    cout << endl;

    long long ans = 0;
    string start = "in";
    part_range pr{
            {'x', {1, 4001}},
            {'m', {1, 4001}},
            {'a', {1, 4001}},
            {'s', {1, 4001}}
    };
    ans = count_parts(workflows, pr, start);

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

