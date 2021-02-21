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
//const int INF = 1e9;
const ll LINF = 1e18;

using Point = pair<double, double>;
using Length = long long;
using Edge = pair<long long, int>;
using Adj_List = vector<vector<Edge>>;
using Distance = vector<Length>;
using Queue = priority_queue<Edge, vector<Edge>, greater<Edge>>;

Length INF = std::numeric_limits<Length>::max() / 4;

class Graph {
    Adj_List adj;
    Distance dist;
    vector<int> workset;
    vector <Point> coords;
    int t_{0}, s_{0};

    Length compute_path() noexcept;

    Length potential(int s, int t) noexcept;

    inline void relax(Queue &, Length, int, int) noexcept;

    void clear_workset() noexcept;

public:
    Graph(int n) noexcept: adj(Adj_List(n, vector<Edge>())), dist(vector<Length>(n, INF)) {};

    Length Astar(int s, int t) noexcept;

    void add_edge(int u, int v, int w) noexcept;

    void add_coords(int x, int y) noexcept;
};

Length Graph::potential(int s, int t) noexcept {
    return sqrt((coords[s].first - coords[t].first) * (coords[s].first - coords[t].first) +
                (coords[s].second - coords[t].second) * (coords[s].second - coords[t].second));
}

void Graph::clear_workset() noexcept {
    for (auto &u: workset)
        dist[u] = INF;
    workset.clear();
}

void Graph::add_coords(int x, int y) noexcept {
    coords.push_back(Point(x, y));
}

void Graph::add_edge(int u, int v, int w) noexcept {
    adj[u].push_back(Edge(w, v));
}

void Graph::relax(Queue& queue, Length weight, int v, int u) noexcept {
    auto dist_u_weight = dist[u] + weight - potential(u, t_) + potential(v, t_);
    if (dist[v] > dist_u_weight) {
        dist[v] = dist_u_weight;
        queue.push(Edge(dist[v], v));
        workset.push_back(v);
    }
}

Length Graph::Astar(int s, int t) noexcept {
    clear_workset();
    s_ = s, t_ = t;

    Queue queue;
    queue.push(Edge(0, s));
    dist[s] = 0;
    workset.push_back(s);

    while (!queue.empty()) {
        int u = queue.top().second;
        queue.pop();

        if (u == t)
            break;

        for (auto &edge: adj[u])
            relax(queue, edge.first, edge.second, u);
    }

    return dist[t] == INF ? -1 : dist[t] + potential(s_, t_);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int n, m, s, t, q;
    cin >> n >> m;
    Graph g(n);

    for (int i = 0; i < n; i++) {
        int x, y;
        std::cin >> x >> y;
        g.add_coords(x, y);
    }

    for (int i = 0; i < m; i++) {
        int x, y, w;
        std::cin >> x >> y >> w;
        g.add_edge(x - 1, y - 1, w);
    }

    std::cin >> q;
    while (q--) {
        std::cin >> s >> t;
        cout << g.Astar(s - 1, t - 1) << endl;
    }

    return 0;
}
