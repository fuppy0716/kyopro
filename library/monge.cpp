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

// verify: https://atcoder.jp/contests/abc355/submissions/54010127
template <typename T>
struct Larsch {
    // https://noshi91.hatenablog.com/entry/2023/02/18/005856
    // 二次元 DP において、DP[i] = min_{j < i} {DP[j] + C[j][i]} という形の遷移を高速に行う
    // ここで、C は monge 行列である
    // A[0][j] := 0, A[i][j] := dp[j] + C[j][i] とすると、A も monge 行列であり、かつ対角成分を含まない下三角行列である
    // このような行列に対して、各行の最小値を求めるクエリを高速に処理する

    using F = function<T(int, int)>;

    int n;
    // (j, i) -> 状態 j から状態 i に遷移するときのコスト
    // alien DP でペナルティを考慮する場合は、ペナルティも考慮済みの関数
    F edge;

    vector<T> mini;     // i 行目の暫定の最小値
    vector<int> argmin; // i 行目の暫定の最小値の列番号

    Larsch(int n, F edge) : n(n), edge(edge) {
        // n は dp の次元数。そのため、よくある設定だと n = (入力の N) + 1 となる
        mini.resize(n, numeric_limits<T>::max());
        argmin.resize(n, 0);
        mini[0] = 0;

        check(n - 1, 0);
        solve(0, n - 1);
    }

    ll get_ans() const {
        return mini[n - 1];
    }

    ll get(int i, int j) {
        // i 行目の j 列目の値を返す
        // dp[j] + edge(j, i) であり、dp[i] = mini[i] である
        return mini[j] + edge(j, i);
    }

    void check(int i, int k) {
        if (get(i, k) < mini[i]) {
            mini[i] = get(i, k);
            argmin[i] = k;
        }
    }

    void solve(int l, int r) {
        if (r - l == 1) return;
        int m = (l + r) / 2;
        for (int k = argmin[l]; k <= argmin[r]; k++) {
            check(m, k);
        }
        solve(l, m);
        for (int k = l + 1; k <= m; k++) {
            check(r, k);
        }
        solve(m, r);
    }
};

// verify: https://atcoder.jp/contests/abc355/submissions/54010127
// verify: https://atcoder.jp/contests/abc218/submissions/54010487
// solve_dp の引数はペナルティ
// k は本来使用したい辺の数
// 最小化問題を解いている
// max_penalty は辺の最大値の 3 倍程度で良い。大きくしすぎるとオーバーフローに注意
template <typename T>
long long alien_dp(function<T(long long)> solve_dp, long long max_penalty, long long k) {
    // ng だとペナルティが大きすぎる, ok はちょうど良いか小さい
    long long ok = -max_penalty, ng = max_penalty;
    while (ng - ok > 2) {
        long long x0 = (2 * ok + ng) / 3, x1 = (ok + 2 * ng) / 3;

        // ペナルティが小さすぎるとき -> たくさん辺を使うのでちょうど k 回使った時よりも val - k * x がお得になり、小さくなる
        // ペナルティが大きすぎる時 -> 辺を全く使わなくても val - k * x が小さくなる
        // ちょうど良い時に最大値を取る
        long long val0 = solve_dp(x0), val1 = solve_dp(x1);
        val0 -= k * x0, val1 -= k * x1;
        if (val0 <= val1) {
            ok = x0;
        } else {
            ng = x1;
        }
    }

    long long ans = -INF;
    for (long long x = ok; x <= ng; x++) {
        chmax(ans, solve_dp(x) - k * x);
    }
    return ans;
}
