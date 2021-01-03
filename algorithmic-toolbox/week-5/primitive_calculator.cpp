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

    ll n;
    cin >> n;

    vll dp(pow(10, 6) + 1, INT_MAX);
    dp[0] = 0;
    dp[1] = 0;
    dp[2] = 1;
    dp[3] = 1;

    for (int i = 4; i <= n; i++) {
        ll cur = INT_MAX;
        cur = min(cur, dp[i - 1] + 1);

        if (i % 2 == 0) {
            cur = min(cur, dp[i / 2] + 1);
        }

        if (i % 3 == 0) {
            cur = min(cur, dp[i / 3] + 1);
        }

        dp[i] = cur;
    }

    cout << dp[n] << endl;

    ll j = n;
    vll ans;

    while (j >= 0 && j != 1) {
        ans.push_back(j);

        ll nextJ = j;

        if (dp[j - 1] < dp[j]) {
            nextJ = j - 1;
        }

        if (j % 2 == 0 && dp[j / 2] < dp[j]) {
            nextJ = j / 2;
        }

        if (j % 3 == 0 && dp[j / 3] < dp[j]) {
            nextJ = j / 3;
        }

        j = nextJ;
    }

    ans.push_back(1);

    copy(ans.rbegin(), ans.rend(), ostream_iterator<ll>(cout, " "));
    cout << endl;

    return 0;
}