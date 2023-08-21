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
    fact[0] = fact[1] = rfact[0] = rfact[1] = 1;
    for (ll i = 2; i <= n; i++) {
        fact[i] = i * fact[i - 1] % M;
        // rfact[i] = mod_inverse(fact[i], M);
    }
}

//http://drken1215.hatenablog.com/entry/2018/06/08/210000
//n���傫��fact���v�Z�ł��Ȃ��Ƃ��̂ق��̌v�Z���@�ɂ��ď����Ă���
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
        ans *= nCr(np[i], rp[i]);
        ans %= M;
    }
    return ans;
}

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
