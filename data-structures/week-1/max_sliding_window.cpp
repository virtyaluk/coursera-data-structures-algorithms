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

    ll n, m;
    cin >> n;

    vll a, ans;
    copy_n(istream_iterator<ll>(cin), n, back_inserter(a));
    cin >> m;

    deque<int> q;

    for (int i = 0; i < n; i++) {
        if (!q.empty() && q.front() == i - m) {
            q.pop_front();
        }

        while (!q.empty() && a[i] >= a[q.back()]) {
            q.pop_back();
        }

        q.push_back(i);

        if (i >= m - 1) {
            ans.push_back(a[q.front()]);
        }
    }

    copy(ans.begin(), ans.end(), ostream_iterator<ll>(cout, " "));
    cout << endl;

    return 0;
}