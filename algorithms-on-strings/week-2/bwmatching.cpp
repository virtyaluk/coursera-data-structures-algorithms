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

pair<unordered_map<char, int>, unordered_map<char, vi>> process(const string& text) {
    unordered_map<char, int> freq = {{'$', 0}, {'A', 0}, {'C', 0}, {'G', 0}, {'T', 0}}, firstOccur = {{'$', 0}};
    unordered_map<char, vi> count;
    vector<char> ele = {'$', 'A', 'C', 'G', 'T'};

    for (const char& ch: text) {
        freq[ch]++;
    }

    for (int i = 1; i < 5; i++) {
        firstOccur[ele[i]] = firstOccur[ele[i - 1]] + freq[ele[i - 1]];
    }

    for (char e: ele) {
        count[e].assign(text.size() + 1, 0);
    }

    for (int i = 0; i < text.size(); i++) {
        unordered_map<char, int> temp = {{text[i], 1}};

        for (char e: ele) {
            count[e][i + 1] = count[e][i] + (temp.find(e) == temp.end() ? 0 : temp[e]);
        }
    }

    return {firstOccur, count};
}

int BWmatching(const string& text, string pattern, unordered_map<char, int>& firstOccur, unordered_map<char, vi>& count) {
    int top = 0, bottom = text.size() - 1;

    while (top <= bottom) {
        if (not pattern.empty()) {
            char symb = pattern.back();
            pattern = pattern.substr(0, pattern.size() - 1);
            top = firstOccur[symb] + count[symb][top];
            bottom = firstOccur[symb] + count[symb][bottom + 1] - 1;
        } else {
            return bottom - top + 1;
        }
    }

    return 0;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    string text, pattern;
    int n;
    cin >> text;
    cin >> n;

    pair<unordered_map<char, int>, unordered_map<char, vi>> pres = process(text);

    for (int i = 0; i < n; i++) {
        cin >> pattern;

        cout << BWmatching(text, pattern, pres.first, pres.second) << " ";
    }

    cout << endl;

    return 0;
}