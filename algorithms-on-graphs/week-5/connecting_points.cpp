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

class disjoint_set {
private:
    vector<ll> id, rank;
    ll size;

public:
    disjoint_set(ll n) {
        size = n;

        id.resize(n);
        rank.resize(n, 1);
        iota(id.begin(), id.end(), 0);
    }

    ll find(ll p) {
        ll root = p;
        //find the root
        while(root != id[root]) {
            root = id[root];
        }

        //perform path compression
        while(p != root) {
            ll newp = id[p];
            id[p] = root;
            p = newp;
        }

        return root;
    }

    bool merge(ll x, ll y) {
        x = find(x);
        y = find(y);

        if (x == y) {
            return false;
        }

        if (rank[x] > rank[y]) {
            id[y] = x;
        } else {
            id[x] = y;
        }

        if (rank[x] == rank[y]) {
            rank[y] += 1;
        }

        return true;
    }
};

double minDist(int& n, vector<tuple<int, int, double>>& edges) {
    int u, v;
    double w, ans = 0.0;
    disjoint_set ds(n);

    sort(edges.begin(), edges.end(), [](const tuple<int, int, double>& lhs, const tuple<int, int, double>& rhs) {
        return get<2>(lhs) < get<2>(rhs);
    });

    for (const auto& e: edges) {
        tie(u, v, w) = e;

        if (ds.find(u) != ds.find(v)) {
            ds.merge(u, v);
            ans += w;
        }
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int n, x, y;
    cin >> n;

    vector<pair<int, int>> points;

    for (int i = 0; i < n; i++) {
        cin >> x >> y;
        points.push_back({x, y});
    }

    vector<tuple<int, int, double>> edges;

    for (int i = 0; i < n; i++) {
        int x0 = points[i].first, y0 = points[i].second;

        for (int j = i + 1; j < n; j++) {
            int x = points[j].first, y = points[j].second;

            double dist = sqrt(pow((double) (x - x0), 2) + pow((double) (y - y0), 2));

            edges.push_back({i, j, dist});
        }
    }

    cout << setprecision(10) << minDist(n, edges);

    return 0;
}
