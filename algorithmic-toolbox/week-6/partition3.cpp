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

ll partition3(vll& v) {
    ll sum = accumulate(v.begin(), v.end(), 0), n = v.size();

    if (sum % 3 != 0 || n < 3) {
        return 0;
    }

    vvll dp(sum + 1, vll(n + 1));

    for (int i = 0; i <= sum; i++) {
        int c = 0;

        for (int j = 0; j <= n; j++) {
            if (i == 0) {
                dp[i][j] = 1;
            } else if (j == 0 && i != 0) {
                dp[i][j] = 0;
            } else if (v[j - 1] <= i) {
                dp[i][j] = (dp[i][j - 1] || dp[i - v[j - 1]][j - 1]);
            } else {
                dp[i][j] = dp[i][j - 1];
            }

            if (dp[i][j] == 1) {
                c++;
            }
        }

        if (i == sum / 3 && c > 1) {
            return 1;
        } else if (i == sum / 3) {
            return 0;
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

    ll n;
    cin >> n;

    vll v;
    copy_n(istream_iterator<ll>(cin), n, back_inserter(v));

    cout << partition3(v) << endl;

    return 0;
}