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

#define N 20010
int n, k;
vi rnk(N + 1);
vi tmp(N + 1);

// (rank[i], rank[i + k]) と (rank[j], rank[j + k]) を比較
bool compare_sa(int i, int j) {
  if (rnk[i] != rnk[j]) return rnk[i] < rnk[j];
  else {
    int ri = i + k <= n ? rnk[i + k] : -1;
    int rj = j + k <= n ? rnk[j + k] : -1;
    return ri < rj;
  }
}

// 文字列sの接尾辞配列を構築、ダブリングの原理
vi construct_sa(string s) {
  n = s.size();
  vi sa(n + 1);
  //最初は一文字、ランクは文字コードにすれば良い
  for (int i = 0; i <= n; i++) {
    sa[i] = i;
    rnk[i] = i < n ? s[i] : -1;
  }

  for (k = 1; k <= n; k *= 2) {
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
