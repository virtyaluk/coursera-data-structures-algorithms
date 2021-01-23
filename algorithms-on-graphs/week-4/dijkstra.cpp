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

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    ll n, m, u, v, wi;
    cin >> n >> m;

//    vvll g(n + 1, vll());
    vector<vector<pair<ll, ll>>> w(n + 1);

    for (int i = 0; i < m; i++) {
        cin >> u >> v >> wi;
//        g[u].push_back(v);
        w[u].push_back({v, wi});
    }

    cin >> u >> v;

    priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> q;
    vll dist(n + 1, INT_MAX);

    dist[u] = 0;
    q.push({0, u});

    while (!q.empty()) {
        pair<ll, ll> node = q.top();
        q.pop();

        for (pair<ll, ll> next: w[node.second]) {
            ll curDist = dist[node.second] + next.second;

            if (curDist < dist[next.first]) {
                dist[next.first] = curDist;
                q.push({dist[next.first], next.first});
            }
        }
    }

    cout << (dist[v] == INT_MAX ? -1 : dist[v]) << endl;

    return 0;
}