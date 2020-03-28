#include <bits/stdc++.h>

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
#define pll pair<ll,ll>
#define fi first
#define se second
#define rep(i,n) for(int i=0;i<(int)(n);i++)
#define rep1(i,n) for(int i=1;i<=(int)(n);i++)
#define all(c) c.begin(),c.end()
#define in(x, a, b) a <= x && x < b
const int inf = 1000000001;
const ll INF = 2e18;
const ll MOD = 1000000007;
//const ll mod = 1000000009;
const double pi = 3.14159265358979323846;
#define Sp(p) cout<<setprecision(15)<< fixed<<p <<endl;
int dx[4] = { 1,0, -1,0 }, dy[4] = { 0,1,0,-1 };
int dx2[8] = { 1,1,0,-1,-1,-1,0,1 }, dy2[8] = { 0,1,1,1,0,-1,-1,-1 };

ll sum = 0;

const char firstChar = 'a';
const int charNum = 26;

class Trie {
public:
  ll value = 0;
  Trie* used[charNum];
  vector<Trie*> next;
  
  Trie() {fill(used, used + charNum, (Trie*)(NULL));}
  
  void insert(string &s, int depth, int value) {
    this->value++;
    if (depth == s.size()) {
      return;
    }
    if (!this->used[s[depth] - firstChar]) {
      this->used[s[depth] - firstChar] = new Trie;
      next.push_back(this->used[s[depth] - firstChar]);
    }
    this->used[s[depth] - firstChar]->insert(s, depth + 1, value);
  }

  ll find(string &s, int depth) {
    if (depth == s.size()) {
      return this->value;
    }
    if (!this->used[s[depth] - firstChar]) {
      return -1;
    }
    return this->used[s[depth] - firstChar]->find(s, depth + 1);
  }
 
  
  void dfs(int depth) {
    //DEBUG(next.size());
    cout << flush;
    if (depth > 0 && this->value >= 2) {
      sum += (this->value * (this->value - 1)) / 2;
    }
    rep (i, next.size()) {
      next[i]->dfs(depth + 1);
    }
  }
};


int main() {  
  Trie* t = new Trie();

  ll n;
  cin >> n;
  int i;
  for (i = 0; i < n; i++) {
    string s;
    cin >> s;
    t->insert(s, 0, 0);
  }
  rep (i, 100) {
    string s;
    cin >> s;
    cout << t->find(s, 0) << endl;
  }
}
