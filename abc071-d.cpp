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
	int n,i,j;
	cin >> n;
	string s[2];
	cin >> s[0] >> s[1];
	ll ans;
	bool flag;
	if (s[0][0] == s[1][0]) {
		ans = 3;
		flag = true;
		i = 1;
	}else{
		ans = 6;
		flag = false;
		i = 2;
	}
	while (i<s[0].size()) {
		if (flag) {
			if (s[0][i] == s[1][i]) {
				ans = (ans * 2) % MOD;
				flag = true;
				i++;
			}
			else {
				ans = (ans * 2) % MOD;
				flag = false;
				i += 2;
			}
		}
		else {
			if (s[0][i] == s[1][i]) {
				flag = true;
				i++;
			}
			else {
				ans = (ans * 3) % MOD;
				flag = false;
				i += 2;
			}
		}
	}
	cout << ans << endl;
}