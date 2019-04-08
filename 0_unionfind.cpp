#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define loop(i,a,b) for(i=a;i<b;i++)
#define rloop(i,a,b) for(i=a;i>=b;i--)
#define vi vector<int>
#define vl vector<ll>
#define vii vector< vector<int> >
#define vll vector< vector<ll> >
#define vs vector<string>
#define pii pair<int,int>
#define pis pair<int,string>
#define psi pair<string,int>
const int inf=1000000001;
const ll INF=1e18;
#define MOD 1000000007
#define mod 1000000009
#define pi 3.14159265358979323846
#define Sp(p) cout<<setprecision(15)<<fixed<<p<<endl;
int dx[4]={1,0,-1,0}, dy[4]={0,1,0,-1};



class UnionFind {
public:
	int n;
	vi par; //親
	vi ran; //木の深さ
	vi num; //要素数

	UnionFind(int _n) {
		n = _n;
		par.resize(n); ran.resize(n); num.resize(n);
		for (int i = 0; i < n; i++) {
			par[i] = i; ran[i] = 0; num[i] = 1;
		}
	}

	//木の根を求める
	int find(int x) {
		if (par[x] == x) {
			return x;
		}
		else {
			return par[x] = find(par[x]);
		}
	}

	//xとyの属する集合を併合
	void unite(int x, int y) {
		x = find(x); y = find(y);
		int numsum = num[x] + num[y];
		if (x == y) {
			return;
		}
		if (ran[x]<ran[y]) {
			par[x] = y;
		}
		else {
			par[y] = x;
			if (ran[x] == ran[y]) {
				ran[x]++;
			}
		}
		num[x] = num[y] = numsum;
	}

	//xとyが同じ集合に属するか否か
	bool same(int x, int y) {
		return find(x) == find(y);
	}

};

//部分永続UF
class PermanenceUF {
public:
	int n;
	vi par; //親
	vi ran; //木の深さ
	vector<vector<pll> > num; //要素数
	vl time; //木が更新された時の時刻

	PermanenceUF(int _n) {
		n = _n;
		par.resize(n); ran.resize(n);
		num.resize(n); time.resize(n);
		for (int i = 0; i < n; i++) {
			par[i] = i; ran[i] = 0; time[i] = INF;
			num[i] = vector<pll>(1, pii(0, 1));
		}
	}

	//時刻tの時の木の根を求める
	int find(ll t, int x) {
		if (time[x] > t) return x;
		else return find(t, par[x]);
	}

	//時刻tにxとyの属する集合を併合
	//tは単調増加している
	void unite(ll t, int x, int y) {
		x = find(t, x); y = find(t, y);
		ll numsum = num[x].back().second + num[y].back().second;
		if (x == y) {
			return;
		}
		if (ran[x] < ran[y]) {
			swap(x, y);
		}
		par[y] = x;
		time[y] = t;
		num[x].push_back(pll(t, numsum));
		if (ran[x] == ran[y]) {
			ran[x]++;
		}
	}

	//時刻tのxとyが同じ集合に属するか否か
	bool same(ll t, int x, int y) {
		return find(t, x) == find(t, y);
	}

	//時刻tの時の要素xを含む集合のサイズ
	int size(ll t, int x) {
		int root = find(t, x);
		int left = 0, right = num[root].size();
		while (left + 1 < right) {
			int mid = (left + right) / 2;
			if (num[root][mid].first <= t) {
				left = mid;
			}
			else {
				right = mid;
			}
		}
		return num[root][left].second;
	}

};

//数直線状のものに有効(年齢、身長など)
class WeightedUF {
public:
  vi par, ran, num;
  vl diff_weight; //親ノード(根ノードではない)との値の差分
  
  WeightedUF(int n) {
    par.resize(n); ran.resize(n);
    num.resize(n); diff_weight.resize(n);
    for (int i = 0; i < n; i++) {
      par[i] = i; ran[i] = 0;
      num[i] = 1; diff_weight[i] = 0;
    }
  }

  //木の根を求める
  int find(int x) {
    if (par[x] == x) {
      return x;
    }
    else {
      int root = find(par[x]);
      diff_weight[x] += diff_weight[par[x]];
      return par[x] = root;
    }
  }

  ll weight(int x) {
    find(x); //経路圧縮
    return diff_weight[x];
  }

  //xからみたyの重み
  ll diff(int x, int y) {
    if (!same(x, y)) {
      return -INF;
    }
    else {
      return weight(y) - weight(x);
    }
  }
  
  //xからみたyの重みがwになるように併合
  bool unite(int x, int y, ll w) {
    w += weight(x); w -= weight(y);
    x = find(x); y = find(y);
    int numsum = num[x] + num[y];
    if (x == y) {
      if (diff(x, y) == w) {
	return true;
      }
      else {
	return false;
      }
    }
    if (ran[x]<ran[y]) {
      swap(x, y);
      w = -w;
    }
    par[y] = x;
    if (ran[x] == ran[y]) {
	ran[x]++;
    }
    diff_weight[y] = w;
    num[x] = num[y] = numsum;
    return true;
  }

  //xとyが同じ集合に属するか否か
  bool same(int x, int y) {
    return find(x) == find(y);
  }
};
