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

    ll n, k = 0;
    cin >> n;

    vll ans;

    for (int i = 1; i <= n; i++) {
        n -= i;

        if (n <= i) {
            ans.push_back(n + i);
        } else if (n == 0) {
            ans.push_back(i);
            break;
        } else {
            ans.push_back(i);
        }
    }

    cout << ans.size() << endl;
    copy(ans.begin(), ans.end(), ostream_iterator<ll>(cout, " "));
    cout << endl;

    return 0;
}