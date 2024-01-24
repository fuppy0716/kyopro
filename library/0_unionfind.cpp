#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define loop(i, a, b) for (i = a; i < b; i++)
#define rloop(i, a, b) for (i = a; i >= b; i--)
#define vi vector<int>
#define vl vector<ll>
#define vii vector<vector<int>>
#define vll vector<vector<ll>>
#define vs vector<string>
#define pii pair<int, int>
#define pis pair<int, string>
#define psi pair<string, int>
const int inf = 1000000001;
const ll INF = 1e18;
#define MOD 1000000007
#define mod 1000000009
#define pi 3.14159265358979323846
#define Sp(p) cout << setprecision(15) << fixed << p << endl;
int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};

class UnionFind {
  private:
    vi par_;      // �e
    vi ran_;      // �؂̐[��
    vi num_;      // �v�f��
    vi edge_num_; // �v�f��
  public:
    int n;
    int g; // group��

    UnionFind(int _n) {
        n = _n;
        g = n;
        par_.resize(n);
        ran_.resize(n);
        num_.resize(n);
        edge_num_.resize(n);
        for (int i = 0; i < n; i++) {
            par_[i] = i;
            ran_[i] = 0;
            num_[i] = 1;
            edge_num_[i] = 0;
        }
    }

    // �؂̍������߂�
    int find(int x) {
        if (par_[x] == x) {
            return x;
        } else {
            return par_[x] = find(par_[x]);
        }
    }

    // x��y�̑�����W���𕹍�
    void unite(int x, int y) {
        x = find(x);
        y = find(y);
        int numsum = num_[x] + num_[y];
        int edge_numsum = edge_num_[x] + edge_num_[y];
        if (x == y) {
            edge_num_[x]++;
            return;
        }
        if (ran_[x] < ran_[y]) {
            par_[x] = y;
        } else {
            par_[y] = x;
            if (ran_[x] == ran_[y]) {
                ran_[x]++;
            }
        }
        num_[x] = num_[y] = numsum;
        edge_num_[x] = edge_num_[y] = edge_numsum + 1;
        g--;
    }

    // x��y�������W���ɑ����邩�ۂ�
    bool same(int x, int y) {
        return find(x) == find(y);
    }

    int num(int x) {
        return num_[find(x)];
    }

    int edge_num(int x) {
        return edge_num_[find(x)];
    }
};

// 部分永続 UnionFind ?
// https://ei1333.github.io/luzhiled/snippets/structure/union-find.html ?
class PermanenceUF {
  public:
    int n;
    vi par;
    vi ran;
    vector<vector<pll>> num;
    vl time;

    PermanenceUF(int _n) {
        n = _n;
        par.resize(n);
        ran.resize(n);
        num.resize(n);
        time.resize(n);
        for (int i = 0; i < n; i++) {
            par[i] = i;
            ran[i] = 0;
            time[i] = INF;
            num[i] = vector<pll>(1, pii(0, 1));
        }
    }

    int find(ll t, int x) {
        if (time[x] > t)
            return x;
        else
            return find(t, par[x]);
    }

    void unite(ll t, int x, int y) {
        x = find(t, x);
        y = find(t, y);
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

    bool same(ll t, int x, int y) {
        return find(t, x) == find(t, y);
    }

    int size(ll t, int x) {
        int root = find(t, x);
        int left = 0, right = num[root].size();
        while (left + 1 < right) {
            int mid = (left + right) / 2;
            if (num[root][mid].first <= t) {
                left = mid;
            } else {
                right = mid;
            }
        }
        return num[root][left].second;
    }
};

// ��������̂��̂ɗL��(�N��A�g���Ȃ�)
class WeightedUF {
  public:
    vi par, ran, num;
    vl diff_weight; // �e�m�[�h(���m�[�h�ł͂Ȃ�)�Ƃ̒l�̍���

    WeightedUF(int n) {
        par.resize(n);
        ran.resize(n);
        num.resize(n);
        diff_weight.resize(n);
        for (int i = 0; i < n; i++) {
            par[i] = i;
            ran[i] = 0;
            num[i] = 1;
            diff_weight[i] = 0;
        }
    }

    // �؂̍������߂�
    int find(int x) {
        if (par[x] == x) {
            return x;
        } else {
            int root = find(par[x]);
            diff_weight[x] += diff_weight[par[x]];
            return par[x] = root;
        }
    }

    ll weight(int x) {
        find(x); // �o�H���k
        return diff_weight[x];
    }

    // x����݂�y�̏d��
    ll diff(int x, int y) {
        if (!same(x, y)) {
            return -INF;
        } else {
            return weight(y) - weight(x);
        }
    }

    // x����݂�y�̏d�݂�w�ɂȂ�悤�ɕ���
    bool unite(int x, int y, ll w) {
        w += weight(x);
        w -= weight(y);
        x = find(x);
        y = find(y);
        int numsum = num[x] + num[y];
        if (x == y) {
            if (diff(x, y) == w) {
                return true;
            } else {
                return false;
            }
        }
        if (ran[x] < ran[y]) {
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

    // x��y�������W���ɑ����邩�ۂ�
    bool same(int x, int y) {
        return find(x) == find(y);
    }
};
