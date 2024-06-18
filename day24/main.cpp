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

    while (getline(input, input_line)) {
        auto splitted = split(input_line, "@");
        splitted = trim(splitted, " ");
        auto pos = trim(split(splitted[0], ","), " ");
        auto vel = trim(split(splitted[1], ","), " ");
//        cout<<"{{"<<pos[0]<<","<<pos[1]<<"},{"<<vel[0]<<","<<vel[1]<<"}},";
        cout << "{{" << pos[0] << "," << pos[1] << "," << pos[2] << "},{" << vel[0] << "," << vel[1] << "," << vel[2]
             << "}},";
    }

}


void part2(ifstream &input) {

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

