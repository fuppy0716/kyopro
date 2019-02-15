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
const int inf = 1000000001;
const ll INF = 1e16;
#define MOD 1000000007
#define mod 1000000009
#define pi 3.14159265358979323846
#define Sp(p) cout<<setprecision(15)<<fixed<<p<<endl;
int dx[4] = { 1,0,-1,0 }, dy[4] = { 0,1,0,-1 };
int dx2[8] = { 1,1,0,-1,-1,-1,0,1 }, dy2[8] = { 0,1,1,1,0,-1,-1,-1 };


template <typename T>
class SegmentTree {
public:
  using F = function<T(T&, T&)>;
  int n;
  vector<T > dat;
  T e; // 単位元
  F query_func;
  F update_func;

  SegmentTree (){}
  SegmentTree(vector<T> a, F query_func, F update_func, T e) :n(a.size()), query_func(query_func), update_func(update_func), e(e) {
    dat.resize(4 * n);
    init(0, 0, n, a);
  }

  void init(int k, int l, int r, vector<T> &a) {
    if (r - l == 1) {
      dat[k] = a[l];
    }
    else {
      int lch = 2 * k + 1, rch = 2 * k + 2;
      init(lch, l, (l + r) / 2, a);
      init(rch, (l + r) / 2, r, a);
      dat[k] = query_func(dat[lch], dat[rch]);
    }
  }

  //k番目の値をaに変更
  void update(int k, T a, int v, int l, int r) {
    if (r - l == 1) {
      dat[v] = update_func(dat[v], a);
    }
    else {
      if (k < (l + r) / 2)
        update(k, a, 2 * v + 1, l, (l + r) / 2);
      else {
        update(k, a, 2 * v + 2, (l + r) / 2, r);
      }
      dat[v] = query_func(dat[v * 2 + 1], dat[v * 2 + 2]);
    }
  }
    
  //[a,b)の最小値を求める
  //後ろのほうの引数は計算の簡単のための引数
  //kは接点の番号,l,rはその接点が[l,r)に対応していることを表す
  //従って、外からはquery(a,b,0,0,n)としてよぶ
  T query(int a, int b, int k, int l, int r) {
    if (r <= a || b <= l) {
      return e;
    }
    if (a <= l && r <= b) {
      return dat[k];
    }
    else {
      T ul = query(a, b, k * 2 + 1, l, (l + r) / 2);
      T ur = query(a, b, k * 2 + 2, (l + r) / 2, r);
      return query_func(ul, ur);
    }
  }
};


class SuffixArray {
public:
  string s;
  int n;
  vi sa;
  vi inv_sa;
  vi lcp;
  vi rnk;
  SegmentTree<int> seg_lcp;
  
  SuffixArray(string s):s(s), n(s.size()) {
    sa = construct_sa(s);
    inv_sa.resize(n + 1);
    rep (i, n + 1) inv_sa[sa[i]] = i;
    lcp = construct_lcp(s, sa);
    function<int(int, int)> f1 = [](int a, int b){return min(a, b);};
    seg_lcp = SegmentTree<int>(lcp, f1, f1, inf);
  }

  int get_lcp(int i, int j) {
    int sa_i = inv_sa[i], sa_j = inv_sa[j];
    if (sa_i > sa_j) swap(sa_i, sa_j);
    if (sa_j == sa_i + 1) return lcp[sa_i];
    else return seg_lcp.query(sa_i, sa_j, 0, 0, seg_lcp.n);
  }
  
  vi construct_sa(string s) {
    vi sa(n + 1);
    rnk.resize(n + 1);
    vi tmp(n + 1);
    //最初は一文字、ランクは文字コードにすれば良い
    for (int i = 0; i <= n; i++) {
      sa[i] = i;
      rnk[i] = i < n ? s[i] : -1;
    }

    for (int k = 1; k <= n; k *= 2) {
      auto compare_sa = [=](int i, int j) {
        if (rnk[i] != rnk[j]) return rnk[i] < rnk[j];
        else {
          int ri = i + k <= n ? rnk[i + k] : -1;
          int rj = j + k <= n ? rnk[j + k] : -1;
          return ri < rj;
        }
      };
      sort(sa.begin(), sa.end(), compare_sa);

      //一旦tmpに次のランクを計算しそれをrankに移す
      tmp[sa[0]] = 0;
      for (int i = 1; i <= n; i++) {
        tmp[sa[i]] = tmp[sa[i - 1]] + (compare_sa(sa[i - 1], sa[i]) ? 1 : 0);
      }
      for (int i = 0; i <= n; i++) {
        rnk[i] = tmp[i];
      }
    }
    return sa;
  }

  //文字列sとその接尾辞配列saを受け取り、高さ配列lcpを返す
  vi construct_lcp(string s, vi sa) {
    int n = s.length();
    vi lcp(n);
    for (int i = 0; i <= n; i++) rnk[sa[i]] = i;

    int h = 0;
    lcp[0] = 0;
    for (int i = 0; i < n; i++) {
      //文字列中での位置iの接尾辞と、接尾辞配列中でその一つ前の設備時のLCPを求める
      int j = sa[rnk[i] - 1];

      //hを先頭の分1減らし、後ろが一致しているだけ増やす
      if (h > 0) h--;
      for (; j + h < n && i + h < n; h++) {
        if (s[j + h] != s[i + h]) break;
      }

      lcp[rnk[i] - 1] = h;
    }
    return lcp;
  }
};
