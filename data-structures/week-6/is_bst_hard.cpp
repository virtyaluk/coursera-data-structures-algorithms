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

class Node {
private:
    int l, r;
    unordered_map<int, Node*> *m;
public:
    ll val;

    Node(ll v, int _l, int _r, unordered_map<int, Node*> *_m) {
        val = v;
        l = _l;
        r = _r;
        m = _m;
    }

    Node* left() {
        if (l == -1) {
            return nullptr;
        }

        return (*m)[l];
    }

    Node* right() {
        if (r == -1) {
            return nullptr;
        }

        return (*m)[r];
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    ll n, v;
    cin >> n;

    int l, r;
    bool isValid = true;
    unordered_map<int, Node*> m;

    for (int i = 0; i < n; i++) {
        cin >> v >> l >> r;

        m[i] = new Node(v, l, r, &m);
    }

    stack<tuple<ll, Node*, ll>> st;

    if (!m.empty()) {
        st.push({-LINF, m[0], LINF});
    }

    while (!st.empty()) {
        ll m = get<0>(st.top()), M = get<2>(st.top());
        Node *node = get<1>(st.top());

        st.pop();

        if (node->val < m || node->val >= M) {
            isValid = false;
            break;
        }

        if (node->left()) {
            st.push({m, node->left(), node->val});
        }

        if (node->right()) {
            st.push({node->val, node->right(), M});
        }
    }

    cout << (isValid ? "CORRECT" : "INCORRECT") << endl;

    return 0;
}