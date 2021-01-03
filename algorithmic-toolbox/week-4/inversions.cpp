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

ll countMerge(vll& a, vll& b, ll lo, ll mid, ll hi) {
    ll ans = 0, i = lo, j = mid + 1, k = lo;

    while (i <= mid && j <= hi) {
        if (a[i] <= a[j]) {
            b[k++] = a[i++];
        } else {
            b[k++] = a[j++];
            ans += mid - i + 1;
        }
    }

    while (i <= mid) {
        b[k++] = a[i++];
    }

    for (int i = lo; i <= hi; i++) {
        a[i] = b[i];
    }

    return ans;
}

ll countMergeAndSort(vll& a, vll& b, ll lo, ll hi) {
    ll ans = 0;

    if (lo < hi) {
        ll mid = lo + (hi - lo) / 2;

        ans += countMergeAndSort(a, b, lo, mid);
        ans += countMergeAndSort(a, b, mid + 1, hi);
        ans += countMerge(a, b, lo, mid, hi);
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    ll n;
    cin >> n;

    vll a, b;

    copy_n(istream_iterator<ll>(cin), n, back_inserter(a));
    b = a;

    cout << countMergeAndSort(a, b, 0, n - 1) << endl;

    return 0;
}