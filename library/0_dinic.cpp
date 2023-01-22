#include "bits/stdc++.h"
using namespace std;

#define DEBUG(x) cout << #x << ": " << x << endl;
#define DEBUG_VEC(v)                   \
    cout << #v << ":";                 \
    for (int i = 0; i < v.size(); i++) \
        cout << " " << v[i];           \
    cout << endl

typedef long long ll;
#define vi vector<int>
#define vl vector<ll>
#define vii vector<vector<int>>
#define vll vector<vector<ll>>
#define vs vector<string>
#define pii pair<int, int>
#define pis pair<int, string>
#define psi pair<string, int>
const int inf = 1000000001;
const ll INF = 1e16;
#define MOD 1000000007
#define mod 1000000009
#define pi 3.14159265358979323846
#define Sp(p) cout << setprecision(15) << fixed << p << endl;
int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
int dx2[8] = {1, 1, 0, -1, -1, -1, 0, 1}, dy2[8] = {0, 1, 1, 1, 0, -1, -1, -1};

// 辺を表す構造体 {行先、容量、逆辺}
struct edge {
    int to;
    ll cap;
    int rev;
};

class Dinic {
  public:
    int n;
    vector<vector<edge>> G; //グラフの隣接リスト表現
    vl level;               //sからの距離
    vi iter;                //どこまで調べ終わったか

    Dinic(int n) : n(n), level(n), iter(n), G(n) {}

    //fromからtoへ向かう容量capの辺をグラフに追加する
    void add_edge(int from, int to, ll cap) {
        edge a;
        a.to = to;
        a.cap = cap;
        a.rev = G[to].size();
        G[from].push_back(a);
        a.to = from;
        a.cap = 0;
        a.rev = G[from].size() - 1;
        G[to].push_back(a);
    }

    //sからの最短距離をBFSで計算する
    void bfs(int s) {
        fill(level.begin(), level.end(), -1);
        queue<int> que;
        level[s] = 0;
        que.push(s);
        while (!que.empty()) {
            int v = que.front();
            que.pop();
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

// https://atcoder.jp/contests/abc259/submissions/38249179
// https://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=7370054#1
class BurnBury {
  public:
    int V;
    int S, T;

    long long offset_value;

    vector<tuple<int, int, long long>> edges;

    BurnBury(int n) : V(n + 2), S(n), T(n + 1), offset_value(0) {}

    void x0_y1_lose(int x, int y, long long z) {
        edges.emplace_back(x, y, z);
    }

    void x0_gain(int x, long long z) {
        offset_value += z;
        edges.emplace_back(S, x, z);
    }

    void x0_lose(int x, long long z) {
        edges.emplace_back(x, T, z);
    }

    void x1_gain(int x, long long z) {
        offset_value += z;
        edges.emplace_back(x, T, z);
    }

    void x1_lose(int x, long long z) {
        edges.emplace_back(S, x, z);
    }

    void x0_y0_gain(int x, int y, long long z) {
        offset_value += z;
        int w = V;
        edges.emplace_back(S, w, z);
        edges.emplace_back(w, x, INF);
        edges.emplace_back(w, y, INF);
        V++;
    }

    void x1_y1_gain(int x, int y, long long z) {
        offset_value += z;
        int w = V;
        edges.emplace_back(w, T, z);
        edges.emplace_back(x, w, INF);
        edges.emplace_back(y, w, INF);
        V++;
    }

    long long solve() {
        Dinic din(V);
        for (auto [from, to, val] : edges) {
            din.add_edge(from, to, val);
        }

        long long f = din.max_flow(S, T);
        return -f + offset_value;
    }
};
