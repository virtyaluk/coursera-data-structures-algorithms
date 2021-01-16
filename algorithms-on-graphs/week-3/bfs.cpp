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

    ll n, m, u, v;
    cin >> n >> m;

    vvll g(n + 1, vll());

    for (int i = 0; i < m; i++) {
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    cin >> u >> v;

    ll ans = -1, level = 0;
    vector<bool> visited(n + 1);
    queue<ll> q;
    q.push(u);

    while (!q.empty()) {
        bool found = false;

        for (int qlen = q.size(); qlen > 0; qlen--) {
            ll node = q.front();
            q.pop();

            if (node == v) {
                found = true;
                break;
            }

            visited[node] = true;

            for (ll& next: g[node]) {
                if (!visited[next]) {
                    q.push(next);
                }
            }
        }

        if (found) {
            ans = level;
            break;
        }

        level++;
    }

    cout << ans << endl;

    return 0;
}