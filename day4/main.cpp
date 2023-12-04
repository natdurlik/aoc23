#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <deque>
#include "utils_aoc.h"


using namespace std;


void part1(ifstream &input) {
    string line;

    long long sum = 0;

    while (getline(input, line)) {
        line = split(line, ":")[1];
        string win = trim(split(line, "|")[0], " ");
        string my = trim(split(line, "|")[1], " ");

        vector<int> wins = stoi(filter(split(win, " ")));
        vector<int> mys = stoi(filter(split(my, " ")));

        set<int> win_set(wins.begin(), wins.end());
        set<int> my_set(mys.begin(), mys.end());

        vector<int> intersection;
        set_intersection(win_set.begin(), win_set.end(), my_set.begin(), my_set.end(), back_inserter(intersection));
        long long counter = intersection.empty() ? 0 : (1 << (intersection.size()-1));
        sum += counter;
    }

    cout << sum << endl;
}


void part2(ifstream &input) {
    string line;

    long long sum = 0;

    vector<int> copies(212 + 1, 1);
    while (getline(input, line)) {
        int id=stoi(line.substr(5));
        line = split(line, ":")[1];
        string win = trim(split(line, "|")[0], " ");
        string my = trim(split(line, "|")[1], " ");

        vector<int> wins = stoi(filter(split(win, " ")));
        vector<int> mys = stoi(filter(split(my, " ")));

        set<int> win_set(wins.begin(), wins.end());
        set<int> my_set(mys.begin(), mys.end());

        vector<int> intersection;
        set_intersection(win_set.begin(), win_set.end(), my_set.begin(), my_set.end(), back_inserter(intersection));
        long long counter = intersection.size();

        for (int i = id + 1; i < std::min((long long)copies.size(), counter + id + 1); i++) {
            copies[i] += copies[id];
        }

        sum += copies[id];
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
