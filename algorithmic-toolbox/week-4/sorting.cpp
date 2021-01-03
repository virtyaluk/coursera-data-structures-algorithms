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

int partition2(vector<int> &a, int l, int r) {
    int x = a[l];
    int j = l;
    for (int i = l + 1; i <= r; i++) {
        if (a[i] <= x) {
            j++;
            swap(a[i], a[j]);
        }
    }
    swap(a[l], a[j]);
    return j;
}

pair<int, int> partition3(vector<int>& a, int l, int r) {
    int x = a[l], lo = l, hi = r, i = l;

    while (i <= hi) {
        if (a[i] < x) {
            swap(a[i++], a[lo++]);
        } else if (a[i] > x) {
            swap(a[i], a[hi--]);
        } else {
            i++;
        }
    }

    return {lo, hi};
}

void randomized_quick_sort(vector<int> &a, int l, int r) {
    if (l >= r) {
        return;
    }

    int k = l + rand() % (r - l + 1);
    swap(a[l], a[k]);
//    int m = partition2(a, l, r);
//
//    randomized_quick_sort(a, l, m - 1);
//    randomized_quick_sort(a, m + 1, r);

    pair<int, int> bounds = partition3(a, l, r);
    randomized_quick_sort(a, l, bounds.first - 1);
    randomized_quick_sort(a, bounds.second + 1, r);
}

int main() {
    int n;
    std::cin >> n;
    vector<int> a(n);
    for (size_t i = 0; i < a.size(); ++i) {
        std::cin >> a[i];
    }
    randomized_quick_sort(a, 0, a.size() - 1);
    for (size_t i = 0; i < a.size(); ++i) {
        std::cout << a[i] << ' ';
    }
    cout << endl;
}
