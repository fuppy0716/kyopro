vl fact(111111), rfact(111111);

ll mod_pow(ll x, ll p, ll M = MOD) {
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
        rfact[i] = mod_inverse(fact[i], M);
    }
}

// https://ei1333.github.io/luzhiled/snippets/math/lagrange-polynomial.html
template <typename T>
T lagrange_polynomial(const vector<T> &y, int64_t t) {
    assert(fact[2] == 2);
    int N = y.size() - 1;
    if (t <= N) return y[t];
    T ret(0);
    vector<T> dp(N + 1, 1), pd(N + 1, 1);
    for (int i = 0; i < N; i++)
        dp[i + 1] = dp[i] * (t - i) % MOD;
    for (int i = N; i > 0; i--)
        pd[i - 1] = pd[i] * (t - i) % MOD;
    for (int i = 0; i <= N; i++) {
        T tmp = y[i] * dp[i] % MOD * pd[i] % MOD * rfact[i] % MOD * rfact[N - i] % MOD;
        if ((N - i) & 1)
            ret -= tmp;
        else
            ret += tmp;
        ret %= MOD;
    }
    return (ret + MOD) % MOD;
}

int main() {
    int n;
    cin >> n;
    set_fact(n);
    vl a(n + 1);
    rep(i, n + 1) cin >> a[i];
    ll t;
    cin >> t;
    ll ans = lagrange_polynomial(a, t);
    cout << ans << endl;
}
