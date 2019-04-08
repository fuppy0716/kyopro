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
#define pll pair<ll,ll>
#define fi first
#define se second
#define rep(i,n) for(int i=0;i<(int)(n);i++)
#define rep1(i,n) for(int i=1;i<=(int)(n);i++)
#define all(c) c.begin(),c.end()
const int inf = 1000000001;
const ll INF = 2e18 * 2;
#define MOD 1000000007
#define mod 1000000009
#define pi 3.14159265358979323846
#define Sp(p) cout<<setprecision(15)<< fixed<<p<<endl;
int dx[4] = { 1,0,-1,0 }, dy[4] = { 0,1,0,-1 };
int dx2[8] = { 1,1,0,-1,-1,-1,0,1 }, dy2[8] = { 0,1,1,1,0,-1,-1,-1 };

typedef complex<double> P;

vector<P> fft(vector<P> v, bool rev = false) {
	int n = v.size(), i, j, m;

	for (i = 0, j = 1; j<n - 1; j++) {
		for (int k = n >> 1; k>(i ^= k); k >>= 1);
		if (i>j) swap(v[i], v[j]);
	}
	for (int m = 2; m <= n; m *= 2) {
		double deg = (rev ? -1 : 1) * 2 * acos(-1) / m;
		P wr(cos(deg), sin(deg));
		for (i = 0; i<n; i += m) {
			P w(1, 0);
			for (int j1 = i, j2 = i + m / 2; j2<i + m; j1++, j2++) {
				P t1 = v[j1], t2 = w*v[j2];
				v[j1] = t1 + t2, v[j2] = t1 - t2;
				w *= wr;
			}
		}
	}
	if (rev) rep(i, n) v[i] *= 1.0 / n;
	return v;
}

vector<P> MultPoly(vector<P> a, vector<P> b) {
  // 前処理あり, main関数を読んで!
	a = fft(a), b = fft(b);
	for (int i = 0; i<a.size(); i++) a[i] *= b[i];
	return fft(a, true);
}




template< int mod, int primitiveroot >
struct NTT {
  vector< vector< int > > rts, rrts;
  void ensure_base(int N) {
    if(rts.size() >= N) return;
    rts.resize(N), rrts.resize(N);
    for(int i = 1; i < N; i <<= 1) {
      if(rts[i].size()) continue;
      int w = mod_pow(primitiveroot, (mod - 1) / (i * 2));
      int rw = inverse(w);
      rts[i].resize(i), rrts[i].resize(i);
      rts[i][0] = 1, rrts[i][0] = 1;
      for(int k = 1; k < i; k++) {
        rts[i][k] = mul(rts[i][k - 1], w);
        rrts[i][k] = mul(rrts[i][k - 1], rw);
      }
    }
  }

  inline int mod_pow(int x, int n) {
    int ret = 1;
    while(n > 0) {
      if(n & 1) ret = mul(ret, x);
      x = mul(x, x);
      n >>= 1;
    }
    return ret;
  }

  inline int inverse(int x) {
    return mod_pow(x, mod - 2);
  }

  inline int add(int x, int y) {
    x += y;
    if(x >= mod) x -= mod;
    return x;
  }

  inline int mul(int a, int b) {
    return int(1LL * a * b % mod);
  }

  void DiscreteFourierTransform(vector< int > &F, bool rev) {
    const int N = (int) F.size();
    ensure_base(N);
    for(int i = 0, j = 1; j + 1 < N; j++) {
      for(int k = N >> 1; k > (i ^= k); k >>= 1);
      if(i > j) swap(F[i], F[j]);
    }
    for(int i = 1; i < N; i <<= 1) {
      for(int j = 0; j < N; j += i * 2) {
        for(int k = 0; k < i; k++) {
          int s = F[j + k], t = mul(F[j + k + i], rev ? rrts[i][k] : rts[i][k]);
          F[j + k] = add(s, t), F[j + k + i] = add(s, mod - t);
        }
      }
    }
    if(rev) {
      int temp = inverse(N);
      for(int i = 0; i < N; i++) F[i] = mul(F[i], temp);
    }
  }

  vector< int > Multiply(const vector< int > &A, const vector< int > &B) {
    int sz = 1;
    while(sz < A.size() + B.size() - 1) sz <<= 1;
    vector< int > F(sz), G(sz);
    for(int i = 0; i < A.size(); i++) F[i] = A[i];
    for(int i = 0; i < B.size(); i++) G[i] = B[i];
    DiscreteFourierTransform(F, false);
    DiscreteFourierTransform(G, false);
    for(int i = 0; i < sz; i++) F[i] = mul(F[i], G[i]);
    DiscreteFourierTransform(F, true);
    F.resize(A.size() + B.size() - 1);
    return F;
  }
};


int main() {
	int n;
	cin >> n;
	vector<P> a(2 * n + 10), b(2 * n + 10);
	ll x = n;
	while (x&(x - 1)) x++;
	x *= 4;
	a.resize(x);
	b.resize(x);
	rep1(i, n) {
		int c, d;
		cin >> c >> d;
		a[i].real(c); b[i].real(d);
	}
	auto ans = MultPoly(a, b);
	rep1(i, 2 * n) {
		cout << (ll)(ans[i].real() + 0.5) << endl;
	}
}
