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
#define pll pair<ll,ll>
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


int main() {
	int f, n, k;
	cin >> f >> n >> k;
	int i, j, x;
	vector< vector<double> > C(n + 1, vector<double>(n + 1));
	C[0][0] = 1;
	for (i = 1; i <= n; i++) {
		for (j = 0; j <= i; j++) {
			if (j == 0 || j == i) {
				C[i][j] = 1;
			}
			else {
				C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
			}
		}
	}
	vector<double> p(f + 1);
	for (i = 1; i <= f; i++) {
		double ans = 0;
		for (x = 1; x <= n; x++) {
			for (j = max(n - k - x + 1, 0); j <= n - k; j++) {
				if (n - x - j < 0) {
					break;
				}
				double p1 = (double)(i - 1) / f;
				double p2 = (double)1 / f;
				double p3 = 1 - (p1 + p2);
				double temp = pow(p1, j) * pow(p2, x) * pow(p3, (n - j - x));
				int k;
				for (k = 1; k <= n; k++)	temp *= k;
				for (k = 1; k <= j; k++)	temp /= k;
				for (k = 1; k <= x; k++)	temp /= k;
				for (k = 1; k <= n - j - x; k++)temp /= k;
				ans += temp;
			}
		}
		p[i] = ans;
	}
	double ans = 0;
	for (i = 1; i <= f; i++) {
		ans += i*p[i];
	}
	Sp(ans);
}