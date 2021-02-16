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

struct Equation {
    vector<vector<double>> a;
    vector<double> b;
};

struct Position {
    short row, col;
};

const Position selectPivotElement(Position& pivot, const vector<vector<double>>& a, const vector<bool>& usedRows) {
    while (usedRows[pivot.row] || a[pivot.row][pivot.col] == 0) {
        pivot.row++;
    }

    return pivot;
}

void swapLines(vector<vector<double>>& a, vector<double>& b, vector<bool>& usedRows, Position& pivot) {
    swap(a[pivot.col], a[pivot.row]);
    swap(b[pivot.col], b[pivot.row]);
    swap(usedRows[pivot.col], usedRows[pivot.row]);
    pivot.row = pivot.col;
}

void processPivotElement(vector<vector<double>>& a, vector<double>& b, vector<bool>& usedRows, const Position& pivot) {
    double scale = a[pivot.row][pivot.col];

    if (scale != 1.0) {
        for (int i = 0; i < a.size(); i++) {
            a[pivot.row][i] /= scale;
        }

        b[pivot.row] /= scale;
    }

    for (int i = 0; i < a.size(); i++) {
        if (i != pivot.row) {
            double multiple = a[i][pivot.col];

            for (int j = 0; j < a.size(); j++) {
                a[i][j] -= a[pivot.row][j] * multiple;
            }

            b[i] -= b[pivot.row] * multiple;
        }
    }

    usedRows[pivot.row] = true;
}

vector<double> solveEquation(const Equation& eq) {
    vector<vector<double>> a = eq.a;
    vector<double> b = eq.b;
    int size = a.size();
    vector<bool> usedRows(size);

    for (short i = 0; i < size; i++) {
        Position pivot{0, i};
        pivot = selectPivotElement(pivot, a, usedRows);

        swapLines(a, b, usedRows, pivot);
        processPivotElement(a, b, usedRows, pivot);
    }

    return b;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    ll n;
    cin >> n;

    vector<vector<double>> a(n, vector<double>(n));
    vector<double> b(n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }

        cin >> b[i];
    }

    Equation eq{move(a), move(b)};
    const vector<double> solution = solveEquation(eq);

    cout.precision(10);
    copy(begin(solution), end(solution), ostream_iterator<double>(cout, " "));
    cout << endl;

    return 0;
}
