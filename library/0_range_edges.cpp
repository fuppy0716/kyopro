
class RangeEdges {
    // https://twitter.com/noshi91/status/1193177214453338113
    // https://codeforces.com/contest/786/submission/85182398
    // https://atcoder.jp/contests/nikkei2019-2-qual/submissions/14711404
    public:
    int n; // 問題で与えられた頂点数
    int V; // 構築するグラフの頂点数
    vector<vector<pll>> G;

    // 0 ~ n - 1: 各頂点
    // n, n + 2, n + 4, ..., n + 2 * (K - 1): out側の各区間（図の上側）
    // n + 1, n + 3, ..., n + 2 * K - 1: in側の各区間（図の下側）
    // n + 2 * K ~ 辺を貼ることによって増えたスーパー頂点

    RangeEdges(int n): n(n), V(n) {
        G.resize(9 * n);
        init(0, 0, n);
    }

    void init(int k, int l, int r) {
        if (r - l == 1) {
            G[n + 2 * k].push_back(pll(0, l));
            G[l].push_back(pll(0, n + 2 * k + 1));
            chmax(V, n + 2 * k + 2);
            return;
        }

        int lch = 2 * k + 1, rch = 2 * k + 2;
        G[n + 2 * k].push_back(pll(0, n + 2 * lch));
        G[n + 2 * k].push_back(pll(0, n + 2 * rch));
        G[n + 2 * lch + 1].push_back(pll(0, n + 2 * k + 1));
        G[n + 2 * rch + 1].push_back(pll(0, n + 2 * k + 1));
        init(lch, l, (l + r) / 2);
        init(rch, (l + r) / 2, r);
    }

    void get_ranges(int a, int b, int k, int l, int r, vector<int>& res) {
        if (r <= a || b <= l) {
            return;
        }
        if (a <= l && r <= b) {
            res.push_back(k);
            return;
        }
        else {
            get_ranges(a, b, k * 2 + 1, l, (l + r) / 2, res);
            get_ranges(a, b, k * 2 + 2, (l + r) / 2, r, res);
            return;
        }
    }

    // [lr1.first, lr1.second) -> [lr2.first, lr2.second)にcostの辺を貼る
    void add_edge(pii lr1, pii lr2, ll cost) {
        vector<int> in_ranges;
        get_ranges(lr1.first, lr1.second, 0, 0, n, in_ranges);
        rep (i, in_ranges.size()) in_ranges[i] = n + in_ranges[i] * 2 + 1;
        vector<int> out_ranges;
        get_ranges(lr2.first, lr2.second, 0, 0, n, out_ranges);
        rep (i, out_ranges.size()) out_ranges[i] = n + out_ranges[i] * 2;
        // DEBUG_VEC(in_ranges);
        // DEBUG_VEC(out_ranges);

        V += 2;
        while (G.size() < V) G.push_back(vector<pll>());

        for (int u: in_ranges) {
            G[u].push_back(pll(0, V - 2));
        }
        G[V - 2].push_back(pll(cost, V - 1));
        for (int v: out_ranges) {
            G[V - 1].push_back(pll(0, v));
        }
    }

    vl dijkstra(int s) {
        vl dist(V, INF);
        dist[s] = 0;
        priority_queue<pll, vector<pll>, greater<pll>> pq;
        pq.push(pll(0, s));
        while (pq.size()) {
            pll temp = pq.top();
            pq.pop();
            int u = temp.second;
            ll cost = temp.first;
            if (dist[u] < cost) continue;
            rep (i, G[u].size()) {
                int v = G[u][i].second;
                ll ncost = cost + G[u][i].first;
                if (dist[v] > ncost) {
                    dist[v] = ncost;
                    pq.push(pll(ncost, v));
                }
            }
        }

        dist.resize(n);
        return dist;
    }    
};