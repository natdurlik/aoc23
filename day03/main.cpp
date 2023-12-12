#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <deque>
#include "utils_aoc.h"


using namespace std;

bool in_grid(int i, int j, const vector<string> &lines) {
    return i >= 0 && j >= 0 && i < lines.size() && j < lines[i].size();
}

bool is_symbol(int i, int j, const vector<string> &lines) {
    return lines[i][j] != '.' && !isdigit(lines[i][j]);
}

bool is_not_banned(int i, int j, int ban_i, int ban_j) {
    return i != ban_i || j != ban_j;
}

bool is_adjacent(int i, int j, const vector<string> &lines) {
    vector<vector<int>> dirs{
            {0,  1},
            {0,  -1},
            {1,  0},
            {-1, 0},
            {1,  1},
            {1,  -1},
            {-1, -1},
            {-1, 1}
    };
    if (!isdigit(lines[i][j])) {
        cout << " not digit! " << endl;
        return false;
    }

    for (const auto &dir: dirs) {
        int row = i + dir[0];
        int col = j + dir[1];

        if (in_grid(row, col, lines) && is_symbol(row, col, lines)) {
            return true;
        }
    }

    return false;
}

void part1(ifstream &input) {
    string line;

    vector<string> lines;

    while (getline(input, line)) {
        lines.push_back(line);
    }

    int sum = 0;
    int n = lines.size();

    for (int i = 0; i < lines.size(); i++) {
        for (int j = 0; j < lines[0].size(); j++) {
            if (isdigit(lines[i][j])) {
                int x = stoi(lines[i].substr(j));
                bool adjacent = false;
                while (j < lines[i].size() && isdigit(lines[i][j])) {
                    if (!adjacent && is_adjacent(i, j, lines)) {
                        adjacent = true;
                        sum += x;
                        j++;
                    } else {
                        j++;
                    }
                }
            }
        }
    }

    cout << sum << endl;
}

int get_number(int row, int col, const vector<string> &lines, vector<vector<bool>> &visited) {
    int j = col;
    while (j >= 0 && isdigit(lines[row][j])) {
        visited[row][j] = true;
        j--;
    }
    j++;
    int x = stoi(lines[row].substr(j));
    while(j<=lines[row].size() && isdigit(lines[row][j])) {
        visited[row][j]=true;
        j++;
    }

    return x;
}

long long gear_ratio(int i, int j, const vector<string> &lines) {
    vector<vector<int>> dirs{
            {0,  1},
            {0,  -1},
            {1,  0},
            {-1, 0},
            {1,  1},
            {1,  -1},
            {-1, -1},
            {-1, 1}
    };

    int counter = 0;
    long long mult = 1;

    vector<vector<bool>> visited(lines.size(), vector<bool>(lines[0].size(), false));
    for (const auto &dir: dirs) {
        int row = i + dir[0];
        int col = j + dir[1];

        if (in_grid(row, col, lines) && isdigit(lines[row][col]) && !visited[row][col]) {
//            cout<< "; "<<row<< " "<< col<<" "<<lines[row][col]<<endl;
            counter++;
            if (counter <= 2) {
                mult *= get_number(row, col, lines, visited);
            }
        }
    }

    if (counter == 2) return mult;

    return 0;
}

void part2(ifstream &input) {
    string line;
    vector<string> lines;
    while (getline(input, line)) {
        lines.push_back(line);
    }
    long long sum = 0;

//    cout<<gear_ratio(8,5,lines)<<endl;
//    vector<vector<bool>> visited(lines.size(), vector<bool>(lines[0].size(), false));
//    cout<<get_number(7,6,lines,visited)<<endl;

    for (int i = 0; i < lines.size(); i++) {
        for (int j = 0; j < lines[0].size(); j++) {
            if (lines[i][j] == '*') {
                sum += gear_ratio(i, j, lines);
            }
        }
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
