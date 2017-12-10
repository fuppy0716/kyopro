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
const ll INF = 1e18 * 2;
#define MOD 1000000007
#define mod 1000000009
#define pi 3.14159265358979323846
#define Sp(p) cout<<setprecision(15)<< fixed<<p<<endl;
int dx[4] = { 1,0,-1,0 }, dy[4] = { 0,1,0,-1 };
int dx2[8] = { 1,1,0,-1,-1,-1,0,1 }, dy2[8] = { 0,1,1,1,0,-1,-1,-1 };

int main() {
	ll a, b, c;
	cin >> a >> b >> c;
	string s;
	cin >> s;
	int i, j;
	vector<pair<char, int> > t;
	char pre = s[0];
	int cnt = 1;
	for (i = 1; i < s.size(); i++) {
		if (pre == s[i]) {
			cnt++;
		}
		else {
			t.push_back(make_pair(pre, cnt));
			pre = s[i];
			cnt = 1;
		}
	}
	t.push_back(make_pair(pre, cnt));

	/*
	for (i = 0; i < t.size(); i++) {
	cout << "(" << t[i].first << ", " << t[i].second << ") ";
	}
	cout << endl;
	*/
	vll sento(t.size() + 1, vl(2)), matsubi(t.size() + 1, vl(2));
	sento[0][0] = 0;
	sento[0][1] = 0;
	cnt = 0;
	for (i = 1; i <= t.size(); i++) {
		if (t[0].first == '0') {
			sento[i][0] = (cnt + t[i - 1].second)*a + c*(i - 1);
			sento[i][1] = i - 1;
			cnt += t[i - 1].second;
		}
		else {
			sento[i][0] = (cnt + t[i - 1].second)*a + c*i;
			sento[i][1] = i;
			cnt += t[i - 1].second;
		}
	}
	/*
	for (i = 0; i <= t.size(); i++) {
	cout << sento[i][0] << " ";
	}
	cout << endl;
	*/
	cnt = 0;
	matsubi[t.size()][0] = 0;
	matsubi[t.size()][1] = 0;
	for (i = t.size() - 1; i >= 0; i--) {
		if (t[t.size() - 1].first == '0') {
			matsubi[i][0] = (cnt + t[i].second)*b + c*(t.size() - i);
			matsubi[i][1] = t.size() - i;
			cnt += t[i].second;
		}
		else {
			matsubi[i][0] = (cnt + t[i].second)*b + c*(t.size() - i - 1);
			matsubi[i][1] = t.size() - i - 1;
			cnt += t[i].second;
		}
	}
	/*
	for (i = 0; i <= t.size(); i++) {
	cout << matsubi[i][0] << " ";
	}
	cout << endl;
	*/
	ll ans = INF;
	for (i = 0; i <= t.size(); i++) {
		ans = min(ans, sento[i][0] + matsubi[i][0] - c * min(sento[i][1], matsubi[i][1]));

	}
	cout << ans << endl;
}