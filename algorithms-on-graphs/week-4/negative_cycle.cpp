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

int negativeCycle(int& n, vvi& edges) {
    vi dist(n + 1, 1001);
    deque<int> negNodes;
    dist[1] = 0;

    for (int i = 0; i < n; i++) {
        for (const vector<int>& e: edges) {
             int u = e[0], v = e[1], wi = e[2];

            if (dist[v] > dist[u] + wi) {
                dist[v] = dist[u] + wi;

                if (i == n - 1) {
                    negNodes.push_back(v);
                }
            }
        }
    }

    return negNodes.empty() ? 0 : 1;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int n, m, u, v, wi;
    cin >> n >> m;

    vvi edges;

    for (int i = 0; i < m; i++) {
        cin >> u >> v >> wi;
        edges.push_back({u, v, wi});
    }

    cout << negativeCycle(n, edges) << endl;

    return 0;
}
