#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <deque>
#include "utils_aoc.h"


using namespace std;


void part1(ifstream &input) {
    string line;
    // A, K, Q, J, T, 9, 8, 7, 6, 5, 4, 3, or 2
    vector<pair<string, int>> hands;
    while (getline(input, line)) {
        vector<string> splitted = filter(split(line, " "));
//        print(splitted);
        hands.emplace_back(splitted[0], stoi(splitted[1]));
    }

    vector<char> order = {'A', 'K', 'Q', 'J', 'T', '9', '8', '7', '6', '5', '4', '3', '2'};
    reverse(order.begin(), order.end());

    auto get_type = [](const pair<string, int> &hand) {
        vector<int> counter(255, 0);
        string s = hand.first;
        for (char c: s) {
            counter[c]++;
        }
//        print(counter);

        vector<int> tmp(6);
        for (int c: counter) {
            if (c != 0) {
                tmp[c]++;
            }
        }

        if (tmp[5]) return 6;
        if (tmp[4]) return 5;
        if (tmp[3] && tmp[2]) return 4;
        if (tmp[3] && tmp[1]) return 3;
        if (tmp[2] == 2) return 2;
        if (tmp[2]) return 1;
        return 0;
    };

//    long pos = distance(order.begin(),find(order.begin(), order.end(), 'A'));
//    cout<<pos<<endl;
    cout << get_type({"11341", 1}) << endl;
//    cout<<get_type({"22FJH",1})<<endl;
//    cout<<get_type({"22FTH",1})<<endl;

    sort(hands.begin(), hands.end(), [&](const pair<string, int> &lhs, const pair<string, int> &rhs) {
        int ltype = get_type(lhs);
        int rtype = get_type(rhs);

        if (ltype != rtype) {
            return ltype < rtype;
        }
        string lh = lhs.first;
        string rh = rhs.first;
        for (int i = 0; i < lh.size(); i++) {
            long lpos = distance(order.begin(), find(order.begin(), order.end(), lh[i]));
            long rpos = distance(order.begin(), find(order.begin(), order.end(), rh[i]));
            if (lpos != rpos) {
                return lpos < rpos;
            }
        }
        cout << "same" << endl;
        return false;
    });


    long long ans = 0;
    for (int i = 0; i < hands.size(); i++) {
        cout << hands[i].first << " " << get_type(hands[i]) << ", ";
        ans += (long long) (i + 1) * hands[i].second;
//        cout << ans << endl;
    }
    cout << endl;

    cout << ans << endl;

    //252198930

}

void part2(ifstream &input) {
    string line;
    // A, K, Q, J, T, 9, 8, 7, 6, 5, 4, 3, or 2
    vector<pair<string, int>> hands;
    while (getline(input, line)) {
        vector<string> splitted = filter(split(line, " "));
        hands.emplace_back(splitted[0], stoi(splitted[1]));
    }

    vector<char> order = {'A', 'K', 'Q', 'T', '9', '8', '7', '6', '5', '4', '3', '2', 'J'};
    reverse(order.begin(), order.end());

    auto get_type = [](const pair<string, int> &hand) {
        vector<int> counter(255, 0);
        string s = hand.first;
        int jokers = 0;
        for (char c: s) {
            if (c != 'J') {
                counter[c]++;
            } else {
                jokers++;
            }
        }

        if (jokers == 5) return 6;
        if (jokers == 4) return 6;

        vector<int> tmp(6);
        for (int c: counter) {
            if (c != 0) {
                tmp[c]++;
            }
        }

        if (jokers != 0) {
            for (int i = 5; i >= 0; i--) {
                if (tmp[i] != 0) {
                    tmp[i]--;
                    tmp[i + jokers]++;
                    break;
                }
            }

        }

        if (tmp[5]) return 6;
        if (tmp[4]) return 5;
        if (tmp[3] && tmp[2]) return 4;
        if (tmp[3] && tmp[1]) return 3;
        if (tmp[2] == 2) return 2;
        if (tmp[2]) return 1;
        return 0;
    };

//    long pos = distance(order.begin(),find(order.begin(), order.end(), 'A'));
//    cout<<pos<<endl;
    cout << get_type({"J1341", 1}) << endl;
    cout << get_type({"J1J41", 1}) << endl;
    cout << get_type({"J1J41", 1}) << endl;
//    cout<<get_type({"22FJH",1})<<endl;
//    cout<<get_type({"22FTH",1})<<endl;

    sort(hands.begin(), hands.end(), [&](const pair<string, int> &lhs, const pair<string, int> &rhs) {
        int ltype = get_type(lhs);
        int rtype = get_type(rhs);

        if (ltype != rtype) {
            return ltype < rtype;
        }
        string lh = lhs.first;
        string rh = rhs.first;
        for (int i = 0; i < lh.size(); i++) {
            long lpos = distance(order.begin(), find(order.begin(), order.end(), lh[i]));
            long rpos = distance(order.begin(), find(order.begin(), order.end(), rh[i]));
            if (lpos != rpos) {
                return lpos < rpos;
            }
        }
        cout << "same" << endl;
        return false;
    });


    long long ans = 0;
    for (int i = 0; i < hands.size(); i++) {
        cout << hands[i].first << " " << get_type(hands[i]) << ", ";
        ans += (long long) (i + 1) * hands[i].second;
//        cout << ans << endl;
    }
    cout << endl;

    cout << ans << endl;
//249469020
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
