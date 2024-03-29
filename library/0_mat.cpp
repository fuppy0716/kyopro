t #include "bits/stdc++.h"
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
const int inf = 1000000001;
const ll INF = 2e18 * 2;
#define MOD 1000000007
#define mod 1000000009
#define pi 3.14159265358979323846
#define Sp(p) cout<<setprecision(15)<< fixed<<p<<endl;
int dx[4] = { 1,0,-1,0 }, dy[4] = { 0,1,0,-1 };
int dx2[8] = { 1,1,0,-1,-1,-1,0,1 }, dy2[8] = { 0,1,1,1,0,-1,-1,-1 };

struct Modint {
	ll n;
	static const ll Mod = 1000000007;
	Modint(int n = 0) : n(n) {}
};

Modint operator+(Modint a, Modint b) { return Modint((a.n += b.n) >= MOD ? a.n - a.Mod : a.n); }
Modint operator-(Modint a, Modint b) { return Modint((a.n -= b.n) < 0 ? a.n + a.Mod : a.n); }
Modint operator*(Modint a, Modint b) { return Modint(1LL * a.n * b.n % a.Mod); }
Modint &operator+=(Modint &a, Modint b) { return a = a + b; }
Modint &operator-=(Modint &a, Modint b) { return a = a - b; }
Modint &operator*=(Modint &a, Modint b) { return a = a * b; }

typedef vector<ll> vec;
typedef vector<vec> mat;

mat mul(mat &A, mat &B) {
	mat C(A.size(), vec(B[0].size()));
	for (int i = 0; i < A.size(); i++) {
		for (int k = 0; k < B.size(); k++) {
			for (int j = 0; j < B[0].size(); j++) {
				C[i][j] = C[i][j] + A[i][k] * B[k][j];
			}
		}
	}
	return C;
}

vec mul(mat &A, vec &B) {
	vec C(A.size());
	for (int i = 0; i < A.size(); i++) {
		for (int j = 0; j < B.size(); j++) {
			C[i] += A[i][j] * B[j];
		}
	}
	return C;
}

mat pow(mat A, ll n) {
	mat B(A.size(), vec(A.size()));
	for (int i = 0; i < A.size(); i++) {
		B[i][i] = 1;
	}
	while (n > 0) {
		if (n & 1)B = mul(B, A);
		A = mul(A, A);
		n >>= 1;
	}
	return B;
}

ll det(vector<vector<ll>> G) {
    int n = G.size();
    ll ans = 1;
    rep (j, n) {
        int i = -1;
        REP (k, j, n) {
            if (G[k][j] != 0) {
                i = k;
                break;
            }
        }
        if (i == -1) return 0;

        if (i != j) {
            swap(G[i], G[j]);
        }

        (ans *= G[j][j]) %= MOD;
        ll inv = mod_inverse(G[j][j]);
        rep (jj, n) {
            (G[j][jj] *= inv) %= MOD;
        }

        rep (i, n) {
            if (i == j) continue;
            ll mul = G[i][j];
            rep (k, n) {
                (G[i][k] -= G[j][k] * mul) %= MOD;
            }
        }
    }

    rep (i, n) (ans *= G[i][i]) %= MOD;
    return (ans + MOD) % MOD;
}

// max(a) < 1 << k
vector<int> hakidashi(vector<int> a, int k) {
    int base_num = 0;
    rep (i, k) {
        int mask = 1 << i;
        bool flag = false;
        REP (j, base_num, a.size()) {
            if ((a[j] & mask) != 0) {
                swap(a[base_num], a[j]);
                flag = true;
                break;
            }
        }
        if (not flag) {
            continue;
        }

        rep (j, a.size()) {
            if (base_num == j) continue;
            if (a[j] & mask) {
                a[j] ^= a[base_num];
            }
        }
        base_num++;
    }
    return a;
}