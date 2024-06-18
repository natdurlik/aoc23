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

    unordered_map<string, unordered_map<string, bool>> inputs; // is high
    unordered_map<string, vector<string>> outputs;
    unordered_map<string, bool> flipped;

    while (getline(input, input_line)) {
        auto splitted = split(input_line, ">");
        string module = splitted[0];
        module = trim(module, " -");
        auto outs = split(splitted[1], ",");
        outs = trim(outs, " ,");

        cout << module << endl;
        for (const auto &s: outs) {
            cout << s << " ";
        }
        cout << endl;

        if (module[0] == '%') {
            flipped[trim(module, "% ")] = false;
        }
        module = trim(module, "%& ");
        outputs[module] = outs;
        for (const auto &o: outs) {
            inputs[o][module] = false;
        }
    }


    vector<int> pulses_count(2, 0);

    for (int button_push = 0; button_push < 1000; ++button_push) {
        bool start_pulse = false;
        pulses_count[0]++;
        string broadcaster = "broadcaster";
        queue<pair<string, bool>> que;
        que.emplace(broadcaster, start_pulse);

        while (!que.empty()) {
            string curr = que.front().first;
            bool is_high_pulse = que.front().second;
            que.pop();

            if (curr == broadcaster) {
                bool next_pulse = is_high_pulse;
                for (const auto &output: outputs[curr]) {
                    que.emplace(output, next_pulse);
                    inputs[output][curr] = next_pulse;
                    pulses_count[next_pulse]++;
                }
            } else if (flipped.contains(curr)) {
                if (!is_high_pulse) {
                    flipped[curr] = !flipped[curr];
                    bool next_pulse = flipped[curr];
                    for (const auto &output: outputs[curr]) {
                        que.emplace(output, next_pulse);
                        inputs[output][curr] = next_pulse;
                        pulses_count[next_pulse]++;
                    }
                }
            } else {
                bool all_high = true;
                for (auto [_, input_pulse]: inputs[curr]) {
                    all_high &= input_pulse;
                }

                bool next_pulse = !all_high;
                for (const auto &output: outputs[curr]) {
                    que.emplace(output, next_pulse);
                    inputs[output][curr] = next_pulse;
                    pulses_count[next_pulse]++;
                }
            }
        }
    }

    cout << "low, high pulses: " << endl;
    cout << pulses_count[0] << " " << pulses_count[1] << endl;
    cout << (long long) pulses_count[0] * pulses_count[1] << endl;
}

void print_mathematica_input(const unordered_map<string, vector<string>> &outputs,
                             const unordered_map<string, bool> &flipped, const string &broadcaster) {
    for (auto [node, adj]: outputs) {
        if (flipped.contains(node)) {
            cout << "%";
        } else if (node != broadcaster) {
            cout << "&";
        }
        cout << node << " ";
        for (const auto &next: adj) {
            if (flipped.contains(next)) {
                cout << "%";
            } else if (next != broadcaster) {
                cout << "&";
            }
            cout << next << " ";
        }
        cout << endl;
    }
}

void part2(ifstream &input) {
    string input_line;

    unordered_map<string, unordered_map<string, bool>> inputs; // is high
    unordered_map<string, vector<string>> outputs;
    unordered_map<string, bool> flipped;

    while (getline(input, input_line)) {
        auto splitted = split(input_line, ">");
        string module = splitted[0];
        module = trim(module, " -");
        auto outs = split(splitted[1], ",");
        outs = trim(outs, " ,");

        if (module[0] == '%') {
            flipped[trim(module, "% ")] = false;
        }
        module = trim(module, "%& ");
        outputs[module] = outs;
        for (const auto &o: outs) {
            inputs[o][module] = false;
        }
    }

    cout << "all: " << inputs.size() << endl;
    cout << "flipflops: " << flipped.size() << endl;
    //    print_mathematica_input(outputs, flipped, broadcaster);


    string broadcaster = "broadcaster";
    int presses = 0;
    // graph is divided in 4 sections - visualization in mathematica
    unordered_map<string, int> sections_min{
            {"vc", -1},
            {"nb", -1},
            {"vg", -1},
            {"ls", -1}
    };


    bool found = false;
    while (!found) {
        presses++;
        bool start_pulse = false;
        queue<pair<string, bool>> que;
        que.emplace(broadcaster, start_pulse);

        while (!que.empty()) {
            string curr = que.front().first;
            bool is_high_pulse = que.front().second;
            que.pop();

            if (sections_min.contains(curr)) {
                if (sections_min[curr] == -1 && !is_high_pulse) {
                    sections_min[curr] = presses;
                }
            }

            if (curr == broadcaster) {
                bool next_pulse = is_high_pulse;
                for (const auto &output: outputs[curr]) {
                    que.emplace(output, next_pulse);
                    inputs[output][curr] = next_pulse;
                }
            } else if (flipped.contains(curr)) {
                if (!is_high_pulse) {
                    flipped[curr] = !flipped[curr];
                    bool next_pulse = flipped[curr];
                    for (const auto &output: outputs[curr]) {
                        que.emplace(output, next_pulse);
                        inputs[output][curr] = next_pulse;
                    }
                }
            } else {
                bool all_high = true;
                for (auto [_, input_pulse]: inputs[curr]) {
                    all_high &= input_pulse;
                }

                bool next_pulse = !all_high;
                for (const auto &output: outputs[curr]) {
                    que.emplace(output, next_pulse);
                    inputs[output][curr] = next_pulse;
                }
            }
        }

        found = true;
        for (auto [section, val]: sections_min) {
            if (val == -1) {
                found = false;
            }
        }
    }

    long long ans = 1;
    for (auto [section, val]: sections_min) {
        cout << section << ": " << val << endl;
        ans = lcm(ans, val);
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
//
    input.close();
}

