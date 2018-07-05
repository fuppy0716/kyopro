#include "bits/stdc++.h"

using namespace std;

#define DEBUG(x) cerr<<#x<<": "<<x<<endl;
#define DEBUG_VEC(v) cerr<<#v<<":";for(int i=0;i<v.size();i++) cerr<<" "<<v[i]; cerr<<endl

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
template<class S, class T> pair<S, T> operator+(const pair<S, T> &s, const pair<S, T> &t) { return pair<S, T>(s.first + t.first, s.second + t.second); }
template<class S, class T> pair<S, T> operator-(const pair<S, T> &s, const pair<S, T> &t) { return pair<S, T>(s.first - t.first, s.second - t.second); }
template<class S, class T> ostream& operator<<(ostream& os, pair<S, T> p) { os << "(" << p.first << ", " << p.second << ")"; return os; }
#define X first
#define Y second
#define rep(i,n) for(ll i=0;i<(ll)(n);i++)
#define rep1(i,n) for(ll i=1;i<=(ll)(n);i++)
#define rrep(i,n) for(ll i=(ll)(n)-1;i>=0;i--)
#define rrep1(i,n) for(ll i=(ll)(n);i>0;i--)
#define REP(i,a,b) for(ll i=(ll)a;i<(ll)b;i++)
#define in(x, a, b) (a <= x && x < b)
#define all(c) c.begin(),c.end()
template<class T> bool chmax(T &a, const T &b) { if (a<b) { a = b; return 1; } return 0; }
template<class T> bool chmin(T &a, const T &b) { if (a>b) { a = b; return 1; } return 0; }
#define UNIQUE(v) v.erase(std::unique(v.begin(), v.end()), v.end());
const ll inf = 1000000001;
const ll INF = 2e18;
const ll MOD = 1000000007;
const double pi = 3.14159265358979323846;
#define Sp(p) cout<<setprecision(15)<< fixed<<p<<endl;
int dx[4] = { 1,0, -1,0 }, dy[4] = { 0,1,0,-1 };
int dx2[8] = { 1,1,0,-1,-1,-1,0,1 }, dy2[8] = { 0,1,1,1,0,-1,-1,-1 };
#define fio() cin.tie(0); ios::sync_with_stdio(false);

//bellmanford.cpp
struct edge { ll from, to, cost; };
vector<edge> es(M);

vl d(N,INF);
ll n, m;

//trueを返す場合、頂点以上に更新チェック→負のコストの閉ループあり
bool bellman_ford(ll s) {
	d[s] = 0;
	ll cnt = 0;
	bool updateFlag;
	while (true) {
		updateFlag = false;
		for (i = 0; i < m; i++) {
			if (d[es[i].from] != INF && d[es[i].to] > d[es[i].from] + es[i].cost) {
				d[es[i].to] = d[es[i].from] + es[i].cost;
				updateFlag = true;
			}
		}

		if (cnt == n - 1) return true;
		if (!updateFlag) break;

		cnt += 1;
	}
	return false;
}

//0_binary_indexed_tree.cpp
class Bit {
public:
	int n;
	vl bit; // 0-index

	Bit(int _n) { n = _n; bit.resize(n); }

	// [0, i)の和
	ll sum(int i) {
		ll s = 0;
		while (i > 0) {
			s += bit[i - 1];
			i -= i & -i;
		}
		return s;
	}

	//iは0-index
	void add(int i, ll x) {
		i++;
		while (i <= n) {
			bit[i - 1] += x;
			i += i & -i;
		}
	}

	// bitに入ってる中でx番目に小さい数を求める
	// 1番小さい数はx = 1;
	// bitに3を入れる→add(3, 1), 3を出す→add(3, -1)
	// return == nの場合x個も入っていない
	ll min_xth(int x) {
		int left = -1, right = n;
		while (left + 1 < right) {
			int mid = (left + right) / 2;
			int temp = sum(mid + 1);
			if (temp < x) {
				left = mid;
			}
			else {
				right = mid;
			}
		}
		return right;
	}


	// pを順番通りにするための交換回数
	ll bubble(vi p) {
		int n = p.size();
		ll ans = 0;
		for (int j = 0; j < n; j++) {
			ans += (j - sum(p[j] + 1));
			add(p[j], 1);
		}
		return ans;
	}
};

//bipartite.cpp
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


//bit.cpp

/*
xの一番下に立っているビットの求め方
x & -x;
*/

//nのkbit表現を表示する
void print_bit(ll n, ll k) {
	ll m = (1LL << (k - 1));;
	while (m >= 1) {
		if ((n&m)) {
			cout << 1;
		}
		else {
			cout << 0;
		}
		m >>= 1;
	}
	cout << endl;
}

//nのビット表現の部分集合を列挙する。
void part(ll n) {
	ll m = n;
	do {
		print_bit(m, 8); //部分集合に対する処理
		m = (m - 1)&n;
	} while (m != n);
}

//{0,1,...,n-1}に含まれるサイズkの部分集合を列挙
void part_size(ll n, ll k) {
	int comb = (1LL << k) - 1;
	while (comb < 1LL << n) {
		print_bit(comb, 12);
		int x = comb & -comb, y = comb + x;
		comb = ((comb & ~y) / x >> 1) | y;
	}
}


//complex.cpp
#define P complex<double>

// 許容する誤差ε
#define EPS (1e-10)
// 2つのスカラーが等しいかどうか
#define EQ(a,b) (abs((a)-(b)) < EPS)
// 2つのベクトルが等しいかどうか
#define EQV(a,b) ( EQ((a).real(), (b).real()) && EQ((a).imag(), (b).imag()) )

/*
// ベクトルaの絶対値を求める
double length = abs(a);

// 2点a,b間の距離を求める
double distance = abs(a-b);

// ベクトルaの単位ベクトルを求める
P b = a / abs(a);

// ベクトルaの法線ベクトルn1,n2を求める
P n1 = a * P(0, 1);
P n2 = a * P(0, -1);
// ベクトルaの単位法線ベクトルun1,un2を求める
P un1 = (a * P(0, +1)) / abs(a);
P un2 = (a * P(0, -1)) / abs(a);
*/

// 内積 (dot product) : a・b = |a||b|cosΘ
double dot(P a, P b) {
	return (a.real() * b.real() + a.imag() * b.imag());
}

// 外積 (cross product) : a×b = |a||b|sinΘ
double cross(P a, P b) {
	return (a.real() * b.imag() - a.imag() * b.real());
}

// 2直線の直交判定 : a⊥b <=> dot(a, b) = 0
int is_orthogonal(P a1, P a2, P b1, P b2) {
	return EQ(dot(a1 - a2, b1 - b2), 0.0);
}

// 2直線の平行判定 : a//b <=> cross(a, b) = 0
int is_parallel(P a1, P a2, P b1, P b2) {
	return EQ(cross(a1 - a2, b1 - b2), 0.0);
}

// 点cが直線a,b上にあるかないか
int is_point_on_line(P a, P b, P c) {
	return EQ(cross(b - a, c - a), 0.0);
}

// 点cが線分a,b上にあるかないか
int is_point_on_lines(P a, P b, P c) {
	// |a-c| + |c-b| <= |a-b| なら線分上
	return (abs(a - c) + abs(c - b) < abs(a - b) + EPS);
}

// 点a,bを通る直線と点cとの距離
double distance_l_p(P a, P b, P c) {
	return abs(cross(b - a, c - a)) / abs(b - a);
}

// 点a,bを端点とする線分と点cとの距離
double distance_ls_p(P a, P b, P c) {
	if (dot(b - a, c - a) < EPS) return abs(c - a);
	if (dot(a - b, c - b) < EPS) return abs(c - b);
	return abs(cross(b - a, c - a)) / abs(b - a);
}

// a1,a2を端点とする線分とb1,b2を端点とする線分の交差判定
int is_intersected_ls(P a1, P a2, P b1, P b2) {
	return (cross(a2 - a1, b1 - a1) * cross(a2 - a1, b2 - a1) < EPS) &&
		(cross(b2 - b1, a1 - b1) * cross(b2 - b1, a2 - b1) < EPS);
}

// a1,a2を端点とする線分とb1,b2を端点とする線分の交点計算
P intersection_ls(P a1, P a2, P b1, P b2) {
	P b = b2 - b1;
	double d1 = abs(cross(b, a1 - b1));
	double d2 = abs(cross(b, a2 - b1));
	double t = d1 / (d1 + d2);

	return a1 + (a2 - a1) * t;
}

// a1,a2を通る直線とb1,b2を通る直線の交差判定
int is_intersected_l(P a1, P a2, P b1, P b2) {
	return !EQ(cross(a1 - a2, b1 - b2), 0.0);
}

// a1,a2を通る直線とb1,b2を通る直線の交点計算
P intersection_l(P a1, P a2, P b1, P b2) {
	P a = a2 - a1; P b = b2 - b1;
	return a1 + a * cross(b, b1 - a1) / cross(b, a);
}

//２つのベクトルABのなす角度θを求める
//0<=theta<=180の範囲で返す
double AngleOf2Vector(P A, P B)
{
	double theta = acos(dot(A, B) / (abs(A)*abs(B)));
	theta *= 180.0 / pi;
	return theta;
}

#define ci complex<ll>
//x,yの順に辞書順ソート
bool cmp_x(const ci p, const ci q) {
	if (p.real() != q.real()) return p.real() < q.real();
	return p.imag() < q.imag();
}

//位置ベクトルa,bの外積
ll det(ci a, ci b) {
	return a.real()*b.imag() - b.real()*a.imag();
}

//位置ベクトルa,bの内積
ll dot(ci a, ci b) {
	return a.real()*b.real() + a.imag()*b.imag();
}

//ps: 全部の座標, n: 座標数。凸包の集合を返す
vector<ci> convex_hull(vector<ci> ps, int n) {
	sort(ps.begin(), ps.end(), cmp_x);
	int k = 0; //凸包の頂点数
	vector<ci> qs(n * 2); //構築中の凸包
	for (int i = 0; i < n; i++) {
		while (k > 1 && det(qs[k - 1] - qs[k - 2], ps[i] - qs[k - 1]) <= 0) k--;
		qs[k++] = ps[i];
	}
	for (int i = n - 2, t = k; i >= 0; i--) {
		while (k > t && det(qs[k - 1] - qs[k - 2], ps[i] - qs[k - 1]) <= 0) k--;
		qs[k++] = ps[i];
	}
	qs.resize(k - 1);
	return qs;
}

//追加される傾きaが単調減少、求めたい点xが単調増加の時のみ最小値を求められる。
template<typename T> class ConvexHullTrick {
  deque<pair<T, T> > lines;
  // 大小を判断する関数
  std::function<bool(T l, T r)> comp;
  
public:
  ConvexHullTrick(std::function<bool(T l, T r)> compFunc = [](T l, T r) {return l >= r; })
    :comp(compFunc)  {
  };

  // 直線l1, l2, l3のうちl2が不必要であるかどうか
  bool check(std::pair<T, T> l1, std::pair<T, T> l2, std::pair<T, T> l3) {
    if (l1 < l3) swap(l1, l3);
    return (l3.second - l2.second) * (l2.first - l1.first) >= (l2.second - l1.second) * (l3.first - l2.first);
  }

  // 直線y=ax+bを追加する
  void add(T a, T b) {
    std::pair<T, T> line(a, b);
    while (lines.size() >= 2 && check(*(lines.end() - 2), lines.back(), line))
      lines.pop_back();
    lines.push_back(line);
  }

  // i番目の直線f_i(x)に対するxの時の値を返す
  T f(int i, T x) {
    return lines[i].first * x + lines[i].second;
  }

  T get(T x) {
    // 最小値(最大値)クエリにおけるxが単調
    while (lines.size() >= 2 && comp(f(0, x), f(1, x)))
      lines.pop_front();
    return f(0, x);
  }
};

//dijkstra
void dijkstra(int s){
	priority_queue<pll, vector<pll>, greater<pll> > pq;
	int i;
	vi color(n,WHITE);
	
	d[s]=0;
	pq.push(make_pair(0,s));
	color[s]=GRAY;
	
	while(!pq.empty()){
		pll f=pq.top();
		pq.pop();
		int u=f.second;
		color[u]=BLACK;
		if(d[u]<f.first){
			continue;
		}
		for (i = 0; i < adj[u].size(); i++) {
			int v=adj[u][i].second;
			if(color[v]==BLACK){
				continue;
			}
			if (d[v] > d[u] + adj[u][i].first) {
				d[v] = d[u] + adj[u][i].first;
				pq.push(make_pair(d[v], v));
				color[v] = GRAY;
			}
		}
	}
}


//dinic

// 辺を表す構造体 {行先、容量、逆辺}
struct edge { int to; ll cap; int rev; };

class Dinic {
public:
	int n;
	vector< vector<edge> > G; //グラフの隣接リスト表現
	vl level; //sからの距離
	vi iter; //どこまで調べ終わったか


	Dinic(int n) :n(n), level(n), iter(n), G(n) {}

	//fromからtoへ向かう容量capの辺をグラフに追加する
	void add_edge(int from, int to, ll cap) {
		edge a;
		a.to = to; a.cap = cap; a.rev = G[to].size();
		G[from].push_back(a);
		a.to = from; a.cap = 0; a.rev = G[from].size() - 1;
		G[to].push_back(a);
	}

	//sからの最短距離をBFSで計算する
	void bfs(int s) {
		fill(level.begin(), level.end(), -1);
		queue<int> que;
		level[s] = 0;
		que.push(s);
		while (!que.empty()) {
			int v = que.front(); que.pop();
			for (int i = 0; i < G[v].size(); i++) {
				edge &e = G[v][i];
				if (e.cap > 0 && level[e.to] < 0) {
					level[e.to] = level[v] + 1;
					que.push(e.to);
				}
			}
		}
	}

	//増加パスをDFSで探す
	ll dfs(int v, int t, ll f) {
		if (v == t) return f;
		for (int &i = iter[v]; i < G[v].size(); i++) {
			edge &e = G[v][i];
			if (e.cap > 0 && level[v] < level[e.to]) {
				ll d = dfs(e.to, t, min(f, e.cap));
				if (d > 0) {
					e.cap -= d;
					G[e.to][e.rev].cap += d;
					return d;
				}
			}
		}
		return 0;
	}

	//sからtへの最大流を調べる
	ll max_flow(int s, int t) {
		ll flow = 0;
		for (;;) {
			bfs(s);
			if (level[t] < 0) return flow;
			fill(iter.begin(), iter.end(), 0);
			ll f;
			while ((f = dfs(s, t, INF)) > 0) {
				flow += f;
			}
		}
	}
};


//fft
typedef complex<double> P;

vector<P> fft(vector<P> v, bool rev = false) {
	int n = v.size(), i, j, m;

	for (i = 0, j = 1; j<n - 1; j++) {
		for (int k = n >> 1; k>(i ^= k); k >>= 1);
		if (i>j) swap(v[i], v[j]);
	}
	for (int m = 2; m <= n; m *= 2) {
		double deg = (rev ? -1 : 1) * 2 * acos(-1) / m;
		P wr(cos(deg), sin(deg));
		for (i = 0; i<n; i += m) {
			P w(1, 0);
			for (int j1 = i, j2 = i + m / 2; j2<i + m; j1++, j2++) {
				P t1 = v[j1], t2 = w*v[j2];
				v[j1] = t1 + t2, v[j2] = t1 - t2;
				w *= wr;
			}
		}
	}
	if (rev) rep(i, n) v[i] *= 1.0 / n;
	return v;
}

vector<P> MultPoly(vector<P> a, vector<P> b) {
	a = fft(a), b = fft(b);
	for (int i = 0; i<a.size(); i++) a[i] *= b[i];
	return fft(a, true);
}

//gauss_jordan
//Ax = bを解く
//解がないか、一意でない場合は長さ0の配列を返す
//A:n*n行列
vd gauss_jordan(vdd A, vd b) {
	int n = A.size(), i, j;
	vdd B(n, vd(n + 1));
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			B[i][j] = A[i][j];
		}
	}
	for (i = 0; i < n; i++) {
		B[i][n] = b[i];
	}

	for (i = 0; i < n; i++) {
		//注目している変数の係数の絶対値が大きい式をi番目に持ってくる
		int pivot = i;
		for (j = i; j < n; j++) {
			if (abs(B[j][i]) > abs(B[pivot][i])) {
				pivot = j;
			}
		}
		swap(B[i], B[pivot]);
		if (abs(B[i][i]) < EPS) return vd();

		for (j = i + 1; j <= n; j++) B[i][j] /= B[i][i];
		B[i][i] = 1;
		for (j = 0; j < n; j++) {
			if (i != j) {
				for (int k = i + 1; k <= n; k++) {
					B[j][k] -= B[j][i] * B[i][k];
				}
			}
		}
	}
	vd x(n);
	for (i = 0; i < n; i++) {
		x[i] = B[i][n];
	}
	return x;
}

//kruskal
vector< pair<ll, pll> > edges(M);
vector<bool> used(M, false);

ll kruskal() {
	sort(edges.begin(), edges.end());
	UnionFind uf(n);
	ll res = 0;
	for (int i = 0; i < edges.size(); i++) {
		if (!uf.same(edges[i].second.first, edges[i].second.second)) {
			uf.unite(edges[i].second.first, edges[i].second.second);
			res += edges[i].first;
			used[i] = true;
		}
	}
	return res;
}

//mat

typedef vector<Modint> vec;
typedef vector<vec> mat;

mat mul(mat &A, mat &B) {
	mat C(A.size(), vec(B[0].size()));
	for (int i = 0; i < A.size(); i++) {
		for (int k = 0; k < B.size(); k++) {
			for (int j = 0; j < B[0].size(); j++) {
				C[i][j] = C[i][j] + A[i][k] * B[k][j];
			}
		}
	}
	return C;
}

vec mul(mat &A, vec &B) {
	vec C(A.size());
	for (int i = 0; i < A.size(); i++) {
		for (int j = 0; j < B.size(); j++) {
			C[i] += A[i][j] * B[j];
		}
	}
	return C;
}


mat pow(mat A, ll n) {
	mat B(A.size(), vec(A.size()));
	for (int i = 0; i < A.size(); i++) {
		B[i][i] = 1;
	}
	while (n > 0) {
		if (n & 1)B = mul(B, A);
		A = mul(A, A);
		n >>= 1;
	}
	return B;
}

//min_cost_flow
#define MAX_V 1000

struct edge { int to, cap, cost, rev; };
int V; //頂点数
vector< vector<edge> > G(MAX_V, vector<edge>(MAX_V)); //グラフの隣接リスト表現
vi h(MAX_V); //ポテンシャル
vi dist(MAX_V); //最短距離
vi prevv(MAX_V), preve(MAX_V); //直前の頂点と辺

							   //fromからtoへ向かう容量cap,コストcostの辺をグラフに追加する
void add_edge(int from, int to, int cap, int cost) {
	edge temp;
	temp.to = to; temp.cap = cap; temp.cost = cost; temp.rev = G[to].size();
	G[from].push_back(temp);
	temp.to = from; temp.cap = 0; temp.cost = -cost; temp.rev = G[from].size() - 1;
	G[to].push_back(temp);
}

//sからtへの流量fの最小費用流を求める
//流せない場合は-1を返す
int min_cost_flow(int s, int t, int f) {
	int res = 0;
	fill(h.begin(), h.end(), 0);
	while (f > 0) {
		priority_queue<pii, vector<pii>, greater<pii> > que; //firstは最短距離、secondは頂点の番号
		fill(dist.begin(), dist.end(), inf);
		dist[s] = 0;
		que.push(pii(0, s));
		while (!que.empty()) {
			pii p = que.top(); que.pop();
			int v = p.second;
			if (dist[v] < p.first) continue;
			for (int i = 0; i < G[v].size(); i++) {
				edge &e = G[v][i];
				if (e.cap > 0 && dist[e.to] > dist[v] + e.cost + h[v] - h[e.to]) {
					dist[e.to] = dist[v] + e.cost + h[v] - h[e.to];
					prevv[e.to] = v;
					preve[e.to] = i;
					que.push(pii(dist[e.to], e.to));
				}
			}
		}
		if (dist[t] == inf) { //これ以上流せない
			return -1;
		}
		for (int v = 0; v < V; v++) {
			h[v] += dist[v];
		}
		int d = f;
		for (int v = t; v != s; v = prevv[v]) {
			d = min(d, G[prevv[v]][preve[v]].cap);
		}
		f -= d;
		res += d*h[t];
		for (int v = t; v != s; v = prevv[v]) {
			edge &e = G[prevv[v]][preve[v]];
			e.cap -= d;
			G[v][e.rev].cap += d;
		}
	}
	return res;
}



//mod_kumi
const int MAXN = 3010;

vl fact(MAXN);
vl rfact(MAXN);

ll mod_pow(ll x, ll p, ll M = MOD) {
	ll a = 1;
	while (p) {
		if (p % 2)
			a = a*x%M;
		x = x*x%M;
		p /= 2;
	}
	return a;
}

ll mod_inverse(ll a, ll M = MOD) {
	return mod_pow(a, M - 2, M);
}

void set_fact(ll n, ll M = MOD) {
	fact[0] = fact[1] = rfact[0] = rfact[1] = 1;
	for (ll i = 2; i <= n; i++) {
		fact[i] = i * fact[i - 1] % M;
		rfact[i] = mod_inverse(fact[i], M);
	}
}

ll nCr(ll n, ll r, ll M = MOD) {
	ll ret = fact[n];
	ret = (ret*rfact[r]) % M;
	ret = (ret*rfact[n - r]) % M;
	return ret;
}

// 第二種スターリング数
// 互いに区別できるn個のものを区別のないk個のグループに分けるとき,その分け方はsecondStirling[n][k]
// ただし空のグループがあってはいけない
vll secondStirling(MAXN, vl(MAXN, 0));
void setSecondStirling(ll n, ll M = MOD) {
	secondStirling[0][0] = 1;
	rep1(i, n) {
		rep(j, i + 1) {
			if (j == i) {
				secondStirling[i][j] = 1;
			}
			else if (j == 0) {
				secondStirling[i][j] = 0;
			}
			else {
				secondStirling[i][j] = (secondStirling[i - 1][j - 1] + (ll)j*secondStirling[i - 1][j] % M) % M;
			}
		}
	}
}


// 分割数
// i個の違いに区別できない品物をj個以下に分割する方法part[n][m]
vll part(MAXN + 1, vl(MAXN + 1));
void setPartition(int n, ll M = MOD) {
  part[0][0] = 1;
  rep (i, n + 1) {
    rep1 (j, n) {
      if (i - j >= 0) {
	part[i][j] = part[i - j][j] + part[i][j - 1];
      }
      else {
	part[i][j] = part[i][j - 1];
      }
      part[i][j] %= M;
    }
  }
}

//natural
ll gcd(ll a, ll b) {
	if (b > a) {
		swap(a, b);
	}
	ll r = a%b;
	while (r != 0) {
		a = b;
		b = r;
		r = a%b;
	}
	return b;
}

ll lcm(ll a, ll b) {
	return (a / gcd(a, b))*b;
}

//ax + by = gcd(a, b) となるx, yをもとめる
ll extgcd(ll a, ll b, ll& x, ll& y) {
	ll d = a;
	if (b != 0) {
		d = extgcd(b, a%b, y, x);
		y -= (a / b)*x;
	}
	else {
		x = 1; y = 0;
	}
	return d;
}

//中国剰余定理
//modの積がすごいときオーバーフローする。
//am[i].first:a_i, am[i].second:m_i
//return (x, y) y = lcm(m1, m2, ..., m_n),  x%m_i = a_i
typedef __int128 lll;
pll crt(vector<pll> am) {
	rep(i, am.size() - 1) {
		ll g, x, y, z;
		am[i].first = (am[i].first % am[i].second + am[i].second) % am[i].second;
		am[i + 1].first = (am[i + 1].first % am[i + 1].second + am[i + 1].second) % am[i + 1].second;
		g = extgcd(am[i].second, am[i + 1].second, x, y);
		if (am[i].first%g != am[i].second%g) return pll(-1, 0); //解なし
		lll lcm = (lll)am[i].second*(am[i + 1].second / g);
		if (lcm < am[i].second) return pll(-2, 0); //オーバーフロー
		ll mo = am[i + 1].second = lcm;
		lll v = am[i].first + ((lll)(am[i].second / g) * x % mo * (am[i + 1].first - am[i].first + mo) % mo);
		am[i + 1].first = (v%mo + mo) % mo;
	}
	return am.back();
}

void prime(vector<bool> &isprime, vll &soinsu) {
	ll i, j;
	isprime[0] = isprime[1] = false;
	for (i = 2; i < isprime.size(); i++) {
		if (isprime[i]) {
			soinsu[i].push_back(i);
			for (j = 2; i*j < isprime.size(); j++) {
				isprime[i*j] = false;
				soinsu[i * j].push_back(i);
				int temp = i * j;
				while (temp % i == 0) {
					temp /= i;
				}
			}
		}
	}
}

//n以下のnと互いに素な自然数の個数
//O(sqrt(n))
int eulerSingle(int n) {
	int res = n;
	for (int i = 2; i*i <= n; i++) {
		if (n%i == 0) {
			res = res / i * (i - 1);
			for (; n%i == 0; n /= i);
		}
	}
	if (n != 1) res = res / n * (n - 1);
	return res;
}


//オイラー関数の値のテーブル
//O(n)
vl euler(n + 1);
void eulerTable(int n) {
	for (i = 0; i <= n; i++) {
		euler[i] = i;
	}
	for (i = 2; i <= n; i++) {
		if (euler[i] == i) {
			for (j = i; j <= n; j += i) {
				euler[j] = euler[j] / i * (i - 1);
			}
		}
	}
}

//priorityqueue
class Cmp {
public:
	bool operator() (pii a, pii b) {
		if (a.first - a.second < b.first - b.second) {
			return false;
		}
		else {
			return true;
		}
	}
};
priority_queue<pii, vector<pii>, Cmp> pq;

//これで大きい順に出てくる
class Cmp2 {
public:
	bool operator() (int a, int b) {
		return a < b;
	}
};
priority_queue<int, vi, Cmp2> pq2;


//rolling_hash
#define MAXN 100010
const ll B1 = 100000007;
const ll B2 = 103;
const ll M = 1000000009;
vector<ll> Bpower1(MAXN);
vector<ll> Bpower2(MAXN);
vector<ll> Bpower_inv1(MAXN);
vector<ll> Bpower_inv2(MAXN);

ll mod_pow(ll x, ll p, ll M) {
	ll a = 1;
	while (p) {
		if (p % 2)
			a = a*x%M;
		x = x*x%M;
		p /= 2;
	}
	return a;
}

ll mod_inverse(ll a, ll m) {
	return mod_pow(a, m - 2, m);
}

void build_bpower() {
	Bpower1[0] = 1;
	for (int j = 1; j < MAXN; j++) {
		Bpower1[j] = Bpower1[j - 1] * B1 % M;
	}
	Bpower2[0] = 1;
	for (int j = 1; j < MAXN; j++) {
		Bpower2[j] = Bpower2[j - 1] * B2 % M;
	}
	for (int j = 0; j < MAXN; j++) {
		Bpower_inv1[j] = mod_inverse(Bpower1[j], M);
		Bpower_inv2[j] = mod_inverse(Bpower2[j], M);
	}
}



class RollingHash {
public:
	string s;
	ll n;
	vector<pll> hash;

	//sのハッシュ値を求める
	//hash[i] = s[i]*(b^(n - i - 1)) + s[i + 1]*(b^(n - i - 2)) + ... + s[n - 1] * b^0;
	RollingHash(string s) :s(s), n(s.size()) {
		hash.resize(n + 1);
		hash[s.size()].first = hash[s.size()].second = 0;
		for (int i = s.size() - 1; i >= 0; i--) {
			hash[i].first = (hash[i + 1].first + s[i] * Bpower1[s.size() - i - 1]) % M;
			hash[i].second = (hash[i + 1].second + s[i] * Bpower2[s.size() - i - 1]) % M;
		}
	}

	//i文字目からl文字のハッシュ値を求める
	pll part(int i, int l) {
		pll h = pll(hash[i].first - hash[i + l].first, hash[i].second - hash[i + l].second);
		h.first += M; h.second += M;
		h.first %= M; h.second %= M;
		h.first = h.first * Bpower_inv1[hash.size() - 1 - i - l] % M;
		h.second = h.second * Bpower_inv2[hash.size() - 1 - i - l] % M;
		return h;
	}
};


//scc
//scc : strongly connected component

int n; //頂点数
#define N 10010
vii G(N, vi()); //グラフの隣接リスト表現
vii rG(N, vi()); //辺の向きを逆にしたグラフ
vi vr; //帰りがけ順のならび
vector<bool> used(N); //すでに調べたか
vi cmp(N); //属する強連結成分のトポロジカル順序

void add_edge(int from, int to) {
	G[from].push_back(to);
	rG[to].push_back(from);
}

void dfs(int v) {
	used[v] = true;
	for (int i = 0; i < G[v].size(); i++) {
		if (!used[G[v][i]]) {
			dfs(G[v][i]);
		}
	}
	vr.push_back(v);
}

void rdfs(int v, int k) {
	used[v] = true;
	cmp[v] = k;
	for (int i = 0; i < rG[v].size(); i++) {
		if (!used[rG[v][i]]) {
			rdfs(rG[v][i], k);
		}
	}
}


int scc() {
	fill(used.begin(), used.end(), false);
	vr.clear();
	for (int v = 0; v < n; v++) {
		if (!used[v]) dfs(v);
	}
	fill(used.begin(), used.end(), false);
	int k = 0;
	for (int i = vr.size() - 1; i >= 0; i--) {
		if (!used[vr[i]]) rdfs(vr[i], k++);
	}
	return k;
}


//segment tree
class SegmentTree {
public:
	const ll MAX_N = 1 << 20;
	int n;
	vl dat;
	vl a;

	SegmentTree(int _n, vl _a) :n(_n), a(_a) { dat.resize(2 * MAX_N - 1); }
	SegmentTree() { dat.resize(2 * MAX_N - 1); }

	void init(int k, int l, int r) {
		if (r - l == 1) {
			dat[k] = a[l];
		}
		else {
			int lch = 2 * k + 1, rch = 2 * k + 2;
			init(lch, l, (l + r) / 2);
			init(rch, (l + r) / 2, r);
			dat[k] = min(dat[lch], dat[rch]);
		}
	}


	//k番目の値をaに変更
	void update(int k, ll a, int v, int l, int r) {
		if (r - l == 1) {
			dat[v] = a;
		}
		else {
			if (k < (l + r) / 2)
				update(k, a, 2 * v + 1, l, (l + r) / 2);
			else {
				update(k, a, 2 * v + 2, (l + r) / 2, r);
			}
			dat[v] = min(dat[v * 2 + 1], dat[v * 2 + 2]);
		}
	}

	//[a,b)の最小値を求める
	//後ろのほうの引数は計算の簡単のための引数
	//kは接点の番号,l,rはその接点が[l,r)に対応していることを表す
	//従って、外からはquery(a,b,0,0,n)としてよぶ
	ll query(int a, int b, int k, int l, int r) {
		if (r <= a || b <= l) {
			return INF;
		}
		if (a <= l && r <= b) {
			return dat[k];
		}
		else {
			ll ul = query(a, b, k * 2 + 1, l, (l + r) / 2);
			ll ur = query(a, b, k * 2 + 2, (l + r) / 2, r);
			return min(ul, ur);
		}
	}

};

///////////////
////sum////////
///////////////

// updateパターン
// addパターンはeval,updateのいくつかの=を+=にする, -2*INFを0にする
class LazySegmentTree {
public:
	int n;
	vl node, lazy;

	LazySegmentTree(vl a) {
		int _n = a.size();
		n = 1; while (n < _n) n *= 2;
		node.resize(2 * n - 1);
		lazy.resize(2 * n - 1, -2*INF);
		for (int i = 0; i < _n; i++) node[i + n - 1] = a[i];
		for (int i = n - 2; i >= 0; i--) {
			node[i] = node[i * 2 + 1] + node[i * 2 + 2];
		}
	}

	// k番目のノードについて遅延評価を行う
	inline void eval(int k, int l, int r) {
		if (lazy[k] != -2 * INF) {
			node[k] = (r - l) * lazy[k];
			if (r - l > 1) {
				lazy[2 * k + 1] = lazy[k]; /////
				lazy[2 * k + 2] = lazy[k]; /////
			}
			lazy[k] = -2 * INF;
		}
	}

	// [a, b)をxにする
	void add(int a, int b, ll x, int k, int l, int r) {
		// k 番目のノードに対して遅延評価を行う
		eval(k, l, r);
		if (b <= l || r <= a) return;
		if (a <= l && r <= b) {
			lazy[k] = x;
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
		return resl + resr;
	}
};


///////////
//最大値///
///////////
class LazySegmentTree {
public:
	int n;
	vl node, lazy;
	bool ismax; //trueなら最大値、falseなら最小値

	LazySegmentTree(vl a, bool _ismax) {
		ismax = _ismax;
		int _n = a.size();
		n = 1; while (n < _n) n *= 2;
		node.resize(2 * n - 1, INF * (1 - (int)ismax * 2));
		lazy.resize(2 * n - 1, 0);
		for (int i = 0; i < _n; i++) node[i + n - 1] = a[i];
		for (int i = n - 2; i >= 0; i--) {
			if (ismax) node[i] = max(node[i * 2 + 1], node[i * 2 + 2]);
			else node[i] = min(node[i * 2 + 1], node[i * 2 + 2]);
		}
	}

	// k番目のノードについて遅延評価を行う
	inline void eval(int k, int l, int r) {
		if (lazy[k] != 0) {
			node[k] += lazy[k];
			if (r - l > 1) {
				lazy[2 * k + 1] += lazy[k]; /////
				lazy[2 * k + 2] += lazy[k]; /////
			}
			lazy[k] = 0;
		}
	}

	void add(int a, int b, ll x, int k, int l, int r) {
		// k 番目のノードに対して遅延評価を行う
		eval(k, l, r);
		if (b <= l || r <= a) return;
		if (a <= l && r <= b) {
			lazy[k] += x; //////
			eval(k, l, r);
		}
		else {
			add(a, b, x, 2 * k + 1, l, (l + r) / 2);
			add(a, b, x, 2 * k + 2, (l + r) / 2, r);
			if (ismax) node[k] = max(node[2 * k + 1], node[2 * k + 2]);
			else node[k] = min(node[2 * k + 1], node[2 * k + 2]);
		}
	}

	ll getmax(int a, int b, int k, int l, int r) {
		eval(k, l, r);
		if (b <= l || r <= a) return 0;
		if (a <= l && r <= b) return node[k];
		ll resl = getmax(a, b, 2 * k + 1, l, (l + r) / 2);
		ll resr = getmax(a, b, 2 * k + 2, (l + r) / 2, r);
		if (ismax) return max(resl, resr);
		else return min(resl, resr);
	}

};

//suffix_array
#define N 20010
int n, k;
vi rnk(N + 1);
vi tmp(N + 1);

// (rank[i], rank[i + k]) と (rank[j], rank[j + k]) を比較
bool compare_sa(int i, int j) {
  if (rnk[i] != rnk[j]) return rnk[i] < rnk[j];
  else {
    int ri = i + k <= n ? rnk[i + k] : -1;
    int rj = j + k <= n ? rnk[j + k] : -1;
    return ri < rj;
  }
}

// 文字列sの接尾辞配列を構築、ダブリングの原理
vi construct_sa(string s) {
  n = s.size();
  vi sa(n + 1);
  //最初は一文字、ランクは文字コードにすれば良い
  for (int i = 0; i <= n; i++) {
    sa[i] = i;
    rnk[i] = i < n ? s[i] : -1;
  }

  for (k = 1; k <= n; k *= 2) {
    sort(sa.begin(), sa.end(), compare_sa);

    //一旦tmpに次のランクを計算しそれをrankに移す
    tmp[sa[0]] = 0;
    for (int i = 1; i <= n; i++) {
      tmp[sa[i]] = tmp[sa[i - 1]] + (compare_sa(sa[i - 1], sa[i]) ? 1 : 0);
    }
    for (int i = 0; i <= n; i++) {
      rnk[i] = tmp[i];
    }
  }
  return sa;
}

//文字列sとその接尾辞配列saを受け取り、高さ配列lcpを返す
vi construct_lcp(string s, vi sa) {
  int n = s.length();
  vi lcp(n);
  for (int i = 0; i <= n; i++) rnk[sa[i]] = i;

  int h = 0;
  lcp[0] = 0;
  for (int i = 0; i < n; i++) {
    //文字列中での位置iの接尾辞と、接尾辞配列中でその一つ前の設備時のLCPを求める
    int j = sa[rnk[i] - 1];

    //hを先頭の分1減らし、後ろが一致しているだけ増やす
    if (h > 0) h--;
    for (; j + h < n && i + h < n; h++) {
      if (s[j + h] != s[i + h]) break;
    }

    lcp[rnk[i] - 1] = h;
  }
  return lcp;
}


//unionfind
class UnionFind {
public:
	int n;
	vi par; //親
	vi ran; //木の深さ
	vi num; //要素数

	UnionFind(int _n) {
		n = _n;
		par.resize(n); ran.resize(n); num.resize(n);
		for (int i = 0; i < n; i++) {
			par[i] = i; ran[i] = 0; num[i] = 1;
		}
	}

	//木の根を求める
	int find(int x) {
		if (par[x] == x) {
			return x;
		}
		else {
			return par[x] = find(par[x]);
		}
	}

	//xとyの属する集合を併合
	void unite(int x, int y) {
		x = find(x); y = find(y);
		int numsum = num[x] + num[y];
		if (x == y) {
			return;
		}
		if (ran[x]<ran[y]) {
			par[x] = y;
		}
		else {
			par[y] = x;
			if (ran[x] == ran[y]) {
				ran[x]++;
			}
		}
		num[x] = num[y] = numsum;
	}

	//xとyが同じ集合に属するか否か
	bool same(int x, int y) {
		return find(x) == find(y);
	}

};

//部分永続UF
class PermanenceUF {
public:
	int n;
	vi par; //親
	vi ran; //木の深さ
	vector<vector<pll> > num; //要素数
	vl time; //木が更新された時の時刻

	PermanenceUF(int _n) {
		n = _n;
		par.resize(n); ran.resize(n);
		num.resize(n); time.resize(n);
		for (int i = 0; i < n; i++) {
			par[i] = i; ran[i] = 0; time[i] = INF;
			num[i] = vector<pll>(1, pii(0, 1));
		}
	}

	//時刻tの時の木の根を求める
	int find(ll t, int x) {
		if (time[x] > t) return x;
		else return find(t, par[x]);
	}

	//時刻tにxとyの属する集合を併合
	//tは単調増加している
	void unite(ll t, int x, int y) {
		x = find(t, x); y = find(t, y);
		ll numsum = num[x].back().second + num[y].back().second;
		if (x == y) {
			return;
		}
		if (ran[x] < ran[y]) {
			swap(x, y);
		}
		par[y] = x;
		time[y] = t;
		num[x].push_back(pll(t, numsum));
		if (ran[x] == ran[y]) {
			ran[x]++;
		}
	}

	//時刻tのxとyが同じ集合に属するか否か
	bool same(ll t, int x, int y) {
		return find(t, x) == find(t, y);
	}

	//時刻tの時の要素xを含む集合のサイズ
	int size(ll t, int x) {
		int root = find(t, x);
		int left = 0, right = num[root].size();
		while (left + 1 < right) {
			int mid = (left + right) / 2;
			if (num[root][mid].first <= t) {
				left = mid;
			}
			else {
				right = mid;
			}
		}
		return num[root][left].second;
	}

};

//数直線状のものに有効(年齢、身長など)
class WeightedUF {
public:
  vi par, ran, num;
  vl diff_weight; //親ノード(根ノードではない)との値の差分
  
  WeightedUF(int n) {
    par.resize(n); ran.resize(n);
    num.resize(n); diff_weight.resize(n);
    for (int i = 0; i < n; i++) {
      par[i] = i; ran[i] = 0;
      num[i] = 1; diff_weight[i] = 0;
    }
  }

  //木の根を求める
  int find(int x) {
    if (par[x] == x) {
      return x;
    }
    else {
      int root = find(par[x]);
      diff_weight[x] += diff_weight[par[x]];
      return par[x] = root;
    }
  }

  ll weight(int x) {
    find(x); //経路圧縮
    return diff_weight[x];
  }

  //xからみたyの重み
  ll diff(int x, int y) {
    if (!same(x, y)) {
      return -INF;
    }
    else {
      return weight(y) - weight(x);
    }
  }
  
  //xからみたyの重みがwになるように併合
  bool unite(int x, int y, ll w) {
    w += weight(x); w -= weight(y);
    x = find(x); y = find(y);
    int numsum = num[x] + num[y];
    if (x == y) {
      if (diff(x, y) == w) {
	return true;
      }
      else {
	return false;
      }
    }
    if (ran[x]<ran[y]) {
      swap(x, y);
      w = -w;
    }
    par[y] = x;
    if (ran[x] == ran[y]) {
	ran[x]++;
    }
    diff_weight[y] = w;
    num[x] = num[y] = numsum;
    return true;
  }

  //xとyが同じ集合に属するか否か
  bool same(int x, int y) {
    return find(x) == find(y);
  }

};
