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

double minDist(const vector<tuple<ll, ll, double>>& edges, ll n, ll k) {
    ll u, v, nEdges = 0;
    double w;
    disjoint_set ds(n);

    for (const tuple<ll, ll, double>& edge: edges) {
        tie(u, v, w) = edge;

        if (ds.find(u) != ds.find(v)) {
            if (nEdges == n - k) {
                return w;
            } else {
                nEdges++;

                ds.merge(u, v);
            }
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

    ll n, k, x, y;
    cin >> n;

    vector<pair<ll, ll>> points;

    for (int i = 0; i < n; i++) {
        cin >> x >> y;
        points.push_back({x, y});
    }

    cin >> k;

    ll x0, y0, x1, y1;
    vector<tuple<ll, ll, double>> edges;

    for (int i = 0; i < n; i++) {
        tie(x0, y0) = points[i];

        for (int j = i + 1; j < n; j++) {
            tie(x1, y1) = points[j];
            double dist = sqrt(pow((double) (x1 - x0), 2) + pow((double) (y1 - y0), 2));

            edges.push_back({i, j, dist});
        }
    }

    sort(begin(edges), end(edges), [](const tuple<ll, ll, double>& lhs, const tuple<ll, ll, double>& rhs) {
       return get<2>(lhs) < get<2>(rhs);
    });

    cout << setprecision(10) << minDist(edges, n, k);

    return 0;
}
