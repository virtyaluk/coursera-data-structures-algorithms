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
public:
    Node *left, *right, *parent;
    int key, size;
    char ch;

    Node(int k, int s, char c, Node *l, Node *r, Node *p): key(k), size(s), ch(c), left(l), right(r), parent(p) {}
};

class Rope {
private:
    Node* _root;
    string _s;
public:
    Rope(string s): _s(s) {
        for (int i = 0; i < s.size(); i++) {
            Node *node = new Node(i, 1, s[i], nullptr, nullptr, nullptr);
            _root = merge(_root, node);
        }
    }

    int getSize(Node *v) {
        if (!v) {
            return 0;
        }

        return v->size;
    }

    void update(Node *v) {
        if (!v) {
            return;
        }

        v->size = getSize(v->left) + getSize(v->right) + 1;

        if (v->left) {
            v->left->parent = v;
        }

        if (v->right) {
            v->right->parent = v;
        }
    }

    void smallRotate(Node *v) {
        Node *parent = v->parent, *grandparent, *m;

        if (!parent) {
            return;
        }

        grandparent = v->parent->parent;

        if (parent->left == v) {
            m = v->right;
            v->right = parent;
            parent->left = m;
        } else {
            m = v->left;
            v->left = parent;
            parent->right = m;
        }

        update(parent);
        update(v);

        v->parent = grandparent;

        if (grandparent) {
            if (grandparent->left == parent) {
                grandparent->left = v;
            } else {
                grandparent->right = v;
            }
        }
    }

    void bigRotate(Node *v) {
        if (v->parent->left == v && v->parent->parent->left == v->parent) {
            smallRotate(v->parent);
            smallRotate(v);
        } else if (v->parent->right == v && v->parent->parent->right == v->parent) {
            smallRotate(v->parent);
            smallRotate(v);
        } else {
            smallRotate(v);
            smallRotate(v);
        }
    }

    Node* splay(Node *v) {
        if (!v) {
            return nullptr;
        }

        while (v->parent) {
            if (!v->parent->parent) {
                smallRotate(v);
                break;
            }

            bigRotate(v);
        }

        return v;
    }

    Node* find(Node *root, int orderStat) {
        Node *v = root;
        int s;

        if (!v) {
            return nullptr;
        }

        if (!v->left) {
            s = 0;
        } else {
            s = getSize(v->left);
        }

        if (orderStat == s + 1) {
            return v;
        } else if (orderStat < s + 1) {
            return splay(find(v->left, orderStat));
        } else {
            return splay(find(v->right, orderStat - s - 1));
        }
    }

    tuple<Node*, Node*> split(Node *root) {
        if (!root) {
            return {root, nullptr};
        }

        Node *right = root, *left;
        left = right->left;
        right->left = nullptr;

        if (left) {
            left->parent = nullptr;
        }

        update(left);
        update(right);

        return {left, right};
    }

    Node* merge(Node *left, Node *right) {
        if (!left) {
            return right;
        }

        if (!right) {
            return left;
        }

        while (right->left) {
            right = right->left;
        }

        right = splay(right);
        right->left = left;

        update(right);

        return right;
    }

    vector<char> inOrder() {
        function<void(Node*)> inOrderHelper;
        vector<char> charResult;

        inOrderHelper = [&](Node* root) {
            if (!root) {
                return;
            }

            inOrderHelper(root->left);

            charResult.push_back(root->ch);

            inOrderHelper(root->right);

            return;
        };

        inOrderHelper(_root);

        return charResult;
    }

    string result() {
        string ans = "";

        for (char ch: inOrder()) {
            ans += ch;
        }

        return ans;
    }

    void process(int i, int j, int k) {
        i++;
        j++;
        k++;
        Node *res = find(_root, j + 1), *left, *right, *mid, *tmp, *tmp2;
        tie(left, right) = split(res);

        if (i == 1) {
            if (!res) {
                return;
            }

            tmp = find(right, k);

            if (tmp) {
                tie(mid, right) = split(tmp);
                left = merge(mid, left);
                _root = merge(left, right);
            } else {
                _root = merge(right, left);
            }
        } else {
            if (res) {
                tmp = find(left, i);

                if (!tmp) {
                    cout << "gotcha" << endl;
                }

                tie(left, mid) = split(tmp);
                left = merge(left, right);
                tmp2 = find(left, k);

                if (tmp2) {
                    tie(left, right) = split(tmp2);
                    left = merge(left, mid);
                    _root = merge(left, right);
                } else {
                    _root = merge(left, mid);
                }
            } else {
                tmp = find(_root, i);
                tie(left, right) = split(tmp);
                tmp2 = find(left, k);

                if (tmp2) {
                    tie(left, mid) = split(tmp2);
                    left = merge(left, right);
                    _root = merge(left, mid);
                } else {
                    _root = merge(left, right);
                }
            }
        }
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    string s;
    int q, i, j, k;
    cin >> s >> q;

    Rope rope(s);

    for (int p = 0; p < q; p++) {
        cin >> i >> j >> k;

        rope.process(i, j, k);
    }

    cout << rope.result() << endl;

    return 0;
}