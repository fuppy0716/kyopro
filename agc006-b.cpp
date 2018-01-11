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
const ll INF = 1e18 * 4;
#define MOD 1000000007
#define mod 1000000009
#define pi 3.14159265358979323846
#define Sp(p) cout<<setprecision(15)<<fixed<<p<<endl;
int dx[4] = { 1,0,-1,0 }, dy[4] = { 0,1,0,-1 };
int dx2[8] = { 1,1,0,-1,-1,-1,0,1 }, dy2[8] = { 0,1,1,1,0,-1,-1,-1 };

int main() {
	int n, x, i;
	cin >> n >> x;
	if (n == 1) {
		cout << 1 << endl << 1 << endl;
		return 0;
	}
	if (x == 1 || x == 2 * n - 1) {
		cout << "No" << endl;
		return 0;
	}
	else {
		cout << "Yes" << endl;
	}
	if (n == 2) {
		cout << 1 << endl << 2 << endl << 3 << endl;
		return 0;
	}
	if (x == 2 * n - 2) {
		for (i = 1; i <= n - 2; i++) {
			cout << i << endl;
		}
		cout << x - 1 << endl;
		cout << x << endl;
		cout << x + 1 << endl;
		cout << x - 2 << endl;
		for (i = n - 1; i < 2 * n - 4; i++) {
			cout << i << endl;
		}
	}
	else {
		vi a(2 * n - 1);
		for (i = 0; i < 2 * n - 1; i++) {
			a[i] = i + 1;
		}
		//DEBUG_VEC(a);
		for (i = 0; i < 4; i++) {
			a.erase(a.begin() + x - 2);
		}
		a.resize(2 * n - 5);
		//DEBUG_VEC(a);
		for (i = 0; i < n - 2; i++) {
			cout << a[i] << endl;
		}
		cout << x + 1 << endl << x << endl << x - 1 << endl << x + 2 << endl;
		for (i = n - 2; i < a.size(); i++) {
			cout << a[i] << endl;
		}

	}
}