
class CentroidDecomposition {
public:
	int n; //頂点数
	vii G; //グラフの隣接リスト表現
	vector<bool> isused; //その頂点がすでに分割に使われているか
	vi subtreesize; //部分木のサイズ,更新される
	vi parent;
	vi centroid; //重心が後ろに追加されていく
	vector<char> ans;

	CentroidDecomposition(int n) : n(n) {
		G.resize(n); isused.resize(n);
		subtreesize.resize(n); parent.resize(n);
		ans.resize(n);
	}

	void add_edge(int u, int v) {
		G[u].push_back(v); G[v].push_back(u);
	}

	int search_centroid(int now, int par, int size) {
		subtreesize[now] = 1;
		parent[now] = par;
		bool iscentroid = true;
		for (int i = 0; i < G[now].size(); i++) {
			int child = G[now][i];
			if (child == par) continue;
			if (isused[child]) continue;
			int child_size = search_centroid(child, now, size);
			if (child_size > size / 2) iscentroid = false;
			subtreesize[now] += child_size;
		}
		if (size - subtreesize[now] > size / 2) {
			iscentroid = false;
		}
		if (iscentroid) {
			centroid.push_back(now);
		}
		return subtreesize[now];
	}

	//問題によって変わる
	void solve(int root, char c, int size) {
		search_centroid(root, -1, size);
		int cent = centroid.back();
		isused[cent] = true;
		ans[cent] = c;
		rep(i, G[cent].size()) {
			int ch = G[cent][i];
			if (isused[ch]) {
				continue;
			}
			if (parent[ch] == cent) {
				solve(ch, c + 1, subtreesize[ch]);
			}
			else {
				solve(ch, c + 1, size - subtreesize[cent]);
			}
		}
		return;
	}


};



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


//根付き木のハッシュ
//木の同型判定に使う
#include <random>
vl rand1(100010);
vl rand2(100010);

void make_rand() {
	random_device rnd;
	mt19937 mt(rnd());
	uniform_int_distribution<> randinf(0, inf);
	rep(i, 100010) {
		rand1[i] = randinf(mt);
		rand2[i] = randinf(mt);
	}
}

pll hs(vii &G, int now, int parent, int depth) {
	pll res = pll(1, 1);
	rep(i, G[now].size()) {
		if (G[now][i] == parent) {
			continue;
		}
		pll temp = hs(G, G[now][i], now, depth + 1);
		(res.first *= (temp.first + rand1[depth])) %= mod;
		(res.second *= (temp.second + rand2[depth])) %= mod;
	}
	return res;
}
