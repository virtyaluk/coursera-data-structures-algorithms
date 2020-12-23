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

ll pisano(ll m) {
    ll f1 = 0, f2 = 1, f = f1 + f2;

    for (int i = 0; i < m * m; i++) {
        f = (f1 + f2) % m;
        f1 = f2;
        f2 = f;

        if (f1 == 0 && f2 == 1) {
            return i + 1;
        }
    }

    return 0;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    ll n, m;
    cin >> n >> m;

    n %= pisano(m);
    ll f1 = 0, f2 = 1, f = n;

    for (int i = 1; i < n; i++) {
        f = (f1 + f2) % m;
        f1 = f2;
        f2 = f;
    }

    cout << f % m << endl;

    return 0;
}