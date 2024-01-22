// https://judge.yosupo.jp/submission/185427
template <typename T>
struct DoubleEndedPriorityQueue {
    multiset<T> st;

    DoubleEndedPriorityQueue() {
    }

    void add(T x) {
        st.insert(x);
    }

    T pop_min() {
        assert(!st.empty());
        T res = *st.begin();
        st.erase(st.begin());
        return res;
    }

    T pop_max() {
        assert(!st.empty());
        T res = *st.rbegin();
        st.erase(prev(st.end()));
        return res;
    }
};
