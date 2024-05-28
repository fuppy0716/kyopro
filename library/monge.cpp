// verify: https://atcoder.jp/contests/colopl2018-final-open/submissions/53984605
struct MonotoneMinima {
    // A は monge 行列であるとする
    // この時、各行の最小値を高速に求める
    // ただし、A を全て与えると O(n^2) かかるため f(i, j) で A[i][j] を返す関数を与える
    // また、オフラインでしか解けず、DP のようにある行の値が別の行の値に依存するケースでは使えない
    // A が正方行列でない場合も解けるはずだが未検証

    vector<long long> ans; // i 行目の最小値
    vector<int> argmin;    // i 行目の最小値の列番号

    MonotoneMinima(int n) : ans(n, INF), argmin(n) {}

    void solve() {
        calc(0, ans.size(), 0, ans.size());
    }

    void calc(int u, int d, int l, int r) {
        if (u >= d || l >= r) return;

        // A[u:d)[l:r) に対する最小値を計算する
        int i = (u + d) / 2;
        for (int j = l; j < r; j++) {
            if (f(i, j) < ans[i]) {
                ans[i] = f(i, j);
                argmin[i] = j;
            }
        }

        calc(u, i, l, argmin[i] + 1);
        calc(i + 1, d, argmin[i], r);
    }

    long long f(int i, int j) {
        // TODO: return the value of A[i][j]
        return 0;
    }
};
