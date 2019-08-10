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




const int MAXN = 3010;

vl fact(MAXN);
vl rfact(MAXN);

ll mod_pow(ll x, ll p, ll M = MOD) {
  ll a = 1;
  while (p) {
    if (p % 2)
      a = a*x%M;
    x = x*x%M;
    p /= 2;
  }
  return a;
}

ll mod_inverse(ll a, ll M = MOD) {
  return mod_pow(a, M - 2, M);
}

void set_fact(ll n, ll M = MOD) {
  fact[0] = fact[1] = rfact[0] = rfact[1] = 1;
  for (ll i = 2; i <= n; i++) {
    fact[i] = i * fact[i - 1] % M;
    // rfact[i] = mod_inverse(fact[i], M);
  }
}

//http://drken1215.hatenablog.com/entry/2018/06/08/210000
//nが大きくfactが計算できないときのほかの計算方法について書いてある
ll nCr(ll n, ll r, ll M = MOD) {
  if (r > n) return 0;
  assert(fact[2] == 2);
  ll ret = fact[n];
  if (rfact[r] == 0) {
    rfact[r] = mod_inverse(fact[r], M);
  }
  ret = (ret*rfact[r]) % M;
  if (rfact[n - r] == 0) {
    rfact[n - r] = mod_inverse(fact[n - r], M);
  }
  ret = (ret*rfact[n - r]) % M;
  return ret;
}

ll nHr(ll n, ll r) {
  return nCr(n+r-1, r);
}

// 第二種スターリング数
// 互いに区別できるn個のものを区別のないk個のグループに分けるとき,その分け方はsecondStirling[n][k]
// ただし空のグループがあってはいけない
vll secondStirling(MAXN, vl(MAXN, 0));
void setSecondStirling(ll n, ll M = MOD) {
	secondStirling[0][0] = 1;
	rep1(i, n) {
		rep(j, i + 1) {
			if (j == i) {
				secondStirling[i][j] = 1;
			}
			else if (j == 0) {
				secondStirling[i][j] = 0;
			}
			else {
				secondStirling[i][j] = (secondStirling[i - 1][j - 1] + (ll)j*secondStirling[i - 1][j] % M) % M;
			}
		}
	}
}


// 分割数
// i個の違いに区別できない品物をjグループ以下に分割する方法part[i][j]
vll part(MAXN + 1, vl(MAXN + 1));
void setPartition(int n, ll M = MOD) {
  part[0][0] = 1;
  rep (i, n + 1) {
    rep1 (j, n) {
      if (i - j >= 0) {
        // 個数が0のグループがあるとき, iのj-1グループと同じ
        // ないとき, i - j のjグループと同じ(すべてのグループで個数を-=1する)
        part[i][j] = part[i - j][j] + part[i][j - 1];
      }
      else {
        part[i][j] = part[i][j - 1];
      }
      part[i][j] %= M;
    }
  }
}



int main() {
	ll n, m, i, j;
	cin >> n >> m;
	if (n < m) {
		cout << 0 << endl;
		return 0;
	}
	fact[0] = 1;
	for (i = 1; i <= m; i++) {
		fact[i] = (fact[i - 1] * i) % MOD;
	}
	for (i = 0; i <= m; i++) {
		if (i == 0)
			C[i] = 1;
		else
			C[i] = nCr(m, i);
	}
	ll ans = 0;
	int fugou = 1;
	for (i = 0; i < m; i++) {
		ans = (ans + fugou * ((C[i] * mod_pow(m - i, n, MOD)) % MOD)) % MOD;
		fugou *= (-1);
	}
	while (ans < 0) {
		ans += MOD;
	}
	cout << ans << endl;
}






