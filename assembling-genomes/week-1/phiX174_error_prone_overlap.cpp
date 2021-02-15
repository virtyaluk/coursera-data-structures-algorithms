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

constexpr int MAX_ERRORS = 2;

int calculate_overlap(const string & a, const string & b, const int mer) noexcept {
    for (int i = 0, n = 1 + a.size() - mer; i < n; ++i) {
        int errors = 0;

        for (int j = 0, s = a.size() - i; j < s && errors <= MAX_ERRORS; ++j) {
            if (a[i + j] != b[j]) {
                errors++;
            }
        }

        if (errors <= MAX_ERRORS) {
            return a.size() - i;
        }
    }

    return 0;
}

char get_most_frq(const vector<char> chars) {
    map<char, int> counts;

    for (auto c: chars) {
        counts[c]++;
    }

    pair<char, int> most_frq = *counts.begin();

    for (auto each: counts) {
        if (each.second > most_frq.second) {
            most_frq = each;
        }
    }

    return most_frq.first;
}

string assemble_genome(vector<string> reads, const int mer) noexcept {
    string genome;
    genome.reserve(1000);
    genome += reads.front();

    string first_read = reads.front(), cur_read = "";
    int cur_index = 0;

    while (reads.size() > 1) {
        cur_read = move(reads[cur_index]);
        reads.erase(reads.begin() + cur_index);

        int max_overlap = -1;

        vector<int> overlaps;
        vector<int> positions;

        for (int j = 0; j < reads.size(); ++j) {
            int overlap = calculate_overlap(cur_read, reads[j], mer);

            if (overlaps.empty() || overlap >= overlaps.back()) {
                overlaps.push_back(overlap);
                positions.push_back(j);
                cur_index = j;
            }
        }

        if (overlaps.size() > 3) {
            char *suffix = &genome[genome.size() - overlaps[overlaps.size() - 4]];
            char *prefix1 = &reads[positions[positions.size() - 4]][0];
            char *prefix2 = &reads[positions[positions.size() - 3]][
                    (overlaps[overlaps.size() - 3] - overlaps[overlaps.size() - 4])];
            char *prefix3 = &reads[positions[positions.size() - 2]][
                    (overlaps[overlaps.size() - 2] - overlaps[overlaps.size() - 4])];
            char *prefix4 = &reads[positions[positions.size() - 1]][
                    (overlaps[overlaps.size() - 1] - overlaps[overlaps.size() - 4])];

            for (int i = 0, n = overlaps[overlaps.size() - 4]; i < n; ++i,
                    ++suffix, ++prefix1, ++prefix2, ++prefix3, ++prefix4) {
                if (*suffix == *prefix1 && *prefix1 == *prefix2 &&
                    *prefix2 == *prefix3 && *prefix3 == *prefix4) {
                    continue;
                }

                const char c = get_most_frq({*suffix, *prefix1, *prefix2, *prefix3, *prefix4});
                *suffix = *prefix1 = *prefix2 = *prefix3 = *prefix4 = c;
            }
        }

        genome += reads[cur_index].substr(overlaps.back());
    }

    genome.erase(0, calculate_overlap(reads[0], first_read, mer));
    return genome;
}

int main () {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    vector <string> reads;
    reads.reserve(1618);
    string s;

    while (cin >> s) {
        reads.emplace_back(move(s));
    }

    random_device rd;
    mt19937 g(rd());

    shuffle(reads.begin(), reads.end(), g);

    cout << assemble_genome(move(reads), 12) << endl;

    return 0;
}
