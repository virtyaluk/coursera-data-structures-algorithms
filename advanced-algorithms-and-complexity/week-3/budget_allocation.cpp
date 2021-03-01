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

void solve(const vvi& a, const vi& b) {
    string clausesStream;
    int cnt = 0;
    bitset<3> combinations;

    for (int i = 0; i < a.size(); i++) {
        const vi& row = a[i];
        int n = count_if(begin(row), row.cend(), [](const int& num) {
           return num != 0;
        });

        for (int j = 0, s = pow(2, n); j < s; j++) {
            combinations = j;
            int sum = 0, comb = 0;

            for (const int& num: row) {
                if (num != 0 and combinations[comb++]) {
                    sum += num;
                }
            }

            if (sum > b[i]) {
                bool isClause = false;

                for (int k = 0, comb = 0; k < row.size(); k++) {
                    if (row[k] != 0) {
                        clausesStream += combinations[comb] ? (to_string(-(k + 1)) + ' ') : (to_string(k + 1) + ' ');
                        comb++;
                        isClause = true;
                    }
                }

                if (isClause) {
                    clausesStream += "0 \n";
                    cnt++;
                }
            }
        }
    }

    if (cnt == 0) {
        cnt++;
        clausesStream += "1 -1 0\n";
    }

    cout << cnt << " " << (a[0].size()) << endl;
    cout << clausesStream.c_str();
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    ll n, m;
    cin >> n >> m;

    vvi a(n, vi(m));
    vi b;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }

    copy_n(istream_iterator<int>(cin), n, back_inserter(b));

    solve(a, b);

    return 0;
}
