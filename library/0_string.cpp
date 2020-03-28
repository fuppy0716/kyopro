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
    for (int i = 0; i < n; i++) res[i] = this->operator()(x, y);
    return res;
  }
} rnd;


using ull = unsigned long long;
class RollingHash {
public:
  
  const ull MASK30 = (1UL << 30) - 1;
  const ull MASK31 = (1UL << 31) - 1;
  const ull M = (1UL << 61) - 1;
  const ull B = rnd(2, M >> 1);
  const ull POSITIVIZER = M * 3;;
  
  vector<ull> hash;
  vector<ull> Bpower;

  RollingHash(string s) {
    int n = s.size();
    hash.resize(n + 1); Bpower.resize(n + 1);
    Bpower[0] = 1;
    
    for (int i = 0; i < n; i++) {
      hash[i + 1] = _calc_mod(_mul(hash[i], B) + s[i]);
      Bpower[i + 1] = _calc_mod(_mul(Bpower[i], B));
    }
  }

  //S[l, r)
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
    if (val > M) val -= M;
    return val;
  }
};

// S と S[i:|S|-1] の最長共通接頭辞の長さ」を記録した配列 A を O(|S|) で構築
vi z_algorithm(string s) {
  int n = s.size();
  vi a(n);
  int c = 0;
  for (int i = 1; i < n; i++){
    if (i+a[i-c] < c+a[c]) {
      a[i] = a[i-c];
    } else {
      int j = max(0, c+a[c]-i);
      while (i+j < n && s[j] == s[i+j]) ++j;
      a[i] = j;
      c = i;
    }
  }
  a[0] = n;
  return a;
}



class Manacher {
public:
  string s, t;
  vi a;

  Manacher (string s): s(s) {
    rep (i, s.size()) {
      t.push_back(s[i]);
      if (i != s.size() - 1) t.push_back('?');
    }
    a.resize(t.size());
    int i = 0, j = 0;
    while (i < t.size()) {
      while (i-j >= 0 && i+j < t.size() && t[i-j] == t[i+j]) ++j;
      a[i] = j;
      int k = 1;
      while (i-k >= 0 && i+k < t.size() && k+a[i-k] < j) a[i+k] = a[i-k], ++k;
      i += k; j -= k;
    }
  }

  // 文字iを中心とする回文の長さ
  int length(int i) {
    int len_ori = 2*a[2*i] - 1;
    if (len_ori % 4 == 1) return len_ori / 2 + 1;
    if (len_ori % 4 == 3) return len_ori / 2;
    assert(false);
  }

  // i, i+1を中心とする回文の長さ
  int length(int i, int j) {
    assert(j == i + 1);
    int len_ori = 2*a[2*i + 1] - 1;
    if (len_ori % 4 == 1) return len_ori / 2;
    if (len_ori % 4 == 3) return len_ori / 2 + 1;
    assert(false);
  }
};

