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

ll getFibN(ll n) {
    ll f1 = 0, f2 = 1, f;

    for (int i = 0; i < n - 1; ++i) {
        f = (f1 + f2) % 10;
        f1 = f2;
        f2 = f;
    }
    return f - 1;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    ll m, n;
    cin >> m >> n;

    n = (n + 2) % 60;
    m = (m + 1) % 60;

    ll a, b;

    if (n <= 1) {
        a = n - 1;
    } else {
        a = getFibN(n);
    }

    if (m <= 1) {
        b = m - 1;
    } else {
        b = getFibN(m);
    }

    if (a >= b) {
        cout << (a - b) << endl;
    } else {
        cout << (10 + a - b) << endl;
    }

    return 0;
}