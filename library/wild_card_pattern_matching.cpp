
struct dice {
    mt19937 mt;
    dice() : mt(chrono::steady_clock::now().time_since_epoch().count()) {}
    // [0, x)の一様乱数
    ll operator()(ll x) { return this->operator()(0, x); }
    // [x, y)の一様乱数
    ll operator()(ll x, ll y) {
        uniform_int_distribution<ll> dist(x, y - 1);
        return dist(mt);
    }
    vl operator()(int n, ll x, ll y) {
        vl res(n);
        for (int i = 0; i < n; i++)
            res[i] = this->operator()(x, y);
        return res;
    }
} rnd;

// Depends on ac-library
using mint = modint998244353;

template <int wildcard>
struct WildCardPatternMatching {
    // 参考: https://qiita.com/MatsuTaku/items/cd5581fab97d7e74a7b3
    // 提出例: https://judge.yosupo.jp/submission/208072
    vector<int> text, pattern;

    vector<mint> t1, t2, t3;
    vector<mint> p1, p2, p3;

    vector<mint> c;

    WildCardPatternMatching(string text_, string pattern_) {
        // text_ の長さを n として
        // O(n log n)
        convert_text_and_pattern(text_, pattern_);

        for (int t : text) {
            t1.push_back(mint(t));
            t2.push_back(t1.back() * t);
            t3.push_back(t2.back() * t);
        }
        for (int i = pattern.size() - 1; i >= 0; i--) {
            int p = pattern[i];
            p1.push_back(mint(p));
            p2.push_back(p1.back() * p);
            p3.push_back(p2.back() * p);
        }

        c = add_vec(convolution(t3, p1), add_vec(mul_vec(convolution(t2, p2), -2), convolution(t1, p3)));
    }

    bool is_match(int k) {
        // パターンの長さを m として
        // text[k, k+m) と pattern が一致してるかを O(1) で取得
        int m = pattern.size();
        assert(0 <= k and k + m <= text.size());
        return c[k + m - 1].val() == 0;
    }

  private:
    void convert_text_and_pattern(string t, string p) {
        string con = t + p;
        unordered_map<int, int> mp;
        unordered_set<int> used;
        for (char c : con) {
            if (c == wildcard || mp.count(c)) {
                continue;
            }
            while (true) {
                int nc = rnd(1, 998244353);
                if (!used.count(nc)) {
                    used.insert(nc);
                    mp[c] = nc;
                    break;
                }
            }
        }

        text = convert(t, mp);
        pattern = convert(p, mp);
    }

    vector<int> convert(string t, unordered_map<int, int> &mp) {
        vector<int> ret;
        for (char c : t) {
            if (c == wildcard) {
                ret.push_back(0);
            } else {
                ret.push_back(mp[c]);
            }
        }
        return ret;
    }

    vector<mint> add_vec(const vector<mint> &a, const vector<mint> &b) {
        int sz = max(a.size(), b.size());
        vector<mint> ret(sz);
        for (int i = 0; i < sz; i++) {
            if (i < a.size()) {
                ret[i] += a[i];
            }
            if (i < b.size()) {
                ret[i] += b[i];
            }
        }
        return ret;
    }

    vector<mint> mul_vec(vector<mint> a, int x) {
        for (mint &v : a) {
            v *= x;
        }
        return a;
    }
};
