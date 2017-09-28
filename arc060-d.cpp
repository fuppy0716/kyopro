#include "bits/stdc++.h"
#include <unordered_set>
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

ll f(ll b, ll n) {
	if (n < b) {
		return n;
	}
	else {
		return f(b, n / b) + n%b;
	}
}

int main() {
	ll n, s, i, j;
	cin >> n >> s;
	if (s == n) {
		cout << n + 1 << endl;
		return 0;
	}
	for (i = 2; i <= sqrt(n) + 1; i++) {
		if (f(i, n) == s) {
			cout << i << endl;
			return 0;
		}
	}
	if (n - s <= 0) {
		cout << -1 << endl;
		return 0;
	}
	for (i = sqrt(n) + 1; i >= 1; i--) {
		if ((n - s) % i) {
			continue;
		}
		ll b = (n - s) / i + 1;
		if (b >= 2) {
			if (f(b, n) == s) {
				cout << b << endl;
				return 0;
			}
		}
	}
	cout << -1 << endl;
	return 0;

}