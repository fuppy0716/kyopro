#include "bits/stdc++.h"
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
#define pll pair<ll, ll>
const int inf = 1000000001;
const ll INF = 1e18;
#define MOD 1000000007
#define mod 1000000009
#define pi 3.14159265358979323846
#define Sp(p) cout<<setprecision(15)<<fixed<<p<<endl;
int dx[4] = { 1,0,-1,0 }, dy[4] = { 0,1,0,-1 };
int dx2[8] = { 1,1,0,-1,-1,-1,0,1 }, dy2[8] = { 0,1,1,1,0,-1,-1,-1 };

//追加される傾きaが単調減少、求めたい点xが単調増加の時のみ最小値を求められる。
template<typename T> class ConvexHullTrick {
  deque<pair<T, T> > lines;
  // 大小を判断する関数
  std::function<bool(T l, T r)> comp;
  
public:
  ConvexHullTrick(std::function<bool(T l, T r)> compFunc = [](T l, T r) {return l >= r; })
    :comp(compFunc)  {
  };

  // 直線l1, l2, l3のうちl2が不必要であるかどうか
  bool check(std::pair<T, T> l1, std::pair<T, T> l2, std::pair<T, T> l3) {
    if (l1 < l3) swap(l1, l3);
    return (l3.second - l2.second) * (l2.first - l1.first) >= (l2.second - l1.second) * (l3.first - l2.first);
  }

  // 直線y=ax+bを追加する
  void add(T a, T b) {
    std::pair<T, T> line(a, b);
    while (lines.size() >= 2 && check(*(lines.end() - 2), lines.back(), line))
      lines.pop_back();
    lines.push_back(line);
  }

  // i番目の直線f_i(x)に対するxの時の値を返す
  T f(int i, T x) {
    return lines[i].first * x + lines[i].second;
  }

  T get(T x) {
    // 最小値(最大値)クエリにおけるxが単調
    while (lines.size() >= 2 && comp(f(0, x), f(1, x)))
      lines.pop_front();
    return f(0, x);
  }
};


//最小値クエリ
//INFの値によってはすぐオーバーフローするので注意(|ab| < LLONG_MAX/4)
//非順序add非順序query
//http://d.hatena.ne.jp/sune2/20140310/1394440369
struct CHT2 {
	CHT2() {
		// 番兵
		S.insert({ L(INF,0), L(-INF,0) });
		C.insert(cp(L(INF, 0), L(-INF, 0)));
	}
	// for debug
	void print() {
		cout << "S : "; for (auto it : S) printf("(%lld,%lld)", it.a, it.b); puts("");
		cout << "C : "; for (auto it : C) printf("(%lld,%lld)", it.n, it.d); puts("");
	}
	// |ab| < LLONG_MAX/4 ???
	void add(ll a, ll b) {
		const L p(a, b);
		It pos = S.insert(p).first;
		if (check(*it_m1(pos), p, *it_p1(pos))) {
			// 直線(a,b)が不要
			S.erase(pos);
			return;
		}
		C.erase(cp(*it_m1(pos), *it_p1(pos)));
		{
			// 右方向の削除
			It it = it_m1(pos);
			while (it != S.begin() && check(*it_m1(it), *it, p)) --it;
			C_erase(it, it_m1(pos));
			S.erase(++it, pos);
			pos = S.find(p);
		}
		{
			// 左方向の削除
			It it = it_p1(pos);
			while (it_p1(it) != S.end() && check(p, *it, *it_p1(it))) ++it;
			C_erase(++pos, it);
			S.erase(pos, it);
			pos = S.find(p);
		}
		C.insert(cp(*it_m1(pos), *pos));
		C.insert(cp(*pos, *it_p1(pos)));
	}
	ll query(ll x) {
		const L &p = (--C.lower_bound(CP(x, 1, L(0, 0))))->p;
		return p.a*x + p.b;
	}

private:

	template<class T> T it_p1(T a) { return ++a; }
	template<class T> T it_m1(T a) { return --a; }
	struct L {
		ll a, b;
		L(ll a, ll b) : a(a), b(b) {}
		bool operator<(const L &rhs) const {
			return a != rhs.a ? a > rhs.a : b < rhs.b;
		}
	};
	struct CP {
		ll n, d;
		L p;
		CP(ll _n, ll _d, const L &p) : n(_n), d(_d), p(p) {
			if (d < 0) { n *= -1; d *= -1; }
		};
		bool operator<(const CP &rhs) const {
			if (n == INF || rhs.n == -INF) return 0;
			if (n == -INF || rhs.n == INF) return 1;
			return n * rhs.d < rhs.n * d;
		}
	};
	set<L> S;
	set<CP> C;

	typedef set<L>::iterator It;

	void C_erase(It a, It b) {
		for (It it = a; it != b; ++it)
			C.erase(cp(*it, *it_p1(it)));
	}
	CP cp(const L &p1, const L &p2) {
		if (p1.a == INF) return CP(-INF, 1, p2);
		if (p2.a == -INF) return CP(INF, 1, p2);
		return CP(p1.b - p2.b, p2.a - p1.a, p2);
	}
	bool check(const L &p1, const L &p2, const L &p3) {
		if (p1.a == p2.a && p1.b <= p2.b) return 1;
		if (p1.a == INF || p3.a == -INF) return 0;
		return (p2.a - p1.a)*(p3.b - p2.b) >= (p2.b - p1.b)*(p3.a - p2.a);
	}
};

int main() {
  ll n, i, j;
  cin >> n;
  vl a(n);
  vl y00(n), k(n), b(n);
  for (i = 0; i < n; i++) {
    cin >> a[i];
  }
  for (i = 0; i < n; i++) {
    y00[i] = a[i] + i*i;
  }
  for (i = 0; i < n; i++) {
    k[i] = -1 - 2 * i;
  }
  for (i = 0; i < n; i++) {
    b[i] = 2 * i;
  }
  for (i = 1; i < n; i++) {
    b[i] = b[i - 1] + b[i];
  }

  ConvexHullTrick<ll> CHT;
  for (i = 0; i < n; i++) {
    CHT.add(k[i], y00[i]);
  }
  for (i = 0; i < n; i++) {
    cout << CHT.get(i) << endl;;
  }
  
  
}
