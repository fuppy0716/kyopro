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

/*
cin.tie(0);
ios::sync_with_stdio(false);
*/
int main() {
	cin.tie(0);
	ios::sync_with_stdio(false);

	int a, i, j;
	cin >> a;
	string s;
	cin >> s;
	int n = s.size();
	vl s2(n);
	for (i = 0; i < n; i++) {
		s2[i] = s[i] - 'a' + 1;
	}
	vl ans = s2;
	int n2 = n;
	i = 0;
	do {
		i = 0;
		s2 = ans;
		n2 = ans.size();
		while (i < n2 - 1) {
			while (ans[i] <= 26 - a && ans[i + 1] > 0) {
				ans[i] += a;
				ans[i + 1]--;
			}
			i++;
		}
		//DEBUG_VEC(ans);
	} while (ans != s2);
	for (i = 0; i < ans.size(); i++) {
		if (ans[i] != 0) {
			cout << (char)('a' + ans[i] - 1);
		}
	}cout << endl;

}