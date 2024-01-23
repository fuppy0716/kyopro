
template <typename T>
class SegmentTree {
  public:
    using F = function<T(T &, T &)>;
    int n;
    vector<T> dat;
    T e;
    F query_func;
    F update_func;

    SegmentTree(vector<T> a, F query_func, F update_func, T e) : n(a.size()), query_func(query_func), update_func(update_func), e(e) {
        if (n == 0) {
            a.push_back(e);
            n++;
        }
        dat.resize(4 * n);
        init(0, 0, n, a);
    }

    void init(int k, int l, int r, vector<T> &a) {
        if (r - l == 1) {
            dat[k] = a[l];
        } else {
            int lch = 2 * k + 1, rch = 2 * k + 2;
            init(lch, l, (l + r) / 2, a);
            init(rch, (l + r) / 2, r, a);
            dat[k] = query_func(dat[lch], dat[rch]);
        }
    }

    void update(int k, T a, int v, int l, int r) {
        if (r - l == 1) {
            dat[v] = update_func(dat[v], a);
        } else {
            if (k < (l + r) / 2)
                update(k, a, 2 * v + 1, l, (l + r) / 2);
            else {
                update(k, a, 2 * v + 2, (l + r) / 2, r);
            }
            dat[v] = query_func(dat[v * 2 + 1], dat[v * 2 + 2]);
        }
    }

    void update(int k, T a) {
        update(k, a, 0, 0, n);
    }

    T query(int a, int b, int k, int l, int r) {
        if (r <= a || b <= l) {
            return e;
        }
        if (a <= l && r <= b) {
            return dat[k];
        } else {
            T ul = query(a, b, k * 2 + 1, l, (l + r) / 2);
            T ur = query(a, b, k * 2 + 2, (l + r) / 2, r);
            return query_func(ul, ur);
        }
    }

    T query(int a, int b) {
        return query(a, b, 0, 0, n);
    }

    int find(int a, int b, int k, int l, int r, int x) {
        if (dat[k] < x || r <= a || b <= l) return -1;
        if (l + 1 == r) {
            if (dat[k] >= x)
                return l;
            else
                return -1;
        }
        int rv = find(a, b, 2 * k + 2, (l + r) / 2, r, x);
        if (rv != -1) return rv;
        return find(a, b, 2 * k + 1, l, (l + r) / 2, x);
    }
};

template <typename T>
class Zaatsu {
    bool is_build;
    vector<T> elements;

  public:
    Zaatsu() : is_build(false) {}

    void add(T x) {
        elements.push_back(x);
    }

    void add(vector<T> x) {
        for (int i = 0; i < (int)x.size(); i++) {
            elements.push_back(x[i]);
        }
    }

    int build() {
        sort(elements.begin(), elements.end());
        UNIQUE(elements);
        is_build = true;
        return elements.size();
    }

    int operator[](T x) {
        assert(is_build);
        return lower_bound(elements.begin(), elements.end(), x) - elements.begin();
    }

    T original(int i) {
        assert(is_build);
        return elements[i];
    }
};

class UnionFind {
  private:
    vi par_;
    vi ran_;
    vi num_;
    vi edge_num_;

  public:
    int n;
    int g;

    UnionFind(int _n) {
        n = _n;
        g = n;
        par_.resize(n);
        ran_.resize(n);
        num_.resize(n);
        edge_num_.resize(n);
        for (int i = 0; i < n; i++) {
            par_[i] = i;
            ran_[i] = 0;
            num_[i] = 1;
            edge_num_[i] = 0;
        }
    }

    int find(int x) {
        if (par_[x] == x) {
            return x;
        } else {
            return par_[x] = find(par_[x]);
        }
    }

    void unite(int x, int y) {
        x = find(x);
        y = find(y);
        int numsum = num_[x] + num_[y];
        int edge_numsum = edge_num_[x] + edge_num_[y];
        if (x == y) {
            edge_num_[x]++;
            return;
        }
        if (ran_[x] < ran_[y]) {
            par_[x] = y;
        } else {
            par_[y] = x;
            if (ran_[x] == ran_[y]) {
                ran_[x]++;
            }
        }
        num_[x] = num_[y] = numsum;
        edge_num_[x] = edge_num_[y] = edge_numsum + 1;
        g--;
    }

    bool same(int x, int y) {
        return find(x) == find(y);
    }

    int num(int x) {
        return num_[find(x)];
    }

    int edge_num(int x) {
        return edge_num_[find(x)];
    }
};

vector<pii> sweep(vector<pll> xy) {
    // 各点について、自分から見て 0 ~ 45 度以内にいる点（右が強い右上）で最も近い点を返す
    int n = xy.size();
    Zaatsu<ll> za_y;
    rep(i, xy.size()) {
        za_y.add(xy[i].second);
    }

    int cnt = za_y.build();

    auto f = [&](pll a, pll b) { return min(a, b); };
    SegmentTree<pll> seg(vector<pll>(n, pll(INF, INF)), f, f, pll(INF, INF));

    using P = pair<pll, int>;
    vector<P> xyi(n);
    rep(i, n) {
        xyi[i] = {xy[i], i};
    }

    // y が小さく x が大きい右下領域からみる
    sort(all(xyi), [](const P &xy1, const P &xy2) {
        return xy1.first.second - xy1.first.first < xy2.first.second - xy2.first.first;
    });

    vector<pii> ret;
    for (auto [xy, u] : xyi) {
        int y_idx = za_y[xy.second];
        // 自分より y_idx が大きい範囲で、x + y が最小
        pll mi = seg.query(y_idx, cnt);
        if (mi.second != INF) {
            ret.emplace_back(u, mi.second);
        }
        seg.update(y_idx, pll(xy.first + xy.second, u));
    }
    return ret;
}

pair<ll, vector<pii>> manhattan_mst(vector<pll> xy) {
    // https://knuu.github.io/manhattan_mst.html#fn:2
    vector<pii> edge_cands;

    rep(i, 2) {
        rep(j, 2) {
            rep(k, 2) {
                vector<pii> temp = sweep(xy);
                edge_cands.insert(
                    edge_cands.end(), temp.begin(), temp.end());

                // y = x で反転
                rep(l, xy.size()) {
                    swap(xy[l].first, xy[l].second);
                }
            }
            // x = 0 で反転
            rep(l, xy.size()) {
                xy[l].first *= -1;
            }
        }
        // y = 0 で反転
        rep(l, xy.size()) {
            xy[l].second *= -1;
        }
    }

    sort(all(edge_cands), [&](const pii &uv1, const pii &uv2) {
        auto [u1, v1] = uv1;
        auto [u2, v2] = uv2;
        return abs(xy[u1].first - xy[v1].first) + abs(xy[u1].second - xy[v1].second) < abs(xy[u2].first - xy[v2].first) + abs(xy[u2].second - xy[v2].second);
    });

    UnionFind uf(xy.size());
    ll ans = 0;
    vector<pii> used_edges;
    for (auto [u, v] : edge_cands) {
        if (!uf.same(u, v)) {
            ans += abs(xy[u].first - xy[v].first) + abs(xy[u].second - xy[v].second);
            used_edges.emplace_back(u, v);
            uf.unite(u, v);
        }
    }
    return {ans, used_edges};
}
