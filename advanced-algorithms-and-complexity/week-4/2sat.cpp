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

struct solver_2SAT {
    struct util {
        util(): index{MIN}, lowlink{MIN}, id{-1}, on_stack{false} {}

        int index, lowlink, id;
        bool on_stack;
        vector<int> edges;
    };

    solver_2SAT(unordered_map<int, util> adj_lst_graph, int num_of_vars): n{num_of_vars}, graph{move(adj_lst_graph)}, sol{vector<bool>(n, false)} {}

    void process_vertex(int v) {
        auto &utl = graph[v];

        utl.lowlink = utl.index = t++;
        utl.on_stack = true;
        stk.push(v);

        for (auto w : utl.edges) {
            if (graph[w].index == MIN) {
                process_vertex(w);
                utl.lowlink = min(utl.lowlink, graph[w].lowlink);
            } else if (graph[w].on_stack) {
                utl.lowlink = min(utl.lowlink, graph[w].index);
            }
        }

        if (utl.lowlink == utl.index) {
            do {
                w = stk.top();
                stk.pop();

                if (id == graph[-w].id) {
                    sat = false;
                    return;
                }

                auto &w_utl = graph[w];
                w_utl.on_stack = false;
                w_utl.id = id;

                sol[abs(w) - 1] = w < 0 ? true : false;

            } while (w != v);
            ++id;
        }
    }

    void solve() {
        for (int i = -n; i <= n; ++i) {
            if (graph[i].index == MIN && i != 0) {
                process_vertex(i);
            }
        }
    }

    void print_solution() const noexcept {
        if (!sat) {
            printf("%s\n", "UNSATISFIABLE\0");
            return;
        }

        printf("%s\n", "SATISFIABLE\0");
        for (unsigned int i = 0, s = sol.size(); i < s; ++i) {
            printf("%d ", (sol[i] ? i + 1 : -(i + 1)));
        }

        printf("\n");
    }

    int t{0}, id{0}, w{0}, n{0};

    unordered_map<int, util> graph;
    vector<bool> sol;
    stack<int> stk;

    bool sat{true};

    static constexpr int MIN = numeric_limits<int>::min();
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int n, m;
    cin >> n >> m;

    unordered_map<int, solver_2SAT::util> adj_lst_graph(n * 2);

    for (int i = 0, x, y; i < m; ++i) {
        cin >> x >> y;
        adj_lst_graph[-x].edges.emplace_back(y);
        adj_lst_graph[-y].edges.emplace_back(x);
    }

    solver_2SAT solver(move(adj_lst_graph), n);
    solver.solve();
    solver.print_solution();

    return 0;
}