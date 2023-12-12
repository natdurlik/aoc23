#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <utility>
#include <list>
#include <queue>
#include <stack>
#include <deque>
#include <set>
#include <map>
#include <array>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <bitset>
#include <limits.h>


using namespace std;


vector<int> input_to_vec(ifstream &input) {
    vector<int> res;
    string line;
    while (getline(input, line)) {
        res.push_back(stoi(line));
    }
    return res;
}



int isdigit(const string& s, int start) {
    unordered_map<string,int> digits{
            {"one",1},
            {"two",2},
            {"three",3},
            {"four",4},
            {"five",5},
            {"six",6},
            {"seven",7},
            {"eight",8},
            {"nine",9}
    };
    if(isdigit(s[start])) {
        return s[start]-'0';
    }
    for(auto [key,val]: digits) {
        if((s.substr(start)).starts_with(key)) {
            return val;
        }
    }

    return -1;
}

int main() {
    ifstream input("/home/leartsura/Documents/projects/aoc23/input");
    if (input.fail()) {
        cout << "cant open input file" << endl;
        exit(0);
    }
    string line;


    int sum=0;
    while (getline(input, line)) {
        int x=0;
        int n=line.size();
        for(int i=0;i<n;i++) {
            int d=isdigit(line,i);
            if(d!=-1) {
                cout<<d<<endl;
                x+=d;
                break;
            }
        }
        x*=10;
        for(int i=n;i>=0;i--) {
            int d=isdigit(line,i);
            if(d!=-1) {
                cout<<d<<endl;
                x+=d;
                break;
            }
        }
        sum+=x;
    }

    cout<<sum<<endl;

    input.close();
}
