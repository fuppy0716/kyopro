
vector<int> popcount_table(1 << 16, 0);

void build_popcount_table() {
    for (int i = 0; i < (1 << 16); i++) {
        popcount_table[i] = __builtin_popcount(i);
    }
}

struct SuccinctBitVector {
    // 簡潔ビットベクトル
    // https://miti-7.hatenablog.com/entry/2018/04/15/155638#fn:2

    int n;

    static constexpr int large_block_size = 512;
    static constexpr int small_block_size = 16;

    // sum_large[i]: [0, 512 * i) の 1 の個数
    vector<int> sum_large;
    // sum_small[i]: 512 / 16 = 32 より [(i // 32) * 512, 16 * i) の 1 の個数（すなわち同じ large_block 内の手前の 1 の個数）
    vector<int> sum_small;
    // bits[i]: i 番目の small_block に含まれる 16 ビットを整数にしたもの
    vector<int> bits;

    bool is_built;

    SuccinctBitVector(int n = 0) : n(n) {
        is_built = false;

        int large_block_num = (n + large_block_size - 1) / large_block_size + 1;
        int small_block_num = (n + small_block_size - 1) / small_block_size + 1;

        sum_large.assign(large_block_num + 1, 0);
        sum_small.assign(small_block_num + 1, 0);
        bits.assign(small_block_num, 0);

        if (popcount_table[1] == 0) {
            // 初期化忘れ防止
            build_popcount_table();
        }
    }

    void set_bit(int i) {
        assert(not is_built);
        bits[i / small_block_size] |= (1 << (i % small_block_size));
    }

    void build() {
        assert(not is_built);
        is_built = true;

        int sum = 0, prev_large = 0;
        for (int i = 0; i <= n; i++) {
            if (i % large_block_size == 0) {
                sum_large[i / large_block_size] = sum;
                prev_large = sum;
            }
            if (i % small_block_size == 0) {
                sum_small[i / small_block_size] = sum - prev_large;
            }
            if (i != n) {
                sum += (bits[i / small_block_size] >> (i % small_block_size)) & 1;
            }
        }
    }

    int access(int i) {
        // i 番目の bit を返す
        assert(is_built);
        assert(i < n);

        return (bits[i / small_block_size] >> (i % small_block_size)) & 1;
    }

    int rank(int i, bool b) {
        // [0, i) の中の b の個数
        assert(is_built);
        assert(i <= n);

        if (!b) {
            return i - rank(i, 1);
        }
        int large_block_idx = i / large_block_size;
        int small_block_idx = i / small_block_size;
        int bit_num = i % small_block_size;
        return sum_large[large_block_idx] + sum_small[small_block_idx] + popcount_table[bits[small_block_idx] & ((1 << bit_num) - 1)];
    }

    int rank_range(int l, int r, bool b) {
        // [l, r) の中の b の個数
        assert(is_built);
        assert(l <= r);
        assert(r <= n);
        return rank(r, b) - rank(l, b);
    }
};

// verify
// rank: https://judge.yosupo.jp/submission/186705
// rank: https://judge.yosupo.jp/submission/186711
// quantile: https://judge.yosupo.jp/submission/186735
template <int bit_size>
struct WaveletMatrix {
    // https://miti-7.hatenablog.com/entry/2018/04/28/152259

    int n;
    // mat[i]: 上位から i ビット目に関する SuccinctBitVector
    SuccinctBitVector mat[bit_size];
    // zero_num[i]: 上位から i ビット目の 0 の個数
    int zero_num[bit_size];

    // 上位から i ビット目に関する、そのビットが 0, 1 の要素の重みの累積和
    // rank の計算に使用
    // メモリを落としたい場合はここを削除するべき
    vector<ll> zero_sums[bit_size], one_sums[bit_size];

    WaveletMatrix(vector<ll> a, vector<ll> w = {}) : n(a.size()) {
        // w は各点 a の重み
        // 指定されていないときは全て 1 とする
        if (w.size() == 0) {
            w.resize(n, 1);
        }

        rep(i, bit_size) {
            mat[i] = SuccinctBitVector(n);
            zero_sums[i].assign(n + 1, 0);
            one_sums[i].assign(n + 1, 0);

            ll mask = 1LL << (bit_size - i - 1);
            rep(j, n) {
                if (a[j] & mask) {
                    mat[i].set_bit(j);
                    one_sums[i][j + 1] = one_sums[i][j] + w[j];
                    zero_sums[i][j + 1] = zero_sums[i][j];
                } else {
                    one_sums[i][j + 1] = one_sums[i][j];
                    zero_sums[i][j + 1] = zero_sums[i][j] + w[j];
                }
            }
            mat[i].build();

            vector<ll> na(n), nw(n);
            int idx = 0;
            rep(j, n) {
                if ((a[j] & mask) == 0) {
                    na[idx] = a[j];
                    nw[idx++] = w[j];
                }
            }
            zero_num[i] = idx;
            rep(j, n) {
                if ((a[j] & mask) == mask) {
                    na[idx] = a[j];
                    nw[idx++] = w[j];
                }
            }
            swap(a, na);
            swap(w, nw);
        }
    }

    ll access(int i) {
        ll ret = 0;
        rep(j, bit_size) {
            int b = mat[j].access(i);
            ret |= (ll)b << (bit_size - j - 1);
            if (b == 1) {
                i = zero_num[j] + mat[j].rank(i, b);
            } else {
                i = mat[j].rank(i, b);
            }
        }
        return ret;
    }

    tuple<ll, ll, ll> rank(int l, int r, ll x) {
        // [l, r) の中の x 未満の個数、x の個数、x 以上の重みの和を返す。
        // 重みを指定していない時は要素の個数と同等である。
        ll small = 0, just = 0, large = 0;

        rep(i, bit_size) {
            int b = (x >> (bit_size - i - 1)) & 1;
            int nl, nr;
            if (b == 0) {
                nl = mat[i].rank(l, b);
                nr = mat[i].rank(r, b);

                large += one_sums[i][r] - one_sums[i][l];
                if (i == bit_size - 1) {
                    just += zero_sums[i][r] - zero_sums[i][l];
                }
            } else {
                nl = zero_num[i] + mat[i].rank(l, b);
                nr = zero_num[i] + mat[i].rank(r, b);

                small += zero_sums[i][r] - zero_sums[i][l];
                if (i == bit_size - 1) {
                    just += one_sums[i][r] - one_sums[i][l];
                }
            }
            l = nl;
            r = nr;
        }
        return make_tuple(small, just, large);
    }

    ll quantile(int l, int r, int k) {
        // [l, r) の中で k 番目に小さい要素を返す
        // 重みは特に使われず、要素の個数のみを考慮する
        assert(0 <= k and k < r - l);
        ll ret = 0;
        rep(i, bit_size) {
            int num0 = mat[i].rank_range(l, r, 0);
            int num1 = r - l - num0;

            int nl, nr;
            if (k < num0) {
                // k 番目に小さい要素の上から i ビット目は 0
                nl = mat[i].rank(l, 0);
                nr = mat[i].rank(r, 0);
            } else {
                // k 番目に小さい要素の上から i ビット目は 1
                ret += 1LL << (bit_size - i - 1);
                nl = zero_num[i] + mat[i].rank(l, 1);
                nr = zero_num[i] + mat[i].rank(r, 1);
                k -= num0;
            }
            l = nl;
            r = nr;
        }
        return ret;
    }
};
