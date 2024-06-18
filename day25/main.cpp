#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <deque>
#include <numeric>
#include <sstream>
#include "utils_aoc.h"

using namespace std;


vector<int>
count_components(unordered_map<string, vector<string>> &adj, const vector<pair<string, string>> &disconnedted) {
    unordered_set<string> visited;
    vector<int> ans;

    for (auto [node, neighs]: adj) {
        if (!visited.contains(node)) {
            int size = 0;
            queue<string> que;
            que.push(node);
            visited.insert(node);
            size++;

            while (!que.empty()) {
                string curr = que.front();
                que.pop();

                for (const auto &neigh: adj[curr]) {
                    pair<string, string> edge = {curr, neigh};
                    pair<string, string> redge = {neigh, curr};
                    if (find(disconnedted.begin(), disconnedted.end(), edge) != disconnedted.end() ||
                        find(disconnedted.begin(), disconnedted.end(), redge) != disconnedted.end()) {
                        continue;
                    }
                    if (!visited.contains(neigh)) {
                        que.push(neigh);
                        visited.insert(neigh);
                        size++;
                    }
                }
            }

            ans.push_back(size);
        }
    }

    return ans;
}

void part1(ifstream &input) {
    string input_line;

    unordered_map<string, vector<string>> adj;
    vector<string> nodes;
    vector<pair<string, string>> edges;
    while (getline(input, input_line)) {
        auto splitted = split(input_line, ":");
        string name = trim(splitted[0], " ");
        nodes.push_back(name);
        splitted = filter(split(splitted[1], " "), "");
//        cout << name << endl;
        for (const auto &out: splitted) {
            edges.emplace_back(name, out);
//            cout << out << endl;
            adj[name].push_back(out);
            adj[out].push_back(name);
        }
    }

//    for (const auto &node: nodes) {
//        cout << node << ": ";
//        for (const auto &neigh: adj[node]) {
//            cout << neigh << " ";
//        }
//        cout << endl;
//    }

    cout << adj.size() << endl;
    cout << edges.size() << endl;


    int ans = 0;
    for (int i = 0; i < edges.size(); i++) {
        for (int j = 0; j < edges.size(); j++) {
            for (int k = 0; k < edges.size(); k++) {
                vector<pair<string, string>> disconnected{edges[i], edges[j], edges[k]};
//                cout << edges[i].first << " " << edges[i].second << "; " << edges[j].first << " " << edges[j].second
//                     << "; " << edges[k].first << " " << edges[k].second << endl;

                vector<int> components = count_components(adj, disconnected);
//                cout << components.size() << endl;
//                for (int component: components) {
//                    cout << component << " ";
//                }
//                cout << endl;

                if (components.size() == 2) {
                    cout << edges[i].first << " " << edges[i].second << "; " << edges[j].first << " " << edges[j].second
                     << "; " << edges[k].first << " " << edges[k].second << endl;
                    ans = components[0] * components[1];
                    cout<<ans<<endl;
                    return;
                }
            }
        }
    }


    cout<<"ans: "<< ans<<endl;
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

