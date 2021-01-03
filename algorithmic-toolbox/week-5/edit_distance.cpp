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

    string str1, str2;
    cin >> str1 >> str2;

    ll m = str1.size() + 1, n = str2.size() + 1;
    vvll dp(m, vll(n));

    for (int i = 0; i < m; i++) {
        dp[i][0] = i;
    }

    for (int j = 0; j < n; j++) {
        dp[0][j] = j;
    }

    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            int diff = str1[i - 1] == str2[j - 1] ? 0 : 1;

            dp[i][j] = min({dp[i - 1][j] + 1, dp[i][j - 1] + 1, dp[i - 1][j - 1] + diff});
        }
    }

    cout << dp[m - 1][n - 1] << endl;

    return 0;
}