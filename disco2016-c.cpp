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

#define N 300010
int n, k;
vi rank2(N + 1);
vi tmp(N + 1);

// (rank[i], rank[i + k]) と (rank[j], rank[j + k]) を比較
bool compare_sa(int i, int j) {
  if (rank2[i] != rank2[j]) return rank2[i] < rank2[j];
  else {
    int ri = i + k <= n ? rank2[i + k] : -1;
    int rj = j + k <= n ? rank2[j + k] : -1;
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
    rank2[i] = i < n ? s[i] : -1;
  }

  for (k = 1; k <= n; k *= 2) {
    sort(sa.begin(), sa.end(), compare_sa);

    //一旦tmpに次のランクを計算しそれをrankに移す
    tmp[sa[0]] = 0;
    for (int i = 1; i <= n; i++) {
      tmp[sa[i]] = tmp[sa[i - 1]] + (compare_sa(sa[i - 1], sa[i]) ? 1 : 0);
    }
    for (int i = 0; i <= n; i++) {
      rank2[i] = tmp[i];
    }
  }
  return sa;
}


int main() {
  string s;
  cin >> s;
  int m, i, j;
  cin >> m;
  int cnt = 0;
  for (i = 0; i < s.size(); i++) {
    if (s[i] != 'a') {
      cnt++;
    }
  }
  if (cnt <= m) {
    for (i = 0; i < s.size() - m; i++) {
      cout << 'a';
    }
    cout << endl;
    return 0;
  }

  cnt = 0;
  int cnt2 = 0;
  int idx = 0;
  for (i = 0; i < s.size(); i++) {
    if (s[i] != 'a') {
      cnt++;
      if (cnt == m) {
	break;
      }
    }
    else {
      for (; idx <= i; idx++) {
	if (s[idx] != 'a') {
	  s[idx] = 'a';
	  cnt2++;
	}
      }
    }
  }
  vi sa = construct_sa(s);
  vi revsa(sa.size());
  for (i = 0; i < sa.size(); i++) {
    revsa[sa[i]] = i;
  }
  int mjun = inf;
  int midx = 0;
  cnt -= cnt2;
  for (i = idx; i <= idx + cnt; i++) {
    if (mjun > revsa[i]) {
      mjun = revsa[i];
      midx = i;
    }
  }
  for (i = idx; i < midx; i++) {
    s[i] = 'a';
    cnt--;
  }
  for (i = 0; i < cnt; i++) {
    cout << 'a';
  }
  cout << s << endl;  
}
