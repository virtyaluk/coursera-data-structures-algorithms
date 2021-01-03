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

    ll s, p;
    cin >> s >> p;

    vector<pair<ll, char>> segments;
    vll points(p), ans;

    for (int i = 0; i < s; i++) {
        ll a, b;
        cin >> a >> b;
        segments.push_back({a, 'l'});
        segments.push_back({b, 'r'});
    }

    for (int i = 0; i < p; i++) {
        cin >> points[i];
        segments.push_back({points[i], 'p'});
    }

    sort(segments.begin(), segments.end(), [](pair<ll, char>& lhs, pair<ll, char>& rhs) {
        if (lhs.first != rhs.first) {
            return lhs.first < rhs.first;
        } else {
            return lhs.second < rhs.second;
        }
    });

    int count = 0;
    unordered_map<int, int> m;

    for (pair<ll, char> seg: segments) {
        if (seg.second == 'l') {
            count++;
        } else if (seg.second == 'r') {
            count--;
        } else {
            m[seg.first] = count;
        }
    }

    for (int p: points) {
        ans.push_back(m[p]);
    }

    copy(ans.begin(), ans.end(), ostream_iterator<ll>(cout, " "));
    cout << endl;

    return 0;
}