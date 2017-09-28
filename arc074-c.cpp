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

int main() {
	int h, w, i, j;
	cin >> h >> w;
	if (h % 3 == 0 || w % 3 == 0) {
		cout << 0 << endl;
		return 0;
	}
	ll ans = min(w, h);
	for (i = max(h / 3 - 5, 1); i < min(h / 3 + 5, h); i++) {
		for (j = max(w / 2 - 5, 1); j < min(w / 2 + 5, w); j++) {
			ll a, b, c;
			a = w*i;
			b = (h - i)*j;
			c = (h - i)*(w - j);
			ll M = max(a, max(b, c));
			ll m = min(a, min(b, c));
			ans = min(ans, M - m);
		}
	}
	for (i = max(w / 3 - 5, 1); i < min(w / 3 + 5, w); i++) {
		for (j = max(h / 2 - 5, 1); j < min(h / 2 + 5, h); j++) {
			ll a, b, c;
			a = h*i;
			b = (w - i)*j;
			c = (w - i)*(h - j);
			ll M = max(a, max(b, c));
			ll m = min(a, min(b, c));
			ans = min(ans, M - m);
		}
	}
	cout << ans << endl;
}