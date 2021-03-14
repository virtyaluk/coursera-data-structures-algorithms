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

vi lastToFirst(const string& text) {
    unordered_map<char, int> counts = {{'$', 0}, {'A', 0}, {'C', 0}, {'G', 0}, {'T', 0}}, position;
    vi ans(text.size());
    int temp = -1;

    for (const char& ch: text) {
        counts[ch]++;
    }

    for (char t: "$ACGT") {
        temp += counts[t];
        position[t] = temp;
    }

    for (int i = text.size() - 1; i >= 0; i--) {
        ans[i] = position[text[i]];
        position[text[i]]--;
    }

    return ans;
}

string invertBWT(const string& text) {
    string ans = "$";
    int pos = 0;
    vi ltf = lastToFirst(text);

    for (int i = 0; i < text.size() - 1; i++) {
        ans += text[pos];
        pos = ltf[pos];
    }

    reverse(begin(ans), end(ans));

    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    string text;
    cin >> text;

    cout << invertBWT(text) << endl;

    return 0;
}