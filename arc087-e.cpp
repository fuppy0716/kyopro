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
#define pll pair<ll,ll>
const int inf = 1000000001;
const ll INF = 1e18 * 2;
#define MOD 1000000007
#define mod 1000000009
#define pi 3.14159265358979323846
#define Sp(p) cout<<setprecision(15)<< fixed<<p<<endl;
int dx[4] = { 1,0,-1,0 }, dy[4] = { 0,1,0,-1 };
int dx2[8] = { 1,1,0,-1,-1,-1,0,1 }, dy2[8] = { 0,1,1,1,0,-1,-1,-1 };

const int charnum = 2;
const char firstchar = '0';

class Trie {
public:
	Trie *next[charnum];

	Trie() {
		fill(next, next + charnum, (Trie *)NULL);
	}

	/*
	void insert(char *s) {
	if (*s == '\0') return;
	if (this->next[*s - 'a'] == NULL)
	this->next[*s - 'a'] = new Trie();
	this->next[*s - 'a']->insert(s + 1);
	}
	*/
	void insert(string s) {
		Trie* now = this;
		for (int i = 0; i < s.size(); i++) {
			if (now->next[s[i] - firstchar] == NULL) {
				now->next[s[i] - firstchar] = new Trie();
			}
			now = now->next[s[i] - firstchar];
		}
	}

	bool find(string s) {
		Trie* now = this;
		for (int i = 0; i < s.size(); i++) {
			if (now->next[s[i] - firstchar] == NULL)
				return false;
			now = now->next[s[i] - firstchar];
		}
		return true;
	}
};

ll n, l;
ll grundy = 0;

void dfs(Trie* now, ll d) {
	if (now->next[0] == NULL && now->next[1] == NULL) {
		return;
	}
	else if (now->next[0] != NULL && now->next[1] != NULL) {
		dfs(now->next[0], d + 1);
		dfs(now->next[1], d + 1);
		return;
	}
	else if (now->next[0] == NULL) {
		grundy ^= (l - d) & (-l + d);
		dfs(now->next[1], d + 1);
		return;
	}
	else {
		grundy ^= (l - d) & (-l + d);
		dfs(now->next[0], d + 1);
		return;
	}
}


int main() {
	cin >> n >> l;
	int i, j;
	Trie* t = new Trie();
	for (i = 0; i < n; i++) {
		string s;
		cin >> s;
		t->insert(s);
	}
	dfs(t, 0LL);
	if (grundy == 0) {
		cout << "Bob" << endl;
	}
	else {
		cout << "Alice" << endl;
	}
}