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


int main() {
	int i, j, n;
	cin >> n;
	vl s(n + 1), a(n + 1);
	a[1] = 1;
	for (i = 2; i <= n; i++) {
		s[i] = (s[i - 2] % MOD + a[i - 1] % MOD) % MOD;
		a[i] = (i*(s[i] % MOD)) % MOD;
	}
	cout << a[n] << endl;

}
