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
    int val;

    Node(int v, int _l, int _r, unordered_map<int, Node*> *_m) {
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

    ll n;
    cin >> n;

    int v, l, r;
    vi in, pre, post;
    unordered_map<int, Node*> m;
    Node *head = nullptr;

    for (int i = 0; i < n; i++) {
        cin >> v >> l >> r;

        Node *node = new Node(v, l, r, &m);
        m[i] = node;

        if (!head) {
            head = node;
        }
    }

    // in-order
    stack<Node*> st;
    Node *cur = head;

    while (!st.empty() || cur != nullptr) {
        if (cur != nullptr) {
            st.push(cur);
            cur = cur->left();
        } else {
            cur = st.top();
            st.pop();

            in.push_back(cur->val);

            cur = cur->right();
        }
    }

    // pre-order
    st = {};
    st.push(head);

    while (!st.empty()) {
        cur = st.top();
        st.pop();

        pre.push_back(cur->val);

        if (cur->right()) {
            st.push(cur->right());
        }

        if (cur->left()) {
            st.push(cur->left());
        }
    }

    // post-order
    st = {};
    st.push(head);

    while (!st.empty()) {
        cur = st.top();
        st.pop();

        post.push_back(cur->val);

        if (cur->left()) {
            st.push(cur->left());
        }

        if (cur->right()) {
            st.push(cur->right());
        }
    }

    reverse(post.begin(), post.end());

    copy(in.begin(), in.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
    copy(pre.begin(), pre.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
    copy(post.begin(), post.end(), ostream_iterator<int>(cout, " "));
    cout << endl;

    return 0;
}