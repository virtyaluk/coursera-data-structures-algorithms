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

int treeHeight(vll& tree) {
    int n = tree.size(), root = -1;
    unordered_map<int, unordered_set<int>> um;
    function<int(int)> getTreeHeight;

    getTreeHeight = [&](int node) {
        int curHeight = 0;

        for (int next: um[node]) {
            curHeight = max(curHeight, getTreeHeight(next));
        }

        return curHeight + 1;
    };

    // [4, -1, 4, 1, 1]

    for (int i = 0; i < n; i++) {
        um[tree[i]].insert(i);
//        um[i].insert(tree[i]);

        if (tree[i] == -1) {
            root = i;
        }
    }

    return getTreeHeight(root);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    ll n;
    cin >> n;

    vll tree;
    copy_n(istream_iterator<ll>(cin), n, back_inserter(tree));

    cout << treeHeight(tree) << endl;

    return 0;
}