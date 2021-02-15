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

vvll makeResidualGraph(vvll& graph, ll& n, ll& m) {
    vvll residual(n + m + 2, vll(n + m + 2));

    for (ll i = 1; i < n + 1; i++) {
        residual[0][i] = 1;

        for (ll j = 0; j < m; j++) {
            residual[i][n + 1 + j] = graph[i - 1][j];
        }
    }

    for (ll k = n + 1; k < n + m + 1; k++) {
        residual[k].back() = 1;
    }

    return residual;
}

bool hasPath(vvll& graph, vll& path) {
    ll V = graph.size();
    vector<bool> visited(V);
    queue<ll> q;

    visited[0] = true;
    q.push(0);

    while (!q.empty()) {
        ll u = q.front();
        q.pop();

        if (u == V - 1) {
            return true;
        }

        for (ll i = 0; i < V; i++) {
            if (!visited[i] && graph[u][i] > 0) {
                q.push(i);
                visited[i] = true;
                path[i] = u;
            }
        }
    }

    return visited[V - 1];
}

vll maxFlow(vvll& graph, ll& n) {
    ll V = graph.size();
    vll path(V), matches(n, -1);

    iota(begin(path), end(path), 0);

    while (hasPath(graph, path)) {
        ll minFlow = INT_MAX, v = V - 1, u;

        while (v) {
            u = path[v];
            minFlow = min(minFlow, graph[u][v]);
            v = u;
        }

        v = V - 1;

        while (v) {
            u = path[v];
            graph[u][v] -= minFlow;
            graph[v][u] += minFlow;
            v = u;
        }
    }

    for (ll i = 0; i < V; i++) {
        if (graph[V - 1][i] == 1) {
            ll person = i - n, flight;

            for (ll j = 0; j < graph[i].size(); j++) {
                if (graph[i][j] == 1) {
                    flight = j;
                    break;
                }
            }

            matches[flight - 1] = person;
        }
    }

    return matches;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    ll n, m;
    cin >> n >> m;

    vvll graph(n, vll(m));

    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < m; j++) {
            cin >> graph[i][j];
        }
    }

    vvll residual = makeResidualGraph(graph, n, m);
    vll matches = maxFlow(residual, n);

    copy(begin(matches), end(matches), ostream_iterator<ll>(cout, " "));
    cout << endl;

    return 0;
}
