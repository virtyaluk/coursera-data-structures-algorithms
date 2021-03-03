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

struct HashFunction {
    long a, b, p, m;

    long operator()(long x) const noexcept {
        return ((a * x + b) % p) % m;
    }
};

struct SignFunction {
    static default_random_engine gen;
    static uniform_int_distribution<int> dist;

    HashFunction hf;

    SignFunction() noexcept: hf{ dist(gen), dist(gen), 10000019, 1000} {}

    int operator()(long x) const noexcept {
        return hf(x) > 500 ? 1 : -1;
    }
};

default_random_engine SignFunction::gen = default_random_engine();
uniform_int_distribution<int> SignFunction::dist = uniform_int_distribution<int>(10, 100);

struct Funcs {
    HashFunction hf;
    SignFunction sf;
};

struct CountSketch {
    CountSketch(long n) noexcept:
        b{ (int)log(n) * 50}, t{ (int) log(n) + 1}, data{ vector<vector<long>>(t, vector<long>(b)) }, ithData{ vector<long>(data.size()) } {
        default_random_engine gen;
        uniform_int_distribution<int> dist(3, 50);

        long p = 10e8 + 19;
        functions.reserve(data.size());

        for (auto i = 0; i < t; i++) {
            functions.push_back(Funcs{ HashFunction{ dist(gen), dist(gen), p, b }, SignFunction() });
        }
    }

    void update(long i, long frq = 1) noexcept {
        for (auto j = 0u; j < data.size(); j++) {
            data[j][functions[j].hf(i)] += (functions[j].sf(i) * frq);
        }
    }

    long estimate(long i) noexcept {
        for (auto j = 0u; j < data.size(); j++) {
            ithData[j] = data[j][functions[j].hf(i)] * functions[j].sf(i);
        }

        return median();
    }

private:
    const int b, t;
    vector<Funcs> functions;
    vector<vector<long>> data;
    vector<long> ithData;

    long median() noexcept {
        nth_element(begin(ithData), begin(ithData) + ithData.size() / 2, end(ithData));

        return *next(begin(ithData), ithData.size() / 2);
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    long n, t, id, val, q, query;
    cin >> n >> t;

    CountSketch countSketch(n);

    for (long i = 0; i < n; i++) {
        cin >> id >> val;
        countSketch.update(id, val);
    }

    for (long i = 0; i < n; i++) {
        cin >> id >> val;
        countSketch.update(id, -val);
    }

    cin >> q;

    for (long i = 0; i < q; i++) {
        cin >> query;
        printf("%c ", (countSketch.estimate(query) >= t) ? '1' : '0');
    }

    printf("\n");

    return 0;
}