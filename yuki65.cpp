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
#define M 1000007

int main() {
	int k;
	cin >> k;
	vector<double> e(k + 6);
	e[k] = e[k + 1] = e[k + 2] = e[k + 3] = e[k + 4] = e[k + 5] = 0;
	int i;
	for (i = k - 1; i >= 0; i--) {
		e[i] = (e[i + 1] + e[i + 2] + e[i + 3] + e[i + 4] + e[i + 5] + e[i + 6]) / 6 + 1;
	}
	cout << e[0] << endl;
}