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
int dx2[8] = { 1,1,0,-1,-1,-1,0,1 }, dy2[8] = { 0,1,1,1,0,-1,-1,-1 };

static const int WHITE = 0;
static const int GRAY = 1;
static const int BLACK = 2;
static const int N = 310;

int n;
vll hyou1(N, vl(N, INF)), hyou2(N, vl(N, INF));
vector< vector< pair<int, int> > > adj(N, vector< pair<int, int> >());
vl d(N, INF);



int main() {
	cin >> n;
	int i, j, k;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			cin >> hyou1[i][j];
		}
	}
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if (i == j) {
				if (hyou1[i][j] != 0) {
					cout << -1 << endl;
					return 0;
				}
			}
			else {
				if (hyou1[i][j] != hyou1[j][i]) {
					cout << -1 << endl;
					return 0;
				}
			}
		}
	}
	for (i = 0; i < n; i++) {
		for (j = 0; j < i; j++) {
			bool flag = false;
			for (k = 0; k < n; k++) {
				if (k == i || k == j) {
					continue;
				}
				if (hyou1[i][j] == hyou1[i][k] + hyou1[k][j]) {
					flag = true;
				}
			}
			if (!flag) {
				adj[i].push_back(make_pair(hyou1[i][j], j));
				adj[j].push_back(make_pair(hyou1[i][j], i));
			}
		}
	}
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if (i == j) {
				hyou2[i][j] = 0;
			}
		}
	}
	for (i = 0; i < n; i++) {
		for (j = 0; j < adj[i].size(); j++) {
			hyou2[i][adj[i][j].second] = adj[i][j].first;
		}
	}
	for (k = 0; k < n; k++) {
		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				if (hyou2[i][j] > hyou2[i][k] + hyou2[k][j]) {
					hyou2[i][j] = hyou2[i][k] + hyou2[k][j];
				}
			}
		}
	}
	if (hyou1 != hyou2) {
		cout << -1 << endl;
		return 0;
	}
	ll sum = 0;
	for (i = 0; i < n; i++) {
		for (j = 0; j < adj[i].size(); j++) {
			sum += adj[i][j].first;
		}
	}
	sum /= 2;
	cout << sum << endl;
}