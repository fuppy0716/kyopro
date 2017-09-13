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

int main() {
	int n, a, b, i, j;
	cin >> n >> a >> b;
	vl v(n);
	for (i = 0; i < n; i++) {
		cin >> v[i];
	}
	sort(v.begin(), v.end());
	reverse(v.begin(), v.end());

	vll C(n + 1, vl(n + 1));
	C[0][0] = 1;
	for (i = 1; i <= n; i++) {
		for (j = 0; j <= i; j++) {
			if (j == 0 || j == i) {
				C[i][j] = 1;
			}
			else {
				C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
			}
		}
	}

	double sum = 0;
	if (v[0] != v[a - 1]) {
		for (i = 0; i < a; i++) {
			sum += v[i];
		}
		Sp(sum / a);
		int cnt = 0;
		int a2;
		for (i = n - 1; i >= 0; i--) {
			if (v[i] == v[a - 1]) {
				cnt++;
				a2 = i;
			}
		}
		cout << C[cnt][a - a2] << endl;
		return 0;
	}

	cout << v[0] << endl;
	int c = 0;
	while (v[c] == v[0]) {
		c++;
		if (c == n)
			break;
	}
	ll ans = 0;
	for (i = a; i <= min(b, c); i++) {
		ans += C[c][i];
	}
	cout << ans << endl;
}