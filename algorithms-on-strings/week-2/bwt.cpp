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

string BWT(const string& text) {
    vector<string> m = {text};

    for (int i = 1; i < text.size(); i++) {
        m.push_back(text.substr(i) + text.substr(0, i));
    }

    sort(begin(m), end(m));

    return accumulate(begin(m), end(m), string(), [](string bwt, string mRow) {
        return bwt + "" + mRow.back();
    });
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    string text;
    cin >> text;

    cout << BWT(text) << endl;

    return 0;
}