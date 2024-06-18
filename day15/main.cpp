#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <deque>
#include <numeric>
#include "utils_aoc.h"

using namespace std;


void part1(ifstream &input) {
    string line;
    getline(input, line);
    cout << line << endl;
    cout << line.size() << endl;

    vector<string> seq = split(line, ",");
    cout << seq.size() << endl;

    int ans = 0;
    for (const auto &s: seq) {
        int curr = 0;
        for (char c: s) {
            curr += c;
            curr *= 17;
            curr %= 256;
        }
        cout << s << " " << curr << endl;
        ans += curr;
    }

    cout << ans << endl;
}

int get_hash(const string &s) {
    int curr = 0;
    for (char c: s) {
        curr += c;
        curr *= 17;
        curr %= 256;
    }
    return curr;
}


void part2(ifstream &input) {
    string line;
    getline(input, line);

    vector<string> seq = split(line, ",");

    vector<list<pair<string, int>>> boxes(256);
    for (const auto &s: seq) {
        if (s.contains('-')) {
//            cout << s << endl;
            string trimmed = trim(s, "-");
            int hash = get_hash(trimmed);
            auto it = boxes[hash].begin();
            while (it != boxes[hash].end()) {
                if (trimmed == (*it).first) {
//                    cout << trimmed << endl;
                    boxes[hash].erase(it);
                    break;
                }
                it++;
            }
        } else {
            auto parts = split(s, "=");
            cout << parts[0] << " " << parts[1] << " " << " " << get_hash(parts[0]) << endl;
            string trimmed = parts[0];
            int focal = stoi(parts[1]);
            int hash = get_hash(trimmed);

            bool f = false;
            auto it = boxes[hash].begin();
            while (it != boxes[hash].end()) {
                if (trimmed == (*it).first) {
                    f = true;
//                    cout << trimmed << endl;
                    (*it).second = focal;
                    break;
                }
                it++;
            }

            if (!f) {
                boxes[hash].emplace_back(trimmed, focal);
            }
        }
    }
    cout << endl;

    long long ans = 0;
    for (int i = 0; i < boxes.size(); i++) {
        int list_idx = 1;
        for (const auto &lense: boxes[i]) {
            long long curr = (i + 1) * list_idx * lense.second;
            ans += curr;
            cout << lense.first << " " << i << " " << list_idx << " " << lense.second << " " << curr << endl;
            list_idx++;
        }
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
