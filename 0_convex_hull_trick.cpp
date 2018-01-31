#include "bits/stdc++.h"
using namespace std;
     
#define DEBUG(x) cout<<#x<<": "<<x<<endl;
#define DEBUG_VEC(v) cout<<#v<<":";for(int i=0;i<v.size();i++) cout<<" "<<v[i]; cout<<endl
     
typedef long long ll;
#define vi vector<int>
#define vl vector<ll>
#define vii vector< vector<int> >
#define vll vector< vector<ll> >
#define vs vector<string>
#define pii pair<int,int>
#define pis pair<int,string>
#define psi pair<string,int>
#define pll pair<ll, ll>
const int inf = 1000000001;
const ll INF = 1e18;
#define MOD 1000000007
#define mod 1000000009
#define pi 3.14159265358979323846
#define Sp(p) cout<<setprecision(15)<<fixed<<p<<endl;
int dx[4] = { 1,0,-1,0 }, dy[4] = { 0,1,0,-1 };
int dx2[8] = { 1,1,0,-1,-1,-1,0,1 }, dy2[8] = { 0,1,1,1,0,-1,-1,-1 };

//追加される傾きaが単調減少、求めたい点xが単調増加の時のみ最小値を求められる。
template<typename T> class ConvexHullTrick {
  deque<pair<T, T> > lines;
  // 大小を判断する関数
  std::function<bool(T l, T r)> comp;
  
public:
  ConvexHullTrick(std::function<bool(T l, T r)> compFunc = [](T l, T r) {return l >= r; })
    :comp(compFunc)  {
  };

  // 直線l1, l2, l3のうちl2が不必要であるかどうか
  bool check(std::pair<T, T> l1, std::pair<T, T> l2, std::pair<T, T> l3) {
    if (l1 < l3) swap(l1, l3);
    return (l3.second - l2.second) * (l2.first - l1.first) >= (l2.second - l1.second) * (l3.first - l2.first);
  }

  // 直線y=ax+bを追加する
  void add(T a, T b) {
    std::pair<T, T> line(a, b);
    while (lines.size() >= 2 && check(*(lines.end() - 2), lines.back(), line))
      lines.pop_back();
    lines.push_back(line);
  }

  // i番目の直線f_i(x)に対するxの時の値を返す
  T f(int i, T x) {
    return lines[i].first * x + lines[i].second;
  }

  T get(T x) {
    // 最小値(最大値)クエリにおけるxが単調
    while (lines.size() >= 2 && comp(f(0, x), f(1, x)))
      lines.pop_front();
    return f(0, x);
  }
};

int main() {
  ll n, i, j;
  cin >> n;
  vl a(n);
  vl y00(n), k(n), b(n);
  for (i = 0; i < n; i++) {
    cin >> a[i];
  }
  for (i = 0; i < n; i++) {
    y00[i] = a[i] + i*i;
  }
  for (i = 0; i < n; i++) {
    k[i] = -1 - 2 * i;
  }
  for (i = 0; i < n; i++) {
    b[i] = 2 * i;
  }
  for (i = 1; i < n; i++) {
    b[i] = b[i - 1] + b[i];
  }

  ConvexHullTrick<ll> CHT;
  for (i = 0; i < n; i++) {
    CHT.add(k[i], y00[i]);
  }
  for (i = 0; i < n; i++) {
    cout << CHT.get(i) << endl;;
  }
  
  
}
