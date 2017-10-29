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
#define Sp(p) cout<<setprecision(15)<<fixed<<p<<endl;
int dx[4] = { 1,0,-1,0 }, dy[4] = { 0,1,0,-1 };
int dx2[8] = { 1,1,0,-1,-1,-1,0,1 }, dy2[8] = { 0,1,1,1,0,-1,-1,-1 };

static const int WHITE = 0;
static const int GRAY = 1;
static const int BLACK = 2;
static const int N = 2005;

//ttŽžAd[v]v‚ðÅ‰‚É”­Œ©‚µ‚½ŽžAf[v]v‚ð’²‚×I‚í‚Á‚½Žž
int n, tt = 0;
vii M(N, vi());
vi color(N, WHITE), d(N), f(N), nt(N, 0);

int next(int u) {
	int v;
	for (v = nt[u]; v < n; v++) {
		nt[u] = v;
		if (M[u][v]) {
			return v;
		}
	}
	return -1;
}


void dfs(int r) {
	stack<int> s;
	s.push(r);
	color[r] = GRAY;
	d[r] = 0;

	while (!s.empty()) {
		int u = s.top();
		for (; nt[u] < M[u].size(); nt[u]++) {
			if (color[M[u][nt[u]]] == WHITE) {
				int v = M[u][nt[u]];
				color[v] = GRAY;
				d[v] = d[u] + 1;
				s.push(v);
				break;
			}
		}
		if (nt[u] == M[u].size()) {
			s.pop();
			color[u] = BLACK;
		}
	}
}


int main() {
	int n, k;
	scanf("%d%d", &n, &k);
	vector<pii> edge(n - 1);
	for (int i = 0; i < n - 1; i++) {
		int a, b;
		scanf("%d%d", &a, &b);
		a--; b--;
		M[a].push_back(b);
		M[b].push_back(a);
		edge[i] = pii(a, b);
	}
	int ans = inf;
	if (!(k % 2)) {
		for (int i = 0; i < n; i++) {
			fill(color.begin(), color.end(), WHITE);
			fill(d.begin(), d.end(), -1);
			fill(nt.begin(), nt.end(), 0);
			dfs(i);
			int cnt = 0;
			bool flag = false;
			for (int j = 0; j < n; j++) {
				if (d[j] > k / 2) {
					cnt++;
				}
			}
			ans = min(ans, cnt);

		}
	}
	else {
		for (int i = 0; i < n - 1; i++) {
			fill(color.begin(), color.end(), WHITE);
			fill(d.begin(), d.end(), -1);
			fill(nt.begin(), nt.end(), 0);
			color[edge[i].second] = GRAY;
			dfs(edge[i].first);
			dfs(edge[i].second);
			int cnt = 0;
			bool flag = false;
			for (int j = 0; j < n; j++) {
				if (d[j] > k / 2) {
					cnt++;
				}
			}
			ans = min(ans, cnt);
		}
	}
	cout << ans << endl;
	return 0;

}