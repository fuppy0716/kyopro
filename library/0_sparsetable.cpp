// https://ei1333.github.io/algorithm/sparse-table.html
template< typename T >
struct SparseTable
{
  vector< vector< T > > st;
  using F = function<T(T&, T&)>;
  F f;

  SparseTable() {}

  SparseTable(const vector< T > &v, const F &f) :f(f)
  {
    int b = 0;
    while((1 << b) <= v.size()) ++b;
    st.assign(b, vector< T >(1 << b));
    for(int i = 0; i < v.size(); i++) {
      st[0][i] = v[i];
    }
    for(int i = 1; i < b; i++) {
      for(int j = 0; j + (1 << i) <= (1 << b); j++) {
        st[i][j] = f(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
      }
    }
  }

  inline T query(int l, int r) // [l, r)
  {
    int b = 32 - __builtin_clz(r - l) - 1;
    return (f(st[b][l], st[b][r - (1 << b)]));
  }
};


template< typename Semigroup >
struct DisjointSparseTable {
  using F = function< Semigroup(Semigroup, Semigroup) >;
  const F f;
  vector< vector< Semigroup > > st;

  DisjointSparseTable(const vector< Semigroup > v, const F f) : f(f) {

    int b = 0;
    while((1 << b) <= v.size()) ++b;
    st.resize(b, vector< Semigroup >(v.size(), Semigroup()));
    for(int i = 0; i < v.size(); i++) st[0][i] = v[i];
    for(int i = 1; i < b; i++) {
      int shift = 1 << i;
      for(int j = 0; j < v.size(); j += shift << 1) {
        int t = min(j + shift, (int) v.size());
        st[i][t - 1] = v[t - 1];
        for(int k = t - 2; k >= j; k--) st[i][k] = f(v[k], st[i][k + 1]);
        if(v.size() <= t) break;
        st[i][t] = v[t];
        int r = min(t + shift, (int) v.size());
        for(int k = t + 1; k < r; k++) st[i][k] = f(st[i][k - 1], v[k]);
      }
    }
  }

  Semigroup query(int l, int r) {
    if(l >= --r) return st[0][l];
    int p = 31 - __builtin_clz(l ^ r);
    return f(st[p][l], st[p][r]);
  }
};
