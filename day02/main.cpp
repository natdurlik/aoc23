#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <deque>
#include "utils.h"

using namespace std;


void part1(ifstream &input) {
    string line;
    int sum = 0;
    vector<int> maxes{12, 13, 14};

    while (getline(input, line)) {
        int id = stoi(line.substr(5));
        line = split(line, ":").back();

        vector<string> subgames = trim(split(line, ";"), " ");
        print(subgames);

        bool possible = true;
        for (string subgame: subgames) {
            vector<string> pulls = trim(split(subgame, ","), " ");
            print(pulls);
            for (string pull: pulls) {
                int x = stoi(pull);
                if (pull.find('d') != string::npos) {
                    if (x > maxes[0]) {
                        possible = false;
                        break;
                    }
                } else if (pull.find('g') != string::npos) {
                    if (x > maxes[1]) {
                        possible = false;
                        break;
                    }
                } else if (pull.find('b') != string::npos) {
                    if (x > maxes[2]) {
                        possible = false;
                        break;
                    }
                }
            }
        }

        if (possible) {
            sum += id;
        }

    }

    cout << sum << endl;
}

void part2(ifstream &input) {
    string line;
    int sum = 0;

    while (getline(input, line)) {
        int id = stoi(line.substr(5));
        line = split(line, ":").back();

        vector<string> subgames = trim(split(line, ";"), " ");
        print(subgames);

        vector<int> maxes{0, 0, 0};
        for (string subgame: subgames) {
            vector<string> pulls = trim(split(subgame, ","), " ");
            print(pulls);
            for (string pull: pulls) {
                int x = stoi(pull);
                if (pull.find('d') != string::npos) {
                    maxes[0] = max(maxes[0], x);
                } else if (pull.find('g') != string::npos) {
                    maxes[1] = max(maxes[1], x);
                } else if (pull.find('b') != string::npos) {
                    maxes[2] = max(maxes[2], x);
                }
            }
        }

        sum += maxes[0] * maxes[1] * maxes[2];

    }

    cout << sum << endl;
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
