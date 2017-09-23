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
	ll h, w, n;
	ll i, j, k, l;
	cin >> h >> w >> n;
	vector< pii > cnt;
	for (i = 0; i < n; i++) {
		pii p;
		cin >> p.second >> p.first;
		p.second--; p.first--;
		if (!(p.first < 1 || p.first >= w - 1 || p.second < 1 || p.second >= h - 1)) {
			cnt.push_back(p);
		}
		for (j = 0; j < 8; j++) {
			pii p2 = make_pair(p.first + dy2[j], p.second + dx2[j]);
			if (p2.first < 1 || p2.first >= w - 1 || p2.second < 1 || p2.second >= h - 1) {
				continue;
			}
			cnt.push_back(p2);
		}
	}
	sort(cnt.begin(), cnt.end());
	pii pre = make_pair(-1, -1);
	vl ans(10);
	int ct = 1;
	for (i = 0; i < cnt.size(); i++) {
		if (pre == cnt[i]) {
			ct++;
		}
		else {
			ans[ct]++;
			pre = cnt[i];
			ct = 1;
		}
	}
	ans[ct]++;
	ans[1]--;
	ll sum = 0;
	for (i = 1; i < 10; i++) {
		sum += ans[i];
	}
	cout << (h - 2)*(w - 2) - sum << endl;
	for (i = 1; i < 10; i++) {
		cout << ans[i] << endl;
	}
}
