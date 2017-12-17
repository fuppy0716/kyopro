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
	bool ari;

	Trie() {
		fill(next, next + charnum, (Trie *)NULL);
		ari = false;
	}

	void insert(string s) {
		Trie* now = this;
		for (int i = 0; i < s.size(); i++) {
			if (now->next[s[i] - firstchar] == NULL) {
				now->next[s[i] - firstchar] = new Trie();
			}
			now = now->next[s[i] - firstchar];
		}
		now->ari = true;
	}

	//insert‚µ‚½‚â‚Â‚Ìprefix‚ª‚·‚×‚Ä‚İ‚Â‚©‚é
	//insert‚µ‚½‚â‚Â‚ğŒ©‚Â‚¯‚½‚¢ê‡AÅŒã‚ğ
	//return now->ari;
	//‚É•Ï‚¦‚éB
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

Trie* t = new Trie();

void dfs(string s) {
	if (s.size() > 11) {
		return;
	}
	if (t->find(s)) {
		cout << s << endl;
	}
	string s2 = s;
	s.push_back('0');
	s2.push_back('1');
	dfs(s);
	dfs(s2);
}


int main() {
	int n;
	cin >> n;
	int i;
	for (i = 0; i < n; i++) {
		string s;
		cin >> s;
		t->insert(s);
	}
	string s = "";
	dfs(s);
}