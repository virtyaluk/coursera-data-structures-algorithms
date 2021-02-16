/*
* Note: This template uses some c++11 functions , so you have to compile it with c++11 flag.
* Example: $ g++ -std=c++11 c++ source.cpp
*
* Author: Bohdan Shtepan
* GitHub: https://github.com/virtyaluk
* Site: https://modern-dev.com
*
*/

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long int
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<vi> vvi;
typedef vector<vll> vvll;
typedef vector<float> vf;
typedef vector<double> vd;

const int MAX_N = 1e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;

vector<string> makeEulerCycle(map<string, vector<string>> graph) {
    stack<string> verteces;
    vector<string> path;
    path.reserve(graph.size());
    verteces.push(graph.begin()->first);
    string current = verteces.top();

    while (not verteces.empty()) {
        current = verteces.top();

        if (not graph[current].empty()) {
            verteces.push(move(graph[current].back()));
            graph[current].pop_back();
            continue;
        }

        path.emplace_back(move(current));
        verteces.pop();
    }

    reverse(path.begin(), path.end());
    return path;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    string s;
    map<string, vector<string>> graph;

    while (cin >> s) {
        graph[s.substr(0, s.size() - 1)].emplace_back(s.substr(1));
    }

    const vector<string> cycle = makeEulerCycle(graph);

    cout << cycle.front();

    for (int i = 1; i < cycle.size() - 9; i++) {
        cout << cycle[i].back();
    }

    cout << endl;

    return 0;
}
