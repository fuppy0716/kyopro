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



ll lcm(ll a, ll b) {
	ll _a = a, _b = b;
	if (a < b)
		swap(a, b);
	ll r = a%b;
	while (r != 0) {
		a = b;
		b = r;
		r = a%b;
	}
	return _a*_b / b;
}

int main() {
	int n, k, i, j;
	cin >> n >> k;
	vi x(k), y(k);
	for (i = 0; i < k; i++) {
		cin >> x[i] >> y[i];
	}
	vi ato(n);
	for (i = 1; i <= n; i++) {
		int temp = i;
		for (j = 0; j < k; j++) {
			if (x[j] == temp) {
				temp = y[j];
			}
			else if (y[j] == temp) {
				temp = x[j];
			}
		}
		ato[temp - 1] = i;
	}
	vi mae(n);
	for (i = 1; i <= n; i++) {
		for (j = 0; j < n; j++) {
			if (ato[j] == i) {
				mae[i - 1] = j + 1;
				break;
			}
		}
	}
	//DEBUG_VEC(ato);
	//DEBUG_VEC(mae);

	vl num(n);
	for (i = 1; i <= n; i++) {
		int temp = i;
		ll cnt = 0;
		do {
			temp = mae[temp - 1];
			cnt++;
		} while (temp != i);
		num[i - 1] = cnt;
	}
	//DEBUG_VEC(num);

	ll ans = 1;
	for (i = 0; i < n; i++) {
		ans = lcm(ans, num[i]);
	}
	cout << ans << endl;

}