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

ll bs(vll& a, ll num) {
    int lo = 0, hi = a.size() - 1;

    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;

        if (a[mid] == num) {
            return mid;
        } else if (num < a[mid]) {
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }

    return -1;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    ll n, k;
    cin >> n;

    vll a(n);

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    cin >> k;

    vll b(k);

    for (int i = 0; i < k; i++) {
        cin >> b[i];

        b[i] = bs(a, b[i]);
    }

    copy(b.begin(), b.end(), ostream_iterator<ll>(cout, " "));
    cout << endl;

    return 0;
}