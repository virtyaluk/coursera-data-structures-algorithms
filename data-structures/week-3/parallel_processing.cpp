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

class myComparator
{
public:
    int operator() (const pair<int, ll>& lhs, const pair<int, ll>& rhs)
    {
        if (lhs.second == rhs.second) {
            return lhs.first > rhs.first;
        }

        return lhs.second > rhs.second;
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    ll n, m;
    cin >> n >> m;

    vll t;
    copy_n(istream_iterator<ll>(cin), m, back_inserter(t));

    priority_queue<pair<int, ll>, vector<pair<int, ll>>, myComparator> q;

    for (int i = 0; i < n; i++) {
        q.push({i, 0});
    }

    for (ll& ti: t) {
        pair<int, ll> w = q.top();
        q.pop();

        cout << w.first << " " << w.second << endl;
        q.push({w.first, w.second + ti});
    }

    return 0;
}