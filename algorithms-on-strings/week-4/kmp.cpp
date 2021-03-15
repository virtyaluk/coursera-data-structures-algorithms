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

vi prefixFunction(const string& text) {
    vi s(text.size());
    int border = 0;

    for (int i = 1; i < text.size(); i++) {
        while (border > 0 and text[i] != text[border]) {
            border = s[border - 1];
        }

        if (text[i] == text[border]) {
            border++;
        } else {
            border = 0;
        }

        s[i] = border;
    }

    return s;
}

vi KMP(const string& text, const string pattern) {
    string s = pattern + "$" + text;
    vi pres = prefixFunction(s), res;

    for (int i = pattern.size() + 1; i < s.size(); i++) {
        if (pres[i] == pattern.size()) {
            res.push_back(i - 2 * pattern.size());
        }
    }

    return res;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    string pattern, text;
    cin >> pattern >> text;

    vi positions = KMP(text, pattern);

    copy(begin(positions), end(positions), ostream_iterator<int>(cout, " "));
    cout << endl;

    return 0;
}