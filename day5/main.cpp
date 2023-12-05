#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <deque>
#include "utils_aoc.h"


using namespace std;


void part1(ifstream &input) {

    string inp;
    vector<string> lines;
    while (getline(input, inp)) {
        lines.push_back(inp);
    }

//    print(split(lines[0].substr(7), " "));
    vector<long long> seedstmp = stoi(filter(split(lines[0].substr(7), " ")));
//    print(seedstmp);
    vector<long long> current = vector<long long>(seedstmp.begin(), seedstmp.end());
    print(current);
    lines = vector<string>(lines.begin() + 2, lines.end());

//    long long location = LONG_LONG_MAX;
    vector<vector<long long>> mapping;
    for (string line: lines) {
        if (line.empty()) {

            for (long long &curr: current) {
                for (int i = 0; i < mapping.size(); i++) {
                    if (mapping[i][1] <= curr) {
                        if (curr <= mapping[i][1] + mapping[i][2]) {
                            curr = mapping[i][0] + (curr - mapping[i][1]);
                            break;
                        }
                    }
                }
            }
//            print(current, " after: ");

        } else if (!isdigit(line[0])) {
            mapping.clear();
        } else {
            vector<long long> nums = stoi(filter(split(line, " ")));
            mapping.push_back({nums[0], nums[1], nums[2]});
        }
//501551390
    }
    // FIXME empty line at the end

    cout << *std::min_element(current.begin(), current.end()) << endl;

//    cout << location << endl;
}

struct range {
    long long start;
    long long stop;
};

range intersection(const range &a, const range &b) {
    if (a.start > b.start) return intersection(b, a);

    if (a.stop < b.start) return {-1, -1};
    long long start = max(a.start, b.start);
    long long stop = min(a.stop, b.stop);

    return {start, stop};
}

long long size(const range &a) {
    if(a.start==-1 || a.stop==-1) return 0;
    return a.stop - a.start + 1;
}

vector<range> split(range inter, range a) {
    if (inter.start == a.start && inter.stop == a.stop) {
        return {};
    }
    if (inter.start == a.start) {
        return {{inter.stop + 1, a.stop}};
    }
    if (inter.stop == a.stop) {
        return {{a.start, inter.start - 1}};
    }

    return {
            {a.start,        inter.start - 1},
            {inter.stop + 1, a.stop}
    };
}

void print(const vector<range> &v) {
    for (auto r: v) {
        cout << r.start << " " << r.stop << " , ";
    }
    cout << endl;
}

vector<range> process_mapping(const vector<range> &current, const vector<pair<long long, range>> &mapping) {
    vector<range> res;
//    print(current);

    for (const auto &curr: current) {

        bool f = false;
        for (auto [dest, r]: mapping) {
            range inter = intersection(curr, r);
//            cout<<"inter: "<<inter.start<<" "<<inter.stop<<endl;
            if (size(inter) == 0) {
                continue;
            }

            f = true;

            long long sizec = size(inter);
            long long new_start = dest + (inter.start - r.start);

            res.push_back({new_start, new_start + sizec - 1});

            vector<range> splitted = split(inter, curr);

            if (!splitted.empty()) {
                vector<range> processed_parts = process_mapping(splitted, mapping);
                res.insert(res.end(), processed_parts.begin(), processed_parts.end());
            }
        }

        if (!f) {
            res.push_back(curr);
        }

//        cout << "curr: " << curr.start << " " << curr.stop << endl;
//        print(res);
    }

    return res;
}

void part2(ifstream &input) {

    string inp;
    vector<string> lines;
    while (getline(input, inp)) {
        lines.push_back(inp);
    }

    vector<long long> seedstmp = stoi(filter(split(lines[0].substr(7), " ")));
    vector<range> current;
    for (int i = 0; i < seedstmp.size(); i += 2) {
        current.emplace_back(seedstmp[i], seedstmp[i] + seedstmp[i + 1] - 1);
    }
//    for (auto v: current) {
//        cout << v.start << " " << v.stop << endl;
//        cout << v.start << " " << v.stop << endl;
//    }
    lines = vector<string>(lines.begin() + 2, lines.end());

    long long location = LONG_LONG_MAX;
    vector<pair<long long, range>> mapping;
    for (string line: lines) {
        if (line.empty()) {
//            for (auto map: mapping) {
//                cout << map.first << ", " << map.second.start << " " << map.second.stop << endl;
//            }
            vector<range> processed = process_mapping(current, mapping);
            current = processed;

        } else if (!isdigit(line[0])) {
            mapping.clear();
        } else {
            vector<long long> nums = stoi(filter(split(line, " ")));
            mapping.push_back({nums[0], {nums[1], nums[2] + nums[1] - 1}});
        }
    }
    // FIXME empty line at the end

    for (auto r: current) {
        location = min(location, r.start);
    }

    cout << location << endl;
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
