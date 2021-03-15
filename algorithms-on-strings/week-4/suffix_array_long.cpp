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

vi sortChars(string s) {
    vi order(s.size());
    unordered_map<char, int> count = {{'$', 0}, {'A', 0}, {'C', 0}, {'G', 0}, {'T', 0}};
    vector<char> ele = {'$', 'A', 'C', 'G', 'T'};

    for (const char& ch: s) {
        count[ch]++;
    }

    for (int i = 1; i < 5; i++) {
        count[ele[i]] += count[ele[i - 1]];
    }

    for (int j = s.size() - 1; j >= 0; j--) {
        char ch = s[j];
        count[ch]--;
        order[count[ch]] = j;
    }

    return order;
}

vi computeCharClasses(string s, vi order) {
    vi charClass(s.size());

    for (int i = 1; i < s.size(); i++) {
        if (s[order[i]] == s[order[i - 1]]) {
            charClass[order[i]] = charClass[order[i - 1]];
        } else {
            charClass[order[i]] = charClass[order[i - 1]] + 1;
        }
    }

    return charClass;
}

vi sortDoubled(string s, int L, vi oldOrder, vi oldClass) {
    vi count(s.size()), newOrder(s.size());

    for (int i = 0; i < s.size(); i++) {
        count[oldClass[i]]++;
    }

    for (int i = 1; i < s.size(); i++) {
        count[i] += count[i - 1];
    }

    for (int j = s.size() - 1; j >= 0; j--) {
        int start = (oldOrder[j] - L + s.size()) % s.size();
        int cl = oldClass[start];
        count[cl]--;
        newOrder[count[cl]] = start;
    }

    return newOrder;
}

vi updateClasses(vi newOrder, vi oldClass, int L) {
    int n = newOrder.size();
    vi newClass(n);

    for (int i = 1; i < n; i++) {
        int cur = newOrder[i];
        int mid = (cur + L) % n;
        int prev = newOrder[i - 1];
        int midPrev = (prev + L) % n;

        if (oldClass[cur] == oldClass[prev] and oldClass[mid] == oldClass[midPrev]) {
            newClass[cur] = newClass[prev];
        } else {
            newClass[cur] = newClass[prev] + 1;
        }
    }

    return newClass;
}

vi buildSuffixArray(string s) {
    vi order = sortChars(s);
    vi klass = computeCharClasses(s, order);
    int L = 1;

    while (L < s.size()) {
        order = sortDoubled(s, L, order, klass);
        klass = updateClasses(order, klass, L);
        L = 2 * L;
    }

    return order;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    string text;
    cin >> text;

    vi suffixArray = buildSuffixArray(text);

    copy(begin(suffixArray), end(suffixArray), ostream_iterator<int>(cout, " "));
    cout << endl;

    return 0;
}