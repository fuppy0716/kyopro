template <typename Semigroup>
struct DisjointSparseTable {
    using F = function<Semigroup(Semigroup, Semigroup)>;
    F f;
    vector<vector<Semigroup>> st;

    DisjointSparseTable() {}

    DisjointSparseTable(const vector<Semigroup> v, const F f) : f(f) {

        int b = 0;
        while ((1 << b) <= v.size())
            ++b;
        st.resize(b, vector<Semigroup>(v.size(), Semigroup()));
        for (int i = 0; i < v.size(); i++)
            st[0][i] = v[i];
        for (int i = 1; i < b; i++) {
            int shift = 1 << i;
            for (int j = 0; j < v.size(); j += shift << 1) {
                int t = min(j + shift, (int)v.size());
                st[i][t - 1] = v[t - 1];
                for (int k = t - 2; k >= j; k--)
                    st[i][k] = f(v[k], st[i][k + 1]);
                if (v.size() <= t) break;
                st[i][t] = v[t];
                int r = min(t + shift, (int)v.size());
                for (int k = t + 1; k < r; k++)
                    st[i][k] = f(st[i][k - 1], v[k]);
            }
        }
    }

    Semigroup query(int l, int r) {
        if (l >= --r) return st[0][l];
        int p = 31 - __builtin_clz(l ^ r);
        return f(st[p][l], st[p][r]);
    }
};

pii f(pii a, pii b) {
    return min(a, b);
}

class SuffixArray {
  public:
    string s;
    int n;
    vi sa;
    vi inv_sa;
    vi lcp;
    vi rnk;
    DisjointSparseTable<pii> dst_inv_sa;

    SuffixArray() {}

    SuffixArray(string s) : s(s), n(s.size()) {
        sa = construct_sa(s);
        inv_sa.resize(n + 1);
        rep(i, n + 1) inv_sa[sa[i]] = i;
        lcp = construct_lcp(s, sa);
        function<int(int, int)> f1 = [](int a, int b) { return min(a, b); };

        vector<pii> inv_sa_with_idx(n + 1);
        rep(i, n + 1) inv_sa_with_idx[i] = pii(inv_sa[i], i);
        dst_inv_sa = DisjointSparseTable<pii>(inv_sa_with_idx, f);
    }

    int min_suffix(int l, int r) {
        // [l, r) から始まる最小の suffix の index
        return dst_inv_sa.query(l, r).second;
    }

    vi construct_sa(string s) {
        vi sa(n + 1);
        rnk.resize(n + 1);
        vi tmp(n + 1);
        // 最初は一文字、ランクは文字コードにすれば良い
        for (int i = 0; i <= n; i++) {
            sa[i] = i;
            rnk[i] = i < n ? s[i] : -1;
        }

        for (int k = 1; k <= n; k *= 2) {
            auto compare_sa = [=](int i, int j) {
                if (rnk[i] != rnk[j])
                    return rnk[i] < rnk[j];
                else {
                    int ri = i + k <= n ? rnk[i + k] : -1;
                    int rj = j + k <= n ? rnk[j + k] : -1;
                    return ri < rj;
                }
            };
            sort(sa.begin(), sa.end(), compare_sa);

            // 一旦tmpに次のランクを計算しそれをrankに移す
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

    // 文字列sとその接尾辞配列saを受け取り、高さ配列lcpを返す
    vi construct_lcp(string s, vi sa) {
        int n = s.length();
        vi lcp(n);
        for (int i = 0; i <= n; i++)
            rnk[sa[i]] = i;

        int h = 0;
        lcp[0] = 0;
        for (int i = 0; i < n; i++) {
            // 文字列中での位置iの接尾辞と、接尾辞配列中でその一つ前の設備時のLCPを求める
            int j = sa[rnk[i] - 1];

            // hを先頭の分1減らし、後ろが一致しているだけ増やす
            if (h > 0) h--;
            for (; j + h < n && i + h < n; h++) {
                if (s[j + h] != s[i + h]) break;
            }

            lcp[rnk[i] - 1] = h;
        }
        return lcp;
    }
};

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

std::random_device seed_gen;
std::mt19937 engine(seed_gen());

using ull = unsigned long long;
const ull MASK30 = (1ULL << 30) - 1;
const ull MASK31 = (1ULL << 31) - 1;
const ull M = (1ULL << 61) - 1;
const ull B = rnd(129, M);
const ull POSITIVIZER = M * ((1ULL << 3) - 1);

class RollingHash {
  public:
    vector<ull> hash;
    vector<ull> Bpower;

    RollingHash() {}

    RollingHash(vi s) {
        int n = s.size();
        hash.resize(n + 1);
        Bpower.resize(n + 1);
        Bpower[0] = 1;
        hash[0] = 0;

        for (int i = 0; i < n; i++) {
            hash[i + 1] = _calc_mod(_mul(hash[i], B) + (ull)s[i]);
            Bpower[i + 1] = _calc_mod(_mul(Bpower[i], B));
        }
    }

    // S[l, r)
    ull part(int l, int r) {
        return _calc_mod(hash[r] + POSITIVIZER - _mul(hash[l], Bpower[r - l]));
    }

    ull _mul(ull a, ull b) {
        ull au = a >> 31;
        ull ad = a & MASK31;
        ull bu = b >> 31;
        ull bd = b & MASK31;
        ull mid = ad * bu + au * bd;
        ull midu = mid >> 30;
        ull midd = mid & MASK30;
        return au * bu * 2 + midu + (midd << 31) + ad * bd;
    }

    ull _calc_mod(ull val) {
        val = (val & M) + (val >> 61);
        if (val >= M) val -= M;
        return val;
    }
};

struct SuffixArrayOfPart {
    // https://www.mimuw.edu.pl/~kociumaka/files/cpm2014a.pdf

    string s;
    SuffixArray sa;
    RollingHash rh;

    vector<vector<int>> suf_len;
    vii b;

    SuffixArrayOfPart(string s_) {
        s = s_;
        sa = SuffixArray(s);
        rh = RollingHash(vi(all(s)));

        // suf_len[i][j] := s[i] で終わる接尾辞で、長さが min(2^j, i + 1) であるものの長さ
        suf_len.resize(s.size());
        rep(i, s.size()) {
            suf_len[i].push_back(1);
            int full_len = i + 1;
            while (suf_len[i].back() < full_len) {
                int x = suf_len[i].back() * 2;
                chmin(x, full_len);
                suf_len[i].push_back(x);
            }
        }

        // b[i][j] := s[i] で終わる長さが suf_len[i][j] である文字列の接尾辞の最小のものが、
        // s[i] で終わる長さが suf_len[i][j - 1] である文字列の接尾辞の最小のものよりも小さいかどうか。
        // b[i][0] は常に 1
        b.resize(s.size());
        rep(i, s.size()) {
            b[i].resize(suf_len[i].size());
            b[i][0] = 1;
            int best_len = 1;
            int best_start_idx = i;
            rep1(j, suf_len[i].size() - 1) {
                int now_len = suf_len[i][j], pre_len = suf_len[i][j - 1];
                int l = i + 1 - now_len, r = i + 1 - pre_len;

                int start_idx = sa.min_suffix(l, r);
                if (sa.inv_sa[start_idx] > sa.inv_sa[best_start_idx]) {
                    b[i][j] = 0;
                    continue;
                }
                if (rh.part(start_idx, start_idx + best_len) == rh.part(best_start_idx, best_start_idx + best_len)) {
                    b[i][j] = 0;
                } else {
                    b[i][j] = 1;
                    best_start_idx = start_idx;
                    best_len = i + 1 - start_idx;
                }
            }
        }
    }

    int query(int l, int r) {
        // s[l, r) の接尾辞のうち、辞書順最小のものの開始位置
        int p = sa.min_suffix(l, r);

        int nl = -1;
        rrep(j, suf_len[r - 1].size()) {
            if (suf_len[r - 1][j] > r - l) continue;
            if (b[r - 1][j] == 1) {
                nl = r - suf_len[r - 1][j];
                break;
            }
        }
        int q = sa.min_suffix(nl, r);

        if (rh.part(q, r) == rh.part(p, p + (r - q))) {
            return q;
        } else {
            return p;
        }
    }
};
