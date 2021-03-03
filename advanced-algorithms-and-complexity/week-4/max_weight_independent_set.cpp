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

struct vertex {
    int weight;
    vi children;
};

int computeMaxIndependentSet(const vector<vertex>& g, const int v, vi& s, const int parent) {
    if (s[v] == - 1) {
        if (g[v].children.empty()) {
            s[v] = g[v].weight;
        } else {
            auto m1 = g[v].weight;

            for (auto u: g[v].children) {
                if (u == parent) {
                    continue;
                }

                for (auto w: g[u].children) {
                    if (w != v) {
                        m1 += computeMaxIndependentSet(g, w, s, u);
                    }
                }
            }

            auto m0 = 0;

            for (auto u: g[v].children) {
                if (u != parent) {
                    m0 += computeMaxIndependentSet(g, u, s, v);
                }
            }

            s[v] = max(m1, m0);
        }
    }

    return s[v];
}

int solve(const vector<vertex>& g) noexcept {
    int size = g.size();

    if (size == 0) {
        return 0;
    }

    vi s(size, -1);

    return computeMaxIndependentSet(g, 0, s, -1);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int n, u, v;
    cin >> n;

    vector<vertex> g(n);

    for (int i = 0; i < n; i++) {
        cin >> g[i].weight;
    }

    for (int i = 1; i < n; i++) {
        cin >> u >> v;

        g[u - 1].children.emplace_back(v - 1);
        g[v - 1].children.emplace_back(u - 1);
    }

    cout << solve(g) << endl;

    return 0;
}