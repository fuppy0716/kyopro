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


//yuki260


struct Modint {
	ll n;
	static const ll Mod = 1000000007;
	Modint(int n = 0) : n(n) {}
};

Modint operator+(Modint a, Modint b) { return Modint((a.n += b.n) >= mod ? a.n - a.Mod : a.n); }
Modint operator-(Modint a, Modint b) { return Modint((a.n -= b.n) < 0 ? a.n + a.Mod : a.n); }
Modint operator*(Modint a, Modint b) { return Modint(1LL * a.n * b.n % a.Mod); }
Modint &operator+=(Modint &a, Modint b) { return a = a + b; }
Modint &operator-=(Modint &a, Modint b) { return a = a - b; }
Modint &operator*=(Modint &a, Modint b) { return a = a * b; }

#define vm vector<Modint>
#define vvm vector<vm>
#define vvvm vector<vvm>
#define vvvvm vector<vvvm>
#define vvvvvm vector<vvvvm>

int main() {
	vector<string> a(2);
	cin >> a[0] >> a[1];
	int i, j;
	for (i = a[0].size() - 1; i >= 0; i--) {
		if (a[0][i] != '0') {
			a[0][i] -= 1;
			break;
		}
		else {
			a[0][i] = '9';
		}
	}
	if (a[0][0] == '0') {
		a[0].erase(a[0].begin());
	}
	vector<Modint> ans(2);
	rep(q, 2) {
		string s = a[q];
		int n = s.size();
		// 桁数、3で割ったあまり、3がつくか否か、8で割ったあまり、最大値に沿っているか否か
		vvvvvm dp(n + 1, vvvvm(3, vvvm(2, vvm(8, vm(2, 0)))));
		dp[0][0][0][0][1] = Modint(1);
		rep(keta, n) {
			rep(dev3, 3) {
				rep(is3, 2) {
					rep(dev8, 8) {
						rep(giri, 2) {
							int up = 9;
							if (giri) {
								up = s[keta] - '0';
							}
							int down = 0;
							for (int add = down; add <= up; add++) {
								int ndev3 = (dev3 * 10 + add) % 3;
								int ndev8 = (dev8 * 10 + add) % 8;
								int nis3 = is3;
								if (add == 3) {
									nis3 = 1;
								}
								int nketa = keta + 1;
								int ngiri = 0;
								if (giri && (add == up)) {
									ngiri = 1;
								}

								dp[nketa][ndev3][nis3][ndev8][ngiri] += dp[keta][dev3][is3][dev8][giri];

							}
						}
					}
				}
			}
		}
		rep(dev3, 3) {
			rep(is3, 2) {
				rep(dev8, 8) {
					rep(giri, 2) {
						if ((dev3 == 0 || is3) && dev8) {
							ans[q] += dp[n][dev3][is3][dev8][giri];
						}
					}
				}
			}
		}


	}
	cout << (ans[1] - ans[0]).n << endl;
}