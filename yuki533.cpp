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
	int n, i, j;
	cin >> n;
	vl s1(1000001), s2(1000001), s3(1000001);
	s1[1] = s2[2] = s3[3] = 1;
	s1[3] = s2[3] = 1;
	for (i = 4; i <= n; i++) {
		s1[i] = (s2[i - 1] + s3[i - 1]) % MOD;
		s2[i] = (s1[i - 2] + s3[i - 2]) % MOD;
		s3[i] = (s1[i - 3] + s2[i - 3]) % MOD;
	}
	cout << (s1[n] + s2[n] + s3[n]) % MOD << endl;
}