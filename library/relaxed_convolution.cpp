
// 提出例: https://atcoder.jp/contests/abc315/submissions/44828688
class RelaxedConvolution {
    // https://qiita.com/Kiri8128/items/1738d5403764a0e26b4c
  public:
    vector<mint> a, b;
    vector<mint> c;

    RelaxedConvolution() {}

    mint query(mint add_a, mint add_b) {
        // a と b にそれぞれ add_a と add_b を加え、c の最新項を返す
        a.push_back(add_a);
        b.push_back(add_b);

        int q = a.size() - 1;
        int len = 1;
        vector<tuple<int, int, int>> yxl;
        while (true) {
            if (q % len == max(0, len - 2) && q >= 2 * len - 2) {
                int i = len - 1, j = q - len + 1;
                yxl.emplace_back(i, j, len);
                if (i != j) {
                    yxl.emplace_back(j, i, len);
                }
                len *= 2;
            } else {
                break;
            }
        }

        for (auto [y, x, l] : yxl) {
            // a[y : y+l) と b[x : x+l) を畳み込む
            auto aa = get_part_a(y, y + l);
            auto bb = get_part_b(x, x + l);

            auto cc = convolution(aa, bb);
            for (int i = x + y; i < x + y + cc.size(); i++) {
                while (i >= c.size()) {
                    c.push_back(0);
                }
                c[i] += cc[i - x - y];
            }
        }

        return c[q];
    }

    vector<mint> get_part_a(int l, int r) {
        return {a.begin() + l, a.begin() + r};
    }
    vector<mint> get_part_b(int l, int r) {
        return {b.begin() + l, b.begin() + r};
    }
};
