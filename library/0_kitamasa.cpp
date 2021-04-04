
/*
k項線線型化式を解く。
最初のk項 a_0, a_1, ..., a_{k-1} と
遷移 a_n = d_0 * a_{n-k} + d_1 * a_{n-k+1} + ... + d_{k-1} * a_{n-1} の d
が与えられる。
f(n) = (x_0, x_1, ..., x_{k-1}) を求める。ただし、
a_n = x_0 * a_0 + ... + x_{k-1} * a_{k-1}

https://atcoder.jp/contests/tdpc/submissions/21499077
*/
template <typename T>
class Kitamasa {
public:
    vector<T> a, d;
    int k;

    Kitamasa(vector<T> a, vector<T> d): a(a), d(d), k(a.size()) {
        assert(a.size() == d.size());
    }

    vector<T> next(vector<T> x) {
        vector<T> res(k);
        res[0] = x[k - 1] * d[0];
        for (int i = 1; i < k; i++) {
            res[i] = x[i - 1] + x[k - 1] * d[i];
        }
        return res;
    }

    vector<T> twice(vector<T> x, int n) {
        vector<vector<T>> fs(k);
        fs[0] = x;
        for (int i = 1; i < k; i++) {
            fs[i] = next(fs[i - 1]);
        }

        if (2 * n <= n + k - 1) {
            return fs[n];
        }

        vector<T> res(k);
        for (int i = 0; i < k; i++) {
            for (int j = 0; j < k; j++) {
                res[i] += x[j] * fs[j][i];
            }
        }
        return res;
    }

    vector<T> f(ll n) {
        if (n <= k) {
            if (n == k) {
                return d;
            }
            else {
                vector<T> res(k);
                res[n] = 1;
                return res;
            }
        }

        vector<T> res = f(n / 2);
        res = twice(res, n / 2);

        if (n % 2 == 1) res = next(res);
        return res;
    }

    // a_n を求める（数列の n+1 番目の値であることに注意）
    T solve(ll n) {
        vector<T> x = f(n);
        T res = 0;
        for (int i = 0; i < k; i++) {
            res += x[i] * a[i];
        }
        return res;
    }
};
