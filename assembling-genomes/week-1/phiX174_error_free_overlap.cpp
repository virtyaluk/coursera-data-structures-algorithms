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

int calculateOverlap(const string& a, const string& b, const int& mer) {
    for (int i = 0, n = 1 + a.size() - mer; i < n; i++) {
        if (strncmp(b.c_str(), a.c_str() + i, a.size() - i) == 0) {
            return a.size() - i;
        }
    }

    return 0;
}

string assembleGenome(vector<string> reads, const int mer) {
    string genome;
    genome.reserve(1000);
    genome += reads.front();
    string firstRead = reads.front(), curRead = "";
    int curIdx = 0;

    while (reads.size() > 1) {
        curRead = move(reads[curIdx]);
        reads.erase(reads.begin() + curIdx);

        int maxOverlap = -1;

        for (int j = 0; j < reads.size(); j++) {
            int overlap = calculateOverlap(curRead, reads[j], mer);

            if (overlap > maxOverlap) {
                maxOverlap = overlap;
                curIdx = j;
            }
        }

        genome += reads[curIdx].substr(maxOverlap);
    }

    genome.erase(0, calculateOverlap(reads[0], firstRead, mer));

    return genome;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    string s;
    vector<string> reads;
    reads.reserve(1618);

    while (cin >> s) {
        if (reads.back() != s) {
            reads.emplace_back(move(s));
        }
    }

    cout << assembleGenome(move(reads), 12) << endl;

    return 0;
}
