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

#define N 102
#define M 1010
int n, m;
vector< vector< pair<int, int> > > adj(N, vector< pair<int, int> >());
vii hyou(N, vi(N, inf));


int main() {
	cin >> n >> m;
	int i, j, k;
	for (i = 0; i < n; i++) {
		hyou[i][i] = 0;
	}
	vii l(m, vi(3));
	for (i = 0; i < m; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		hyou[a - 1][b - 1] = hyou[b - 1][a - 1] = c;
		l[i][0] = a - 1;
		l[i][1] = b - 1;
		l[i][2] = c;
	}
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			for (k = 0; k < n; k++) {
				if (hyou[j][k] > hyou[j][i] + hyou[i][k]) {
					hyou[j][k] = hyou[j][i] + hyou[i][k];
				}
			}
		}
	}

	int ans = 0;
	for (i = 0; i < m; i++) {
		bool flag = false;
		for (j = 0; j < n; j++) {
			for (k = 0; k < n; k++) {
				if (hyou[j][k] == hyou[j][l[i][0]] + l[i][2] + hyou[l[i][1]][k]) {
					flag = true;
				}
			}
		}
		if (!flag) {
			ans++;
		}
	}
	cout << ans << endl;
}