#include "bits/stdc++.h"
#include <unordered_set>
using namespace std;

#define DEBUG(x) cout<<#x<<": "<<x<<endl;
#define DEBUG_VEC(v) cout<<#v<<":";for(int i=0;i<v.size();i++) cout<<" "<<v[i]; cout<<endl

typedef long long ll;
#define vi vector<int>
#define vl vector<ll>
#define vii vector< vector<int> >
#define vll vector< vector<ll> >
#define vs vector<string>
#define pii pair<int,int>
#define pis pair<int,string>
#define psi pair<string,int>
const int inf = 1000000001;
const ll INF = 1e16;
#define MOD 1000000007
#define mod 1000000009
#define pi 3.14159265358979323846
#define Sp(p) cout<<setprecision(15)<<fixed<<p<<endl;
int dx[4] = { 1,0,-1,0 }, dy[4] = { 0,1,0,-1 };
int dx2[8] = { 1,1,0,-1,-1,-1,0,1 }, dy2[8] = { 0,1,1,1,0,-1,-1,-1 };

ll gcd(ll a, ll b) {
  if (b > a) {
    swap(a, b);
  }
  ll r = a%b;
  while (r != 0) {
    a = b;
    b = r;
    r = a%b;
  }
  return b;
}

ll lcm(ll a, ll b) {
  return (a / gcd(a, b))*b;
}

//ax + by = gcd(a, b) �ƂȂ�x, y�����Ƃ߂�
ll extgcd(ll a, ll b, ll& x, ll& y) {
  ll d = a;
  if (b != 0) {
    d = extgcd(b, a%b, y, x);
    y -= (a / b)*x;
  }
  else {
    x = 1; y = 0;
  }
  return d;
}


//������]�藝
//mod�̐ς��������Ƃ��I�[�o�[�t���[����B
//am[i].first:a_i, am[i].second:m_i
//return (x, y) y = lcm(m1, m2, ..., m_n),  x%m_i = a_i
typedef __int128 lll;
pll crt(vector<pll> am) {
  rep(i, am.size() - 1) {
    ll g, x, y, z;
    am[i].first = (am[i].first % am[i].second + am[i].second) % am[i].second;
    am[i + 1].first = (am[i + 1].first % am[i + 1].second + am[i + 1].second) % am[i + 1].second;
    g = extgcd(am[i].second, am[i + 1].second, x, y);
    if (am[i].first%g != am[i].second%g) return pll(-1, 0); //���Ȃ�
    lll lcm = (lll)am[i].second*(am[i + 1].second / g);
    if (lcm < am[i].second) return pll(-2, 0); //�I�[�o�[�t���[
    ll mo = am[i + 1].second = lcm;
    lll v = am[i].first + ((lll)(am[i].second / g) * x % mo * (am[i + 1].first - am[i].first + mo) % mo);
    am[i + 1].first = (v%mo + mo) % mo;
  }
  return am.back();
}

void prime(vector<bool> &isprime /*, vll &soinsu */) {
  ll i, j;
  assert(isprime[0]);
  isprime[0] = isprime[1] = false;
  for (i = 2; i < isprime.size(); i++) {
    if (isprime[i]) {
      // soinsu[i].push_back(i);
      for (j = 2; i*j < isprime.size(); j++) {
        isprime[i*j] = false;
        /*
          soinsu[i * j].push_back(i);
          int temp = i * j;
          while (temp % i == 0) {
          temp /= i;
          }
        */
      }
    }
  }
}

//n�ȉ���n�ƌ݂��ɑf�Ȏ��R���̌�
//O(sqrt(n))
int eulerSingle(int n) {
  int res = n;
  for (int i = 2; i*i <= n; i++) {
    if (n%i == 0) {
      res = res / i * (i - 1);
      for (; n%i == 0; n /= i);
    }
  }
  if (n != 1) res = res / n * (n - 1);
  return res;
}


//�I�C���[�֐��̒l�̃e�[�u��
//O(n)
vl euler(n + 1);
void eulerTable(int n) {
  for (i = 0; i <= n; i++) {
    euler[i] = i;
  }
  for (i = 2; i <= n; i++) {
    if (euler[i] == i) {
      for (j = i; j <= n; j += i) {
        euler[j] = euler[j] / i * (i - 1);
      }
    }
  }
}



// Miller Rubin
using u32 = unsigned int;
using u64 = unsigned long long;
using u128 = __uint128_t;

template <class Uint, class BinOp>
bool is_prime_impl(const Uint &n, const Uint *witness, BinOp modmul) {
    if (n == 2) return true;
    if (n < 2 || n % 2 == 0) return false;
    const Uint m = n - 1, d = m / (m & -m);
    auto modpow = [&](Uint a, Uint b) {
        Uint res = 1;
        for (; b; b /= 2) {
            if (b & 1) res = modmul(res, a);
            a = modmul(a, a);
        }
        return res;
    };
    auto suspect = [&](Uint a, Uint t) {
        a = modpow(a, t);
        while (t != n - 1 && a != 1 && a != n - 1) {
            a = modmul(a, a);
            t = modmul(t, 2);
        }
        return a == n - 1 || t % 2 == 1;
    };
    for (const Uint *w = witness; *w; w++) {
        if (*w % n != 0 && !suspect(*w, d)) return false;
    }
    return true;
}

bool is_prime(const u128 &n) {
    assert(n < 1ULL << 63);
    if (n < 1ULL << 32) {
        // n < 2^32
        constexpr u64 witness[] = {2, 7, 61, 0};
        auto modmul = [&](u64 a, u64 b) { return a * b % n; };
        return is_prime_impl<u64>(n, witness, modmul);
    } 
    else {
        // n < 2^63
        constexpr u128 witness[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022, 0};
        // if u128 is available
        auto modmul = [&](u128 a, u128 b) { return a * b % n; };
        return is_prime_impl<u128>(n, witness, modmul);
    }
}
