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

vector<string> makeEulerCycle(map<string, set<string>> graph) {
    stack <string> verteces;
    vector <string> path;
    verteces.push(graph.begin()->first);
    string current = verteces.top();

    while (not verteces.empty()) {
        current = verteces.top();

        if (not graph[current].empty()) {
            verteces.push(*graph[current].begin());
            graph[current].erase(graph[current].begin());
            continue;
        }

        path.push_back(current);
        verteces.pop();
    }

    reverse(path.begin(), path.end());
    return path;
}

map<string, set<string>> makeDeBruijnGraph(const int k, const int n) {
    map<string, set<string>> graph;

    for (size_t i = 0; i < n; i++) {
        auto s1 = bitset < 16 > {i}.to_string().substr(16 - k, k - 1),
                s2 = bitset < 16 > {i * 2 % n}.to_string().substr(16 - k),
                s3 = bitset < 16 > {i * 2 % n + 1}.to_string().substr(16 - k);

        graph[s1].emplace(s2.substr(0, k - 1));
        graph[s1].emplace(s3.substr(0, k - 1));
    }

    return graph;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int k, n;
    cin >> k;
    n = pow(2, k);

    const vector<string> cycle = makeEulerCycle(makeDeBruijnGraph(k, n));

    for (int i = 0; i < cycle.size() - 1; i++) {
        const auto &s = cycle[i];
        cout << s.substr(0, s.size() - (k - 2));
    }

    cout << endl;

    return 0;
}
