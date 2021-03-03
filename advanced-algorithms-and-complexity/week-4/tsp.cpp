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

struct Node {
    int dist = INF, parent = 0;
};

struct TSP {
    const int N;
    vvi dist;
    vector<vector<Node>> C;

    TSP(vvi g): N(g.size()), C(vector<vector<Node>>(1 << N, vector<Node>(N))), dist(move(g)) {
        for (int k = 1; k < N; k++) {
            C[1 << k][k] = Node{dist[0][k], 0};
        }
    }

    pair<int, vi> optimalTour() noexcept {
        for (int s = 2; s < 1 << (N - 1); s++) {
            if (s & (s - 1)) {
                vi S = combinations(s);
                int bits = s * 2;

                for (auto k: S) {
                    int prev = bits ^ (1 << k);
                    Node minNode;

                    for (auto m: S) {
                        if (C[prev][m].dist + dist[m][k] < minNode.dist and k != m) {
                            minNode = Node{C[prev][m].dist + dist[m][k], m};
                        }
                    }

                    C[bits][k] = minNode;
                }
            }
        }

        return backtrackOptimal();
    }

    vi combinations(const int n) noexcept {
        vi combs;
        bitset<16> bset = n;

        for (auto k = 0u; k < bset.size(); k++) {
            if (bset[k]) {
                combs.emplace_back(k + 1);
            }
        }

        return combs;
    }

    pair<int, vi> backtrackOptimal() noexcept {
        Node minNode;
        int bits = (1 << N) - 2;

        for (int k = 1; k < N; k++) {
            if (minNode.dist > C[bits][k].dist + dist[k][0]) {
                minNode = Node{C[bits][k].dist + dist[k][0], k};
            }
        }

        if (minNode.dist == INF) {
            return {-1, {}};
        }

        pair<int, vi> optimalTour;

        optimalTour.second.reserve(N);
        optimalTour.first = minNode.dist;
        optimalTour.second.emplace_back(1);

        for (int i = 0; i < N - 1; i++) {
            optimalTour.second.emplace_back(minNode.parent + 1);
            minNode.parent = C[bits][minNode.parent].parent;
            bits = bits ^ (1 << (optimalTour.second.back() - 1));
        }

        return optimalTour;
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int n, m, u, v, w;
    cin >> n >> m;

    vvi g(n, vi(n, INF));

    for (int i = 0; i < m; i++) {
        cin >> u >> v >> w;
        --u, --v;
        g[u][v] = g[v][u] = w;
    }

    TSP tsp(g);
    const pair<int, vi> tour = tsp.optimalTour();

    printf("%d\n", tour.first);

    if (tour.first == -1) {
        return 0;
    }

    for (auto p: tour.second) {
        printf("%d ", p);
    }

    printf("\n");

    return 0;
}