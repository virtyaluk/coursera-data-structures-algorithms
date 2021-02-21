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

enum class result {
    no_cycle,
    one_cycle,
    multiple_cycles
};

result check_Euler_cycle(const map<string, set<string>> graph) {
    for (auto &kv : graph) {
        if (kv.second.empty()) return result::no_cycle;
        if (kv.second.size() > 1) return result::multiple_cycles;
    }

    return result::one_cycle;
}

map<string, set<string>> construct_DeBruijn_graph(const vector<string>& reads, const int k) {
    map <string, set<string>> graph;

    for (const auto &read : reads) {
        for (size_t i = 0; i + k < read.size(); ++i) {
            graph[read.substr(i, k - 1)].emplace(read.substr(i + 2, k - 1));
            if (i + k + 1 < read.size()) graph[read.substr(i + 2, k - 1)];
        }
    }

    return graph;
}

int binary_search_k(const vector<string> reads, int l, int r) {
    while (r >= l) {
        int mid = l + (r - l) / 2;

        result res = check_Euler_cycle(construct_DeBruijn_graph(reads, mid));
        switch (res) {
            case result::one_cycle:
                return mid;
            case result::no_cycle:
                r = mid - 1;
                continue;
            case result::multiple_cycles:
                l = mid + 1;
                continue;
        }
    }

    throw logic_error{"optimal k not found"};
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    vector<string> reads;
    string s;

    while (cin >> s) {
        reads.emplace_back(move(s));
    }

    const int mer_size = 100;
    cout << binary_search_k(reads, 0, mer_size) << endl;

    return 0;
}
