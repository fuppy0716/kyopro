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
const int inf = 1000000001;
const ll INF = 1e16;
#define MOD 1000000007
#define mod 1000000009
#define pi 3.14159265358979323846
#define Sp(p) cout << setprecision(15) << fixed << p << endl;
int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};

const int MAXN = 200010;

vl fact(MAXN);
vl rfact(MAXN);

ll mod_pow(ll x, ll p, ll M = MOD) {
    if (p < 0) {
        x = mod_pow(x, M - 2, M);
        p = -p;
    }
    x %= M;
    ll a = 1;
    while (p) {
        if (p % 2)
            a = a * x % M;
        x = x * x % M;
        p /= 2;
    }
    return a;
}

ll mod_inverse(ll a, ll M = MOD) {
    return mod_pow(a, M - 2, M);
}

void set_fact(ll n, ll M = MOD) {
    fact[0] = 1;
    for (ll i = 1; i <= n; i++) {
        fact[i] = i * fact[i - 1] % M;
    }
    rfact[n] = mod_inverse(fact[n], M);
    for (ll i = n - 1; i >= 0; i--) {
        rfact[i] = (i + 1) * rfact[i + 1] % M;
    }
}

// http://drken1215.hatenablog.com/entry/2018/06/08/210000
ll nCr(ll n, ll r, ll M = MOD) {
    if (r > n) return 0;
    assert(fact[2] == 2);
    ll ret = fact[n];
    if (rfact[r] == 0) {
        rfact[r] = mod_inverse(fact[r], M);
    }
    ret = (ret * rfact[r]) % M;
    if (rfact[n - r] == 0) {
        rfact[n - r] = mod_inverse(fact[n - r], M);
    }
    ret = (ret * rfact[n - r]) % M;
    return ret;
}

ll nHr(ll n, ll r) {
    return nCr(n + r - 1, r);
}

// M は素数である
// M が小さい時に有効（r >= M のとき通常の方はゼロ除算が発生する）
ll nCr_lucas(ll n, ll r, ll M) {
    vi np, rp;
    while (n > 0 or r > 0) {
        np.push_back(n % M);
        rp.push_back(r % M);
        n /= M;
        r /= M;
    }
    ll ans = 1;
    rep(i, np.size()) {
        ans *= nCr(np[i], rp[i], M);
        ans %= M;
    }
    return ans;
}

// noimi のライブラリ拝借した
// https://codeforces.com/contest/1942/submission/254160773
// +1 n 個 -1 m 個で累積和 >= 0
mint Catalan(int n, int m) { return nCr(n + m, m) - nCr(n + m, m - 1); }

// +1 n 個 -1 m 個で累積和 > -k
mint Catalan2(int n, int m, int k) {
    if (m < k) return nCr(n + m, m);
    if (m < n + k) return nCr(n + m, m) - nCr(n + m, m - k);
    return 0;
}

// +1 n 個 -1 m 個で累積和 < +k
mint Catalan3(int n, int m, int k) { return Catalan2(m, n, k); }

// 前計算 O(m) くらい
// クエリ O(log n) くらい
struct BinomialPrimePow {
    int p, q;
    int m;
    vl ppow;
    vl fact_except_p, fact_except_p_inv;
    BinomialPrimePow() {}
    BinomialPrimePow(int p, int q) : p(p), q(q) {
        m = 1;
        ppow.push_back(1);
        rep(_, q) {
            m *= p;
            ppow.push_back(m);
        }

        fact_except_p.resize(m);
        fact_except_p[0] = 1;
        for (int i = 1; i < m; i++) {
            fact_except_p[i] = fact_except_p[i - 1];
            if (i % p != 0) {
                fact_except_p[i] *= i;
                fact_except_p[i] %= m;
            }
        }

        fact_except_p_inv.resize(m);
        // ax + My = 1 のとき mod M で x は a の逆元
        ll temp;
        extgcd(fact_except_p[m - 1], m, fact_except_p_inv[m - 1], temp);
        fact_except_p_inv[m - 1] = (fact_except_p_inv[m - 1] % m + m) % m;
        assert(fact_except_p[m - 1] * fact_except_p_inv[m - 1] % m == 1);

        for (int i = m - 2; i >= 0; i--) {
            fact_except_p_inv[i] = fact_except_p_inv[i + 1];
            if ((i + 1) % p != 0) {
                fact_except_p_inv[i] *= i + 1;
                fact_except_p_inv[i] %= m;
            }
        }
    }

    ll nCk(ll n, ll k) {
        // nCk mod p^q を求める
        if (n < k or k < 0) return 0;
        ll r = n - k;

        if (p == 2 and q == 1) return !((~n) & r);

        ll e0 = ej(n / p) - ej(k / p) - ej(r / p);
        if (e0 >= q) return 0;

        ll ret = ppow[e0];
        if ((p > 2 or q < 3) and (ej(n / m) - ej(r / m) - ej(k / m)) & 1) {
            ret = m - ret;
        }

        while (n > 0) {
            int N = n % m, K = k % m, R = r % m;
            ret = __int128_t(ret) * fact_except_p[N] * fact_except_p_inv[K] * fact_except_p_inv[R] % m;

            n /= p;
            k /= p;
            r /= p;
        }

        return (ret + m) % m;
    }

  private:
    // ax + by = gcd(a, b) gcd > 0 は保証
    ll extgcd(ll a, ll b, ll &x, ll &y, bool first_call = true) {
        ll d = a;
        if (b != 0) {
            d = extgcd(b, a % b, y, x, false);
            y -= (a / b) * x;
        } else {
            x = 1;
            y = 0;
        }
        if (first_call and d < 0) {
            d *= -1;
            x *= -1;
            y *= -1;
        }
        return d;
    }

    long long ej(long long n) const {
        long long ret = 0;
        while (n)
            ret += n, n /= p;
        return ret;
    }
};

// 前計算 O(m) くらい
// クエリあたり O(log n log m) くらい
// verify: https://judge.yosupo.jp/submission/187937
struct BinomialCoefficient {
    // https://ferin-tech.hatenablog.com/entry/2018/01/17/010829
    vector<BinomialPrimePow> bpps;

    BinomialCoefficient(int m) {
        for (int p = 2; p * p <= m; p++) {
            int q = 0;
            while (m % p == 0) {
                m /= p;
                q++;
            }
            if (q > 0) {
                bpps.emplace_back(p, q);
            }
        }
        if (m > 1) {
            bpps.emplace_back(m, 1);
        }
    }

    ll nCk(ll n, ll k) {
        // nCk mod m を求める
        if (n < k) return 0;
        vl rets;
        vl ms;
        for (int i = 0; i < bpps.size(); i++) {
            rets.push_back(bpps[i].nCk(n, k));
            ms.push_back(bpps[i].m);
        }

        auto [ans, _] = atcoder::crt(rets, ms);
        return ans;
    }
};

// ����X�^�[�����O��
// �݂��ɋ�ʂł���n�̂��̂���ʂ̂Ȃ�k�̃O���[�v�ɕ�����Ƃ�,���̕�������secondStirling[n][k]
// ��������̃O���[�v�������Ă͂����Ȃ�
vll secondStirling(MAXN, vl(MAXN, 0));
void setSecondStirling(ll n, ll M = MOD) {
    secondStirling[0][0] = 1;
    rep1(i, n) {
        rep(j, i + 1) {
            if (j == i) {
                secondStirling[i][j] = 1;
            } else if (j == 0) {
                secondStirling[i][j] = 0;
            } else {
                secondStirling[i][j] = (secondStirling[i - 1][j - 1] + (ll)j * secondStirling[i - 1][j] % M) % M;
            }
        }
    }
}

// ������
// i�̈Ⴂ�ɋ�ʂł��Ȃ��i����j�O���[�v�ȉ��ɕ���������@part[i][j]
vll part(MAXN + 1, vl(MAXN + 1));
void setPartition(int n, ll M = MOD) {
    part[0][0] = 1;
    rep(i, n + 1) {
        rep1(j, n) {
            if (i - j >= 0) {
                // ����0�̃O���[�v������Ƃ�, i��j-1�O���[�v�Ɠ���
                // �Ȃ��Ƃ�, i - j ��j�O���[�v�Ɠ���(���ׂẴO���[�v�Ō���-=1����)
                part[i][j] = part[i - j][j] + part[i][j - 1];
            } else {
                part[i][j] = part[i][j - 1];
            }
            part[i][j] %= M;
        }
    }
}

int main() {
    ll n, m, i, j;
    cin >> n >> m;
    if (n < m) {
        cout << 0 << endl;
        return 0;
    }
    fact[0] = 1;
    for (i = 1; i <= m; i++) {
        fact[i] = (fact[i - 1] * i) % MOD;
    }
    for (i = 0; i <= m; i++) {
        if (i == 0)
            C[i] = 1;
        else
            C[i] = nCr(m, i);
    }
    ll ans = 0;
    int fugou = 1;
    for (i = 0; i < m; i++) {
        ans = (ans + fugou * ((C[i] * mod_pow(m - i, n, MOD)) % MOD)) % MOD;
        fugou *= (-1);
    }
    while (ans < 0) {
        ans += MOD;
    }
    cout << ans << endl;
}
