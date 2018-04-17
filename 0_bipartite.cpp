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
#define pll pair<ll,ll>
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

#define N 100010
vii G(N, vi()); //グラフの隣接リスト表現
vi match(N); //マッチングのペア
vector<bool> used(N); //DFSですでに調べたかのフラグ
int n, m;
vi color(N, -1);

//二部グラフかどうかを判断
bool bipartite() {
	stack<int> st;
	color[0] = 0;
	st.push(0);
	int i, j;
	while (!st.empty()) {
		i = st.top();
		st.pop();
		for (j = 0; j < G[i].size(); j++) {
			if (color[G[i][j]] == color[i]) {
				//cout << "NO" << endl;
				return false;
			}
			else {
				if (color[G[i][j]] == -1) {
					color[G[i][j]] = 1 - color[i];
					st.push(G[i][j]);
				}
			}
		}
	}
	//cout << "YES" << endl;
	return true;
}

//マッチングに使う
bool dfs(int v) {
	used[v] = true;
	for (int i = 0; i < G[v].size(); i++) {
		int u = G[v][i], w = match[u];
		if (w < 0 || !used[w] && dfs(w)) {
			match[v] = u;
			match[u] = v;
			return true;
		}
	}
	return false;
}

//二部グラフの最大マッチングを求める
//二部グラフの最大マッチング = 最小点カバー = n-最小辺カバー = n-最大安定集合
int bipartite_matching() {
	int res = 0;
	fill(match.begin(), match.end(), -1);
	for (int v = 0; v < n; v++) {
		if (match[v] < 0) {
			fill(used.begin(), used.end(), 0);
			if (dfs(v)) {
				res++;
			}
		}
	}
	return res;
}

int main() {
	int i, j;
	scanf("%lld%lld", &n, &m);
	int a, b;

	for (i = 0; i < m; i++) {
		scanf("%d%d", &a, &b);
		a--; b--;
		G[a].push_back(b);
		G[b].push_back(a);
	}
	bool flag = bipartite();
	if (flag) {
		ll w = 0, b = 0;
		for (i = 0; i < n; i++) {
			if (color[i] == 0) {
				w++;
			}
			else {
				b++;
			}
		}
		cout << w*b - m << endl;
		return 0;
	}
	else {
		cout << (n*n - n) / 2 - m << endl;
		return 0;
	}
}








const int N = 100100;
const int M = 100100;
vector<vector<pll> > G(N + 1);
vl u(M + N), v(M + N), w(M + N);

int main() {
	int n, m;
	cin >> n >> m;
	rep1(i, n) {
		G[0].push_back(pll(i, 0));
		u[i - 1] = 0; v[i - 1] = i; w[i - 1] = 0;
	}
	rep(i, m) {
		cin >> u[i + n] >> v[i + n] >> w[i + n];
		w[i + n]++;
		G[u[i + n]].push_back(pll(v[i + n], w[i + n]));
	}
	vi idx(n + 1);
	vl dp(n + m, -1);
	rep(i, n) {
		dp[i] = 0;
	}
}