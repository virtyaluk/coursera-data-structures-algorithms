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

struct TrieNode {
    unordered_map<char, TrieNode*> children;
    bool isEndOfWord = false;
    ll pos;

    TrieNode(ll _pos): pos(_pos){}
};

class Trie {
private:
    TrieNode *root = nullptr;
    ll pos = 0;

public:
    Trie() {
        root = new TrieNode(pos++);
    }

    void insert(const string& s) {
        TrieNode *cur = root;

        for (const char& ch: s) {
            if (not cur->children.count(ch)) {
                cur->children[ch] = new TrieNode(pos++);
            }

            cur = cur->children[ch];
        }

        cur->isEndOfWord = true;
    }

    TrieNode* _getRoot() {
        return root;
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

    Trie *trie = new Trie();
    string s;

    for (ll i = 0; i < n; i++) {
        cin >> s;
        trie->insert(s);
    }

    queue<TrieNode*> q;
    q.push(trie->_getRoot());

    while (not q.empty()) {
        TrieNode *node = q.front();
        q.pop();

        for (auto it: node->children) {
            cout << (node->pos) << "->" << (it.second->pos) << ":" << it.first << '\n';

            q.push(it.second);
        }
    }

    return 0;
}