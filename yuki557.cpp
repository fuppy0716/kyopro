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
#define M12 365103863
#define M6 668655281

int main() {
	ll n, i;
	cin >> n;
	if (n == 1) {
		cout << 2 << endl;
		return 0;
	}
	ll a = (n / 2 - 1) / 1000000000000;
	ll b = ((n / 2 - 1) - 1000000000000 * a) / 1000000;
	ll seki = 1;
	if (n % 2) {
		seki *= 3;
		seki *= 4;
		for (i = 0; i < a; i++) {
			seki = (seki * M12) % MOD;
		}
		for (i = 0; i < b; i++) {
			seki = (seki * M6) % MOD;
		}
		for (i = 0; i < ((n / 2 - 1) - 1000000000000 * a - b * 1000000); i++) {
			seki = (seki * 5) % MOD;
		}
	}
	else {
		seki *= 4;
		for (i = 0; i < a; i++) {
			seki = (seki * M12) % MOD;
		}
		for (i = 0; i < b; i++) {
			seki = (seki * M6) % MOD;
		}
		for (i = 0; i < ((n / 2 - 1) - 1000000000000 * a - b * 1000000); i++) {
			seki = (seki * 5) % MOD;
		}
	}
	cout << seki << endl;
}