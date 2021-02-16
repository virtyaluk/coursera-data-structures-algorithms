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

bool checkDegrees(const vll& in, const vll& out) {
    for (ll i = 0; i < in.size(); i++) {
        if (in[i] != out[i]) {
            return false;
        }
    }

    return true;
}

vll makeEulerCycle(vvll& g) {
    stack<ll> v;
    vll path;
    ll cur = 0;
    v.push(0);

    while (not v.empty()) {
        cur = v.top();

        if (not g[cur].empty()) {
            v.push(g[cur].back());
            g[cur].pop_back();
            continue;
        }

        path.push_back(cur);
        v.pop();
    }

    reverse(begin(path), end(path));
    path.pop_back();

    return path;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    ll n, m, u, v;
    cin >> n >> m;

    vvll g(n);
    vll in(n), out(n);

    for (ll i = 0; i < m; i++) {
        cin >> u >> v;
        g[--u].push_back(--v);
        in[v]++;
        out[u]++;
    }

    if (not checkDegrees(in, out)) {
        cout << 0 << endl;
        return 0;
    }

    const vll cycle = makeEulerCycle(g);

    cout << 1 << endl;

    for (const ll& vc: cycle) {
        cout << vc + 1 << " ";
    }

    cout << endl;

    return 0;
}
