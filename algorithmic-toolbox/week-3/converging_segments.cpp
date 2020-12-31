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

    vector<pair<ll, ll>> segments;

    for (int i = 0; i < n; i++) {
        ll a, b;
        cin >> a >> b;

        segments.push_back({a, b});
    }

    sort(segments.begin(), segments.end(), [](pair<ll, ll>& lhs, pair<ll, ll>& rhs) {
        return lhs.second < rhs.second;
    });

    ll point = segments[0].second;
    vll ans = {point};

    for (int i = 1; i < n; i++) {
        if (point < segments[i].first || point > segments[i].second) {
            point = segments[i].second;
            ans.push_back(point);
        }
    }

    cout << ans.size() << endl;
    copy(ans.begin(), ans.end(), ostream_iterator<ll>(cout, " "));
    cout << endl;

    return 0;
}