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

static constexpr auto K = 3;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    ll n, m, u, v;
    cin >> n >> m;

    vector<pair<ll, ll>> edges(m);

    for (ll i = 0; i < m; i++) {
        cin >> u >> v;
        edges[i] = {u, v};
    }

    ll C = K * m + n, V = n * K;

    printf("%d %d\n", C, V);

    for (ll j = 0, cnt = 1; j < n; j++, cnt += K) {
        printf("%d %d %d 0\n", cnt, cnt + 1, cnt + 2);
    }

    for (const pair<ll, ll>& e: edges) {
        ll from = e.first, to = e.second;

        printf("%d %d 0\n", -((from - 1) * K + 1), -((to - 1) * K + 1));
        printf("%d %d 0\n", -((from - 1) * K + 2), -((to - 1) * K + 2));
        printf("%d %d 0\n", -((from - 1) * K + 3), -((to - 1) * K + 3));
    }

    return 0;
}
