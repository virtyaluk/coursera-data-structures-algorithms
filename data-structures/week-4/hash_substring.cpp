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

ll hashf(string& s, ll prime, ll x) {
    ll hv = 0;

    for (int i = s.size() - 1; i >= 0; i--) {
        hv = (hv * x + s[i]) % prime;
    }

    return hv;
}

vll precomputeHashes(string& text, string& pattern, ll prime, ll x) {
    int t = text.size(), p = pattern.size();
    string s = text.substr(t - p, string::npos);
    vll h(t - p + 1);
    ll y = 1;

    h[t - p] = hashf(s, prime, x);

    for (int i = 1; i <= p; i++) {
        y = (y * x) % prime;
    }

    for (int i = t - p - 1; i >= 0; i--) {
        h[i] = (x * h[i + 1] + text[i] - y * text[i + p]) % prime;
    }

    return h;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    string text, pattern;
    cin >> pattern >> text;

    ll prime = 1000000007, x = 236;
    ll phash = hashf(pattern, prime, x);
    vll h = precomputeHashes(text, pattern, prime, x);
    vi ans;

    for (int i = 0; i < (text.size() - pattern.size() + 1); i++) {
        if (phash == h[i]) {
            ans.push_back(i);
        }
    }

    copy(ans.begin(), ans.end(), ostream_iterator<int>(cout, " "));
    cout << endl;

    return 0;
}