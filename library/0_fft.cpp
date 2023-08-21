#include "bits/stdc++.h"
using namespace std;

#define DEBUG(x) cout << #x << ": " << x << endl;
#define DEBUG_VEC(v)                   \
    cout << #v << ":";                 \
    for (int i = 0; i < v.size(); i++) \
        cout << " " << v[i];           \
    cout << endl

typedef long long ll;
#define vi vector<int>
#define vl vector<ll>
#define vii vector<vector<int>>
#define vll vector<vector<ll>>
#define vs vector<string>
#define pii pair<int, int>
#define pis pair<int, string>
#define psi pair<string, int>
#define pll pair<ll, ll>
#define fi first
#define se second
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep1(i, n) for (int i = 1; i <= (int)(n); i++)
#define all(c) c.begin(), c.end()
const int inf = 1000000001;
const ll INF = 2e18 * 2;
#define MOD 1000000007
#define mod 1000000009
#define pi 3.14159265358979323846
#define Sp(p) cout << setprecision(15) << fixed << p << endl;
int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
int dx2[8] = {1, 1, 0, -1, -1, -1, 0, 1}, dy2[8] = {0, 1, 1, 1, 0, -1, -1, -1};

// https://ei1333.github.io/luzhiled/snippets/math/fast-fourier-transform.html
//https://atcoder.jp/contests/jsc2019-final/submissions/7783091
namespace FastFourierTransform {
using real = double;

struct C {
    real x, y;

    C() : x(0), y(0) {}

    C(real x, real y) : x(x), y(y) {}

    inline C operator+(const C &c) const { return C(x + c.x, y + c.y); }

    inline C operator-(const C &c) const { return C(x - c.x, y - c.y); }

    inline C operator*(const C &c) const { return C(x * c.x - y * c.y, x * c.y + y * c.x); }

    inline C conj() const { return C(x, -y); }
};

const real PI = acosl(-1);
int base = 1;
vector<C> rts = {{0, 0},
                 {1, 0}};
vector<int> rev = {0, 1};

void ensure_base(int nbase) {
    if (nbase <= base) return;
    rev.resize(1 << nbase);
    rts.resize(1 << nbase);
    for (int i = 0; i < (1 << nbase); i++) {
        rev[i] = (rev[i >> 1] >> 1) + ((i & 1) << (nbase - 1));
    }
    while (base < nbase) {
        real angle = PI * 2.0 / (1 << (base + 1));
        for (int i = 1 << (base - 1); i < (1 << base); i++) {
            rts[i << 1] = rts[i];
            real angle_i = angle * (2 * i + 1 - (1 << base));
            rts[(i << 1) + 1] = C(cos(angle_i), sin(angle_i));
        }
        ++base;
    }
}

void fft(vector<C> &a, int n) {
    assert((n & (n - 1)) == 0);
    int zeros = __builtin_ctz(n);
    ensure_base(zeros);
    int shift = base - zeros;
    for (int i = 0; i < n; i++) {
        if (i < (rev[i] >> shift)) {
            swap(a[i], a[rev[i] >> shift]);
        }
    }
    for (int k = 1; k < n; k <<= 1) {
        for (int i = 0; i < n; i += 2 * k) {
            for (int j = 0; j < k; j++) {
                C z = a[i + j + k] * rts[j + k];
                a[i + j + k] = a[i + j] - z;
                a[i + j] = a[i + j] + z;
            }
        }
    }
}

vector<int64_t> multiply(const vector<int> &a, const vector<int> &b) {
    int need = (int)a.size() + (int)b.size() - 1;
    int nbase = 1;
    while ((1 << nbase) < need)
        nbase++;
    ensure_base(nbase);
    int sz = 1 << nbase;
    vector<C> fa(sz);
    for (int i = 0; i < sz; i++) {
        int x = (i < (int)a.size() ? a[i] : 0);
        int y = (i < (int)b.size() ? b[i] : 0);
        fa[i] = C(x, y);
    }
    fft(fa, sz);
    C r(0, -0.25 / (sz >> 1)), s(0, 1), t(0.5, 0);
    for (int i = 0; i <= (sz >> 1); i++) {
        int j = (sz - i) & (sz - 1);
        C z = (fa[j] * fa[j] - (fa[i] * fa[i]).conj()) * r;
        fa[j] = (fa[i] * fa[i] - (fa[j] * fa[j]).conj()) * r;
        fa[i] = z;
    }
    for (int i = 0; i < (sz >> 1); i++) {
        C A0 = (fa[i] + fa[i + (sz >> 1)]) * t;
        C A1 = (fa[i] - fa[i + (sz >> 1)]) * t * rts[(sz >> 1) + i];
        fa[i] = A0 + A1 * s;
    }
    fft(fa, sz >> 1);
    vector<int64_t> ret(need);
    for (int i = 0; i < need; i++) {
        ret[i] = llround(i & 1 ? fa[i >> 1].y : fa[i >> 1].x);
    }
    return ret;
}
}; // namespace FastFourierTransform

// NTT<998244353, 3>で宣言
// グローバルで一度宣言すれば何度でも使用可能
// https://atcoder.jp/contests/jsc2019-final/submissions/7782824
template <int mod, int primitiveroot>
struct NTT {
    vector<vector<int>> rts, rrts;
    void ensure_base(int N) {
        if (rts.size() >= N) return;
        rts.resize(N), rrts.resize(N);
        for (int i = 1; i < N; i <<= 1) {
            if (rts[i].size()) continue;
            int w = mod_pow(primitiveroot, (mod - 1) / (i * 2));
            int rw = inverse(w);
            rts[i].resize(i), rrts[i].resize(i);
            rts[i][0] = 1, rrts[i][0] = 1;
            for (int k = 1; k < i; k++) {
                rts[i][k] = mul(rts[i][k - 1], w);
                rrts[i][k] = mul(rrts[i][k - 1], rw);
            }
        }
    }

    inline int mod_pow(int x, int n) {
        int ret = 1;
        while (n > 0) {
            if (n & 1) ret = mul(ret, x);
            x = mul(x, x);
            n >>= 1;
        }
        return ret;
    }

    inline int inverse(int x) {
        return mod_pow(x, mod - 2);
    }

    inline int add(int x, int y) {
        x += y;
        if (x >= mod) x -= mod;
        return x;
    }

    inline int mul(int a, int b) {
        return int(1LL * a * b % mod);
    }

    void DiscreteFourierTransform(vector<int> &F, bool rev) {
        const int N = (int)F.size();
        ensure_base(N);
        for (int i = 0, j = 1; j + 1 < N; j++) {
            for (int k = N >> 1; k > (i ^= k); k >>= 1)
                ;
            if (i > j) swap(F[i], F[j]);
        }
        for (int i = 1; i < N; i <<= 1) {
            for (int j = 0; j < N; j += i * 2) {
                for (int k = 0; k < i; k++) {
                    int s = F[j + k], t = mul(F[j + k + i], rev ? rrts[i][k] : rts[i][k]);
                    F[j + k] = add(s, t), F[j + k + i] = add(s, mod - t);
                }
            }
        }
        if (rev) {
            int temp = inverse(N);
            for (int i = 0; i < N; i++)
                F[i] = mul(F[i], temp);
        }
    }

    vector<int> Multiply(const vector<int> &A, const vector<int> &B) {
        int sz = 1;
        while (sz < A.size() + B.size() - 1)
            sz <<= 1;
        vector<int> F(sz), G(sz);
        for (int i = 0; i < A.size(); i++)
            F[i] = A[i];
        for (int i = 0; i < B.size(); i++)
            G[i] = B[i];
        DiscreteFourierTransform(F, false);
        DiscreteFourierTransform(G, false);
        for (int i = 0; i < sz; i++)
            F[i] = mul(F[i], G[i]);
        DiscreteFourierTransform(F, true);
        F.resize(A.size() + B.size() - 1);
        return F;
    }
};

// https://atcoder.jp/contests/abc315/submissions/44828348
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
        if (q == 0) {
            c.push_back(add_a * add_b);
            return c.back();
        }

        int len = 1;
        vector<tuple<int, int, int>> yxl;
        while (len <= q) {
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

int main() {
    int n;
    cin >> n;
    vector<P> a(2 * n + 10), b(2 * n + 10);
    ll x = n;
    while (x & (x - 1))
        x++;
    x *= 4;
    a.resize(x);
    b.resize(x);
    rep1(i, n) {
        int c, d;
        cin >> c >> d;
        a[i].real(c);
        b[i].real(d);
    }
    auto ans = MultPoly(a, b);
    rep1(i, 2 * n) {
        cout << (ll)(ans[i].real() + 0.5) << endl;
    }
}
