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

bool hasPath(vvll& graph, ll& n, vll& path) {
    vector<bool> visited(n);
    queue<ll> q;

    visited[0] = true;
    q.push(0);

    while (!q.empty()) {
        ll tmp = q.front();
        q.pop();

        if (tmp == n - 1) {
            return true;
        }

        for (ll i = 0; i < n; i++) {
            if (!visited[i] && graph[tmp][i] > 0) {
                q.push(i);
                visited[i] = true;
                path[i] = tmp;
            }
        }
    }

    return visited[n - 1];
}

ll maxFlow(vvll& graph, ll& n) {
    ll flow = 0;
    vll path(n);

    iota(begin(path), end(path), 0);

    while (hasPath(graph, n, path)) {
        ll minFlow = INT_MAX, v = n - 1, u;

        while (v) {
            u = path[v];
            minFlow = min(minFlow, graph[u][v]);
            v = u;
        }

        v = n - 1;

        while (v) {
            u = path[v];
            graph[u][v] -= minFlow;
            graph[v][u] += minFlow;
            v = u;
        }

        flow += minFlow;
    }

    return flow;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    ll n, m, u, v, c;
    cin >> n >> m;

    vvll graph(n, vll(n));

    for (ll i = 0; i < m; i++) {
        cin >> u >> v >> c;
        graph[u - 1][v - 1] += c;
    }

    cout << maxFlow(graph, n) << endl;

    return 0;
}
