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

vi random_vector(int n, int mi, int ma) {
  vi a(n);
  for (int i = 0; i < n; i++) {
    a[i] = 
  }
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
