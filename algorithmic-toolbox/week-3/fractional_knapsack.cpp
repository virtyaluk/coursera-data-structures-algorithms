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

    ll n, W;
    cin >> n >> W;

    vector<pair<double, double>> vw;
    double ans;

    for (int i = 0; i < n; i++) {
        double v, w;
        cin >> v >> w;

        vw.push_back({v, w});
    }

    sort(vw.begin(), vw.end(), [](pair<double, double>& lhs, pair<double, double>& rhs) {
        return lhs.first / lhs.second > rhs.first / rhs.second;
    });

    for (pair<double, double>& item: vw) {
        if (W == 0) {
            break;
        }

        double amount = min((double) W, item.second);

        ans += item.first / item.second * amount;
        W -= amount;
    }

    cout.precision(10);
    cout << ans << endl;

    return 0;
}