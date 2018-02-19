


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
#define fi first
#define se second
#define rep(i,n) for(int i=0;i<(int)(n);i++)
#define rep1(i,n) for(int i=1;i<=(int)(n);i++)
#define all(c) c.begin(),c.end()
const int inf = 1000000001;
const ll INF = 2e18 * 2;
#define MOD 1000000007
#define mod 1000000009
#define pi 3.14159265358979323846
#define Sp(p) cout<<setprecision(15)<< fixed<<p<<endl;
int dx[4] = { 1,0,-1,0 }, dy[4] = { 0,1,0,-1 };
int dx2[8] = { 1,1,0,-1,-1,-1,0,1 }, dy2[8] = { 0,1,1,1,0,-1,-1,-1 };


//http://beet-aizu.hatenablog.com/entry/2017/12/12/235950
struct HLDecomposition {
	int n, pos;
	vector<vector<int> > G;
	vector<int> vid, head, sub, hvy, par, dep, inv, type;

	HLDecomposition() {}
	HLDecomposition(int sz) :
		n(sz), pos(0), G(n),
		vid(n, -1), head(n), sub(n, 1), hvy(n, -1),
		par(n), dep(n), inv(n), type(n) {}

	void add_edge(int u, int v) {
		G[u].push_back(v);
		G[v].push_back(u);
	}

	void build(vector<int> rs = { 0 }) {
		int c = 0;
		for (int r : rs) {
			dfs(r);
			bfs(r, c++);
		}
	}

	void dfs(int rt) {
		using T = pair<int, int>;
		stack<T> st;
		par[rt] = -1;
		dep[rt] = 0;
		st.emplace(rt, 0);
		while (!st.empty()) {
			int v = st.top().first;
			int &i = st.top().second;
			if (i<(int)G[v].size()) {
				int u = G[v][i++];
				if (u == par[v]) continue;
				par[u] = v;
				dep[u] = dep[v] + 1;
				st.emplace(u, 0);
			}
			else {
				st.pop();
				int res = 0;
				for (int u : G[v]) {
					if (u == par[v]) continue;
					sub[v] += sub[u];
					if (res<sub[u]) res = sub[u], hvy[v] = u;
				}
			}
		}
	}

	void bfs(int r, int c) {
		int &k = pos;
		queue<int> q({ r });
		while (!q.empty()) {
			int h = q.front(); q.pop();
			for (int i = h; i != -1; i = hvy[i]) {
				type[i] = c;
				vid[i] = k++;
				inv[vid[i]] = i;
				head[i] = h;
				for (int j : G[i])
					if (j != par[i] && j != hvy[i]) q.push(j);
			}
		}
	}

	// for_each(vertex)
	// [l,r] <- attention!!
	void for_each(int u, int v, const function<void(int, int)>& f) {
		while (1) {
			if (vid[u]>vid[v]) swap(u, v);
			f(max(vid[head[v]], vid[u]), vid[v]);
			if (head[u] != head[v]) v = par[head[v]];
			else break;
		}
	}

	// for_each(edge)
	// [l,r] <- attention!!
	// 値が辺に乗っているときは、頂点から遠いほう(すなわちvidが大きいほう)の
	// 頂点に値を移す。yuki650
	void for_each_edge(int u, int v, const function<void(int, int)>& f) {
		while (1) {
			if (vid[u]>vid[v]) swap(u, v);
			if (head[u] != head[v]) {
				f(vid[head[v]], vid[v]);
				v = par[head[v]];
			}
			else {
				if (u != v) f(vid[u] + 1, vid[v]);
				break;
			}
		}
	}

	int lca(int u, int v) {
		while (1) {
			if (vid[u]>vid[v]) swap(u, v);
			if (head[u] == head[v]) return u;
			v = par[head[v]];
		}
	}

	int distance(int u, int v) {
		return dep[u] + dep[v] - 2 * dep[lca(u, v)];
	}
};

class LazySegmentTree {
public:
	int n;
	vl node, lazy;

	LazySegmentTree(vl a) {
		int _n = a.size();
		n = 1; while (n < _n) n *= 2;
		node.resize(2 * n - 1);
		lazy.resize(2 * n - 1, 0);
		for (int i = 0; i < _n; i++) node[i + n - 1] = a[i];
		for (int i = n - 2; i >= 0; i--) {
			node[i] = node[i * 2 + 1] + node[i * 2 + 2];
			node[i] %= MOD;
		}
	}

	// k番目のノードについて遅延評価を行う
	inline void eval(int k, int l, int r) {
		if (lazy[k] != 0) {
			node[k] += (r - l) * lazy[k];
			if (r - l > 1) {
				(lazy[2 * k + 1] += lazy[k]); /////
				(lazy[2 * k + 2] += lazy[k]); /////
			}
			lazy[k] = 0;
		}
	}

	// [a, b)をxにする
	void add(int a, int b, ll x, int k, int l, int r) {
		// k 番目のノードに対して遅延評価を行う
		eval(k, l, r);
		if (b <= l || r <= a) return;
		if (a <= l && r <= b) {
			(lazy[k] += x);
			eval(k, l, r);
		}
		else {
			add(a, b, x, 2 * k + 1, l, (l + r) / 2);
			add(a, b, x, 2 * k + 2, (l + r) / 2, r);
			node[k] = node[2 * k + 1] + node[2 * k + 2];
		}
	}

	ll getsum(int a, int b, int k, int l, int r) {
		eval(k, l, r);
		if (b <= l || r <= a) return 0;
		if (a <= l && r <= b) return node[k];
		ll resl = getsum(a, b, 2 * k + 1, l, (l + r) / 2);
		ll resr = getsum(a, b, 2 * k + 2, (l + r) / 2, r);
		return (resl + resr);
	}
};


int main() {
	int n, i, j;
	cin >> n;


	HLDecomposition hld(n);
	rep(i, n - 1) {
		int a, b;
		cin >> a >> b;
		a--; b--;
		hld.add_edge(a, b);
	}
	hld.build();

	vl a(n);
	LazySegmentTree lst(a);

	int q;
	cin >> q;
	ll ans = 0;
	while (q--) {
		int u0, v0;
		cin >> u0 >> v0;
		u0--; v0--;
		int u = u0, v = v0;
		while (true) {
			//cout << hld.vid[u] << " " << hld.vid[v] << endl;
			if (hld.vid[u] > hld.vid[v]) swap(u, v);
			lst.add(max(hld.vid[hld.head[v]], hld.vid[u]), hld.vid[v] + 1, 1, 0, 0, lst.n);
			if (hld.head[u] != hld.head[v]) v = hld.par[hld.head[v]];
			else break;
		}
		u = u0; v = v0;
		while (true) {
			//cout << hld.vid[u] << " " << hld.vid[v] << endl;
			if (hld.vid[u] > hld.vid[v]) swap(u, v);
			ans += lst.getsum(max(hld.vid[hld.head[v]], hld.vid[u]), hld.vid[v] + 1, 0, 0, lst.n);
			if (hld.head[u] != hld.head[v]) v = hld.par[hld.head[v]];
			else break;
		}
		//DEBUG(ans); cout << endl;
	}
	cout << ans << endl;

}