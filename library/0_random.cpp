#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct dice {
  mt19937 mt;
  dice() : mt(chrono::steady_clock::now().time_since_epoch().count()) {}
  // [0, x)の一様乱数
  ll operator()(ll x) { return this->operator()(0, x); }
  // [x, y)の一様乱数
  ll operator()(ll x, ll y) {
    uniform_int_distribution<ll> dist(x, y - 1);
    return dist(mt);
  }
  vl operator()(int n, ll x, ll y) {
    vl res(n);
    for (int i = 0; i < n; i++) res[i] = this->operator()(x, y);
    return res;
  }
} rnd;

vii generate_random_tree(int n) {
    vi prufer(n - 2);
    rep (i, n - 2) prufer[i] = rnd(n);

    vector<bool> appear(n);
    rep (i, n - 2) appear[prufer[i]] = true;

    vii G(n);
    rep (i, n - 2) {
        int u = prufer[i];
        rep (i, n) {
            if (not appear[i]) {
                G[u].push_back(i);
                G[i].push_back(u);
                appear[i] = true;
                break;
            }
        }

        bool flag = false;
        for (int j = i + 1; j < n - 2; j++) {
            if (prufer[j] == u) {
                flag = true;
                break;
            }
        }
        if (not flag) appear[u] = false;
    }
    vi rem;
    rep (i, n) {
        if (not appear[i]) rem.push_back(i);
    }
    assert(rem.size() == 2);
    int u = rem[0], v = rem[1];
    G[u].push_back(v);
    G[v].push_back(u);
    return G;
}

int main() {
  for (int i = 0; i < 30; i++) {
    cout << rnd(10) << " ";
  }
  cout << endl;
  for (int i = 0; i < 30; i++) {
    cout << rnd(5, 10) << " ";
  }
  cout << endl;
}
