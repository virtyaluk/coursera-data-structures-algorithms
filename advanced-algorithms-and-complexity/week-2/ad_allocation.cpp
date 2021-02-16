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

const long double EPS = numeric_limits<long double>::epsilon();

enum class state { optimal,
    infeasible,
    unbounded
};
enum class method_phase {
    one,
    two
};

using matrix = vector<vector<long double> >;

using column = vector<long double>;
using row = vector<long double>;

struct position {
    short row;
    short column;
    bool is_optimal() { return row == -1 || column == -1; }
};

struct simplex_method {
    void debug_print() const {
        for (size_t i = 0; i < A.size(); ++i) {
            for (size_t j = 0; j < A[i].size(); ++j) {
                cout << fixed << setw(5) << setprecision(2) << A[i][j] << ' ';
            }

            cout << fixed << setw(5) << " | " << setprecision(2) << b[i] << endl;
        }

        for (const auto &v : c) {
            cout << setw(7) << v << ' ';
        }

        cout << " | " << b[b.size() - 2] << endl;

        if (phase == method_phase::one) {
            for (const auto &v : w) {
                cout << setw(5) << v << ' ';
            }

            cout << " | " << b.back() << endl;
        }
    }

    void handle_artficial_vars() {
        for (size_t i = 0, j = m + n; i < b.size() - 1; ++i, ++j) {
            if (b[i] < 0.0) {

                solusion_vars[i] = -2;
                A[i][j] = -1;

                b.back() += b[i];
                b[i] = -b[i];

                transform(A[i].begin(), A[i].end(), A[i].begin(), negate<long double>());

                for (int k = 0; k < n + m; ++k) {
                    w[k] += A[i][k];
                }
            }
        }

        transform(w.begin(), w.end(), w.begin(), negate<long double>());
    }

    void handle_slack_vars() {
        for (size_t i = 0; i < A.size(); ++i) {
            A[i][i + m] = 1;
        }
    }

    // find pivots and run eliminations to get optimal objective
    void Gauss_Jordam_eliminations(row &obj) {
        while (true) {
            position p = find_pivot(obj);

            if (p.is_optimal() || cur_solution == state::unbounded) {
                break;
            }

            solusion_vars[p.column] = p.row;

            scale_pivot(p);

            process_pivot(p, obj);
        }
    }

    void trim_table_from_avars() {
        c.resize(c.size() - n);
        b.pop_back();

        for (auto &r : A) {
            r.resize(r.size() - n);
        }
    }

    void phase_two() {
        phase = method_phase::two;
        trim_table_from_avars();
        Gauss_Jordam_eliminations(c);
    }

    void phase_one() {
        phase = method_phase::one;
        Gauss_Jordam_eliminations(w);
        cur_solution = double_equals_zero(b.back()) ? state::optimal : state::infeasible;
    }

    void prepare_table() {
        solusion_vars = vector<int>(A[0].size(), -1);
        transform(c.begin(), c.end(), c.begin(), negate<double>());
        handle_slack_vars();
        if (mc) {
            w = row(c.size());
            handle_artficial_vars();
        }
    }

    bool double_equals(double a, double b, double epsilon = 0.001) {
        return abs(a - b) < epsilon;
    }

    bool mixed_constraints() const {
        auto it = find_if(b.cbegin(), b.cend(), [](const long double& j) { return j < 0.0; });
        return it == b.cend() ? false : true;
    }

    pair<int, vector<long double> > read_optimal_solution() {
        vector<long double> result(m);

        for (int i = 0; i < m; ++i) {
            long double sum = 0.0;
            int k = 0;
            for (size_t j = 0; j < A.size(); ++j) {
                if (solusion_vars[j] >= 0.0)
                    sum += fabs(A[j][i]);
                if (double_equals(A[j][i], 1.0)) {
                    k = j;
                }
            }

            result[i] = (sum - 1.0 > EPS) ? 0.0 : b[k];
        }

        return {0, move(result)};
    }

    pair<int, vector<long double> > solve() {
        mc = mixed_constraints();

        prepare_table();

        if (mc) {
            phase_one();
            if (cur_solution == state::infeasible) {
                return {-1, {}};
            }
        }

        phase_two();

        if (cur_solution == state::unbounded) {
            return {1, {}};
        }

        return read_optimal_solution();
    }

    bool double_equals_zero(long double a, long double epsilon = 0.001) {
        return abs(a - 0.0) < epsilon;
    }

    position find_pivot(row &cw) {
        short i = 0, j = distance(cw.begin(), min_element(cw.begin(), cw.end()));
        long double ratio = numeric_limits<long double>::max() - 1;

        if (cw[j] >= 0.0) {
            return {-1, -1};
        }

        for (size_t k = 0; k < A.size(); ++k) {
            long double r = b[k] / A[k][j];
            if ((A[k][j] > 0.0 || A[k][j] < 0.0) && r - ratio < EPS && r > 0.0) {
                ratio = r;
                i = k;
            }
        }

        if (ratio == numeric_limits<long double>::max() - 1) {
            cur_solution = state::unbounded;
        }

        return {i, j};
    }

    void process_pivot(position p, row &w) {
        long double m{0.0};

        for (int i = 0, s = A.size(); i < s; ++i) {
            if (p.row != i && !double_equals_zero(A[i][p.column], EPS)) {

                m = A[i][p.column];

                for (size_t j = 0; j < A[i].size(); ++j) {
                    A[i][j] -= A[p.row][j] * m;
                }

                b[i] -= b[p.row] * m;
            }
        }

        if (phase == method_phase::one) {
            b[b.size() - 2] -= b[p.row] * c[p.column];
            b[b.size() - 1] -= b[p.row] * w[p.column];
            auto mw = w[p.column];
            auto cw = c[p.column];
            for (size_t i = 0; i < w.size(); ++i) {
                w[i] -= A[p.row][i] * mw;
                c[i] -= A[p.row][i] * cw;
            }
        } else {
            b[b.size() - 1] -= b[p.row] * c[p.column];
            auto cw = c[p.column];
            for (size_t i = 0; i < w.size(); ++i) {
                c[i] -= A[p.row][i] * cw;
            }
        }
    }

    void scale_pivot(position p) {
        auto d = A[p.row][p.column];
        b[p.row] /= d;
        for (auto &n : A[p.row]) {
            n /= d;
        }
    }

    int n, m;
    matrix A;
    vector<long double> b, c, w;
    vector<int> solusion_vars;
    state cur_solution;
    method_phase phase;
    bool mc;
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int n, m;
    cin >> n >> m;

    matrix A(n, vector<long double>(n + m + n, 0.0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> A[i][j];
        }
    }
    vector<long double> b(n + 2);
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }

    vector<long double> c(n + m + n);
    for (int i = 0; i < m; i++) {
        cin >> c[i];
    }

    simplex_method sm{n, m, move(A), move(b), move(c)};

    pair<int, vector<long double> > ans = sm.solve();

    switch (ans.first) {
        case -1:
            printf("No solution\n");
            break;
        case 0:
            printf("Bounded solution\n");
            for (int i = 0; i < m; i++) {
                printf("%.18Lf%c", ans.second[i], " \n"[i + 1 == m]);
            }
            break;
        case 1:
            printf("Infinity\n");
            break;
    }
    return 0;
}
