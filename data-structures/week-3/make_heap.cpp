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

void siftDown(vll& a, vector<pair<int, int>>& swaps, int i) {
    int minIdx = i, left = 2 * i + 1, right = 2 * i + 2;

    if (left < a.size() && a[left] < a[minIdx]) {
        minIdx = left;
    }

    if (right < a.size() && a[right] < a[minIdx]) {
        minIdx = right;
    }

    if (minIdx != i) {
        swaps.push_back({i, minIdx});
        swap(a[i], a[minIdx]);
        siftDown(a, swaps, minIdx);
    }
}

void buildHeap(vll& a, vector<pair<int, int>>& swaps) {
    int n = a.size();

    for (int i = n / 2; i >= 0; i--) {
        siftDown(a, swaps, i);
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    ll n;
    cin >> n;

    vector<pair<int, int>> swaps;
    vll a;
    copy_n(istream_iterator<ll>(cin), n, back_inserter(a));

    buildHeap(a, swaps);

    cout << swaps.size() << endl;

    for (pair<int, int>& swap: swaps) {
        cout << swap.first << " " << swap.second << endl;
    }

    return 0;
}