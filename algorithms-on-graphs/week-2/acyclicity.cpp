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

bool dfs(vvll& g, ll node, vector<bool>& visited) {
    visited[node] = true;

    bool ans = true;

    for (ll& next: g[node]) {
        if (visited[next] || !dfs(g, next, visited)) {
            ans = false;
            break;
        }
    }

    visited[node] = false;

    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    ll n, m, u, v;
    cin >> n >> m;

    vvll g(n + 1, vll());

    for (int i = 0; i < m; i++) {
        cin >> u >> v;
        g[u].push_back(v);
    }

    bool isAcyclic = true;
    vector<bool> visited(n + 1);

    for (ll i = 1; i <= n; i++) {
        if (!dfs(g, i, visited)) {
            isAcyclic = false;
            break;
        }
    }

    cout << int(!isAcyclic) << endl;

    return 0;
}