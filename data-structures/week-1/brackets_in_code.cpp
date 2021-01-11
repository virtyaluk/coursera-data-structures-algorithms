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

string findMismatch(string s) {
    stack<pair<char, int>> st;
    ll ans;

    for (int i = 0; i < s.size(); i++) {
        char ch = s[i];

        if (ch == '(' || ch == '{' || ch == '[') {
            st.push({ch, i});
        } else if (ch == ')' || ch == '}' || ch == ']') {
            if (st.empty()) {
                return to_string(i + 1);
            }

            char top = st.top().first;
            st.pop();

            if ((top == '(' && ch != ')') || (top == '{' && ch != '}') || (top == '[' && ch != ']')) {
                return to_string(i + 1);
            }
        }
    }

    if (!st.empty()) {
        return to_string(st.top().second + 1);
    }

    return "Success";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    string s;
    cin >> s;

    cout << findMismatch(s) << endl;

    return 0;
}