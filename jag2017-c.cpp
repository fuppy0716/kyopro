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
#define Sp(p) cout<<setprecision(15)<< fixed<<p<<endl;
int dx[4] = { 1,0,-1,0 }, dy[4] = { 0,1,0,-1 };
int dx2[8] = { 1,1,0,-1,-1,-1,0,1 }, dy2[8] = { 0,1,1,1,0,-1,-1,-1 };

#define M 1000100

int main() {
	int i, j;
	vector<bool> sosuu(M, true);
	vi sosuu2;
	sosuu[0] = sosuu[1] = false;
	for (i = 2; i < M; i++) {
		if (sosuu[i]) {
			sosuu2.push_back(i);
			for (j = 2; i*j < M; j++) {
				sosuu[i*j] = false;
			}
		}
	}
	int l, r;
	cin >> l >> r;
	vector<pii> cnt(r - l + 1);
	for (int a = l; a <= r; a++) {
		cnt[a - l].first = a;
		cnt[a - l].second = 0;
	}
	for (i = 0; i < sosuu2.size(); i++) {
		int L = ((l + sosuu2[i] - 1) / sosuu2[i])*sosuu2[i];
		for (int a = L; a <= r; a += sosuu2[i]) {
			while (cnt[a - l].first%sosuu2[i] == 0) {
				cnt[a - l].second++;
				cnt[a - l].first /= sosuu2[i];
			}
		}
	}
	int ans = 0;
	for (int a = l; a <= r; a++) {
		if (cnt[a - l].first > 1) {
			cnt[a - l].second++;
		}
		if (sosuu[cnt[a - l].second]) {
			ans++;
		}
	}
	cout << ans << endl;


}