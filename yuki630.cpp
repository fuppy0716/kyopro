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
const int inf = 1000000001;
const ll INF = 2e18 * 2;
#define MOD 1000000007
#define mod 1000000009
#define pi 3.14159265358979323846
#define Sp(p) cout<<setprecision(15)<< fixed<<p<<endl;
int dx[4] = { 1,0,-1,0 }, dy[4] = { 0,1,0,-1 };
int dx2[8] = { 1,1,0,-1,-1,-1,0,1 }, dy2[8] = { 0,1,1,1,0,-1,-1,-1 };

int main() {
	ll n, m;
	cin >> n >> m;
	if (m > n * (n - 1) / 2) {
		cout << "NO" << endl;
		return 0;
	}
	if (m < n - 1) {
		cout << "NO" << endl;
		return 0;
	}
	if (m >(n / 2) * (n - n / 2)) {
		cout << "NO" << endl;
		return 0;
	}
	cout << "YES" << endl;
	int i, j;
	vi a(n);
	for (i = 0; i < n / 2; i++) {
		a[i] = i + 1;
	}
	for (i = n / 2; i < n; i++) {
		a[i] = n - (i - n / 2);
	}

	for (i = 0; i < n; i++) {
		cout << a[i] << " ";
	}
	cout << endl;


	if (n % 2 == 0) {
		cout << n << " " << n / 2 << endl;
	}
	for (i = 1; i <= (n - 1) / 2; i++) {
		cout << n / 2 + i << " " << i << endl;
		cout << i << " " << n / 2 + i + 1 << endl;
	}
	int nokori = m - (n - 1);

	for (i = 1; i <= n / 2; i++) {
		for (j = n / 2 + 1; j <= n; j++) {
			if (nokori == 0) {
				return 0;
			}
			if (j == n / 2 + i || j == n / 2 + i + 1) {
				continue;
			}
			cout << i << " " << j << endl;
			nokori--;
		}
	}
}