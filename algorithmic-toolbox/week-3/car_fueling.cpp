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

    ll d, m, n, ans = 0;
    cin >> d >> m >> n;

    vll stop(n + 2);
    stop[n + 1] = d;

    for (int i = 1; i <= n; i++) {
        cin >> stop[i];
    }

    int curRefill = 0;

    while (curRefill <= n) {
        int lastRefill = curRefill;

        while (curRefill <= n && stop[curRefill + 1] - stop[lastRefill] <= m) {
            curRefill++;
        }

        if (curRefill == lastRefill) {
            ans = -1;
            break;
        }

        if (curRefill <= n) {
            ans++;
        }
    }

    cout << ans << endl;

    return 0;
}