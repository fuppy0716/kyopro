
struct WordSizeTree {
    // https://judge.yosupo.jp/submission/205544
    using ull = unsigned long long;
    int W = 64;
    int B = 6;

    ull low_mask = (1 << B) - 1;

    vector<vector<ull>> exists;
    int height;

    WordSizeTree(int n) {
        // [0, n) を扱う

        height = 1;
        int current = W;
        exists.push_back(vector<ull>(1, 0));
        while (current < n) {
            height++;
            exists.push_back(vector<ull>(current, 0));
            current *= W;
        }
    }

    bool empty() const {
        return exists[0][0] == 0;
    }

    void insert(int x) {
        for (int i = height - 1; i >= 0; i--) {
            int j = x >> B;
            int k = x & low_mask;
            exists[i][j] |= 1ULL << k;
            x >>= B;
        }
    }

    void erase(int x) {
        for (int i = height - 1; i >= 0; i--) {
            int j = x >> B;
            int k = x & low_mask;
            exists[i][j] &= ~(1ULL << k);
            if (exists[i][j] != 0) {
                return;
            }
            x >>= B;
        }
    }

    int count(int x) {
        return (exists[height - 1][x >> B] >> (x & low_mask)) & 1;
    }

    int get_min(int x) {
        // x 以上の最小の要素を返す
        int d = height - 1, i = x;
        // 深さ d で i 以上の最小を探す
        // 深く潜る時は増やすビットは 0 埋めする
        while (true) {
            if (d == -1) {
                return -1;
            }
            if ((i >> B) >= exists[d].size()) {
                return -1;
            }
            int k = i & low_mask;
            // k 以上の最小のビットを探す
            ull mask = (~(0ULL)) << k;
            int b = ctz(exists[d][i >> B] & mask);
            if (b == -1) {
                d--;
                i >>= B;
                i++;
                continue;
            }
            i = ((i >> B) << B) + b;
            if (d == height - 1) {
                break;
            }
            d++;
            i <<= B;
        }
        return i;
    }

    int get_max(int x) {
        // x 以下の最大値の要素を返す
        int d = height - 1, i = x;
        // 深さ d で i 以下の最大を探す
        // 深く潜る時は増やすビットは 1 埋めする
        while (true) {
            if (d == -1) {
                return -1;
            }
            if (i < 0) {
                return -1;
            }
            int k = i & low_mask;
            // k 以下の最大のビットを探す
            ull mask = (~(0ULL)) >> (63 - k);
            int b = clz(exists[d][i >> B] & mask);
            if (b == -1) {
                d--;
                i >>= B;
                i--;
                continue;
            }
            i = ((i >> B) << B) + b;
            if (d == height - 1) {
                break;
            }
            d++;
            i <<= B;
            i += low_mask;
        }
        return i;
    }

  private:
    inline int ctz(ull n) {
        // 一番下の立っているビットは下から何番目か（0-indexed）
        return n ? __builtin_ctzll(n) : -1;
    }
    inline int clz(ull n) {
        // 一番上の立っているビットは下から何番目か（0-indexed）
        return n ? 63 - __builtin_clzll(n) : -1;
    }
};