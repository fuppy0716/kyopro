template <typename T>
struct RangeSum {
    vector<T> sum;

    RangeSum(vector<T> &a) {
        int n = a.size();
        sum.resize(n + 1);
        sum[0] = 0;
        rep(i, n) {
            sum[i + 1] = sum[i] + a[i];
        }
    }

    T get(int l, int r) {
        // [l, r)
        return sum[r] - sum[l];
    }
};
