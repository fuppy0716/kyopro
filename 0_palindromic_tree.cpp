
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
#define fi first
#define se second
#define rep(i,n) for(int i=0;i<(int)(n);i++)
#define rep1(i,n) for(int i=1;i<=(int)(n);i++)
#define all(c) c.begin(),c.end()
const int inf = 1000000001;
const ll INF = 2e18 * 2;
#define MOD 1000000007
#define mod 1000000009
#define pi 3.14159265358979323846
#define Sp(p) cout<<setprecision(15)<< fixed<<p<<endl;
int dx[4] = { 1,0,-1,0 }, dy[4] = { 0,1,0,-1 };
int dx2[8] = { 1,1,0,-1,-1,-1,0,1 }, dy2[8] = { 0,1,1,1,0,-1,-1,-1 };

// http://math314.hateblo.jp/entry/2016/12/19/005919
// 一文字ずつ追加(add)していく
// 頂点は文字列に含まれるユニークな回文+長さ0+長さ-1
// つまり、文字列に含まれるユニークな回文の種類はc.size() - 2

struct PalindromicTree {
	//
	// private:
	struct node {
		map<char, int> link;
		int suffix_link;
		int len;
		int count;
	};

	vector<node> c;
	string s;
	int active_idx;

	node* create_node() {
		c.emplace_back();
		node* ret = &c.back();
		ret->count = 0;
		return ret;
	}

	// this->s の状態に依存する
	int find_prev_palindrome_idx(int node_id) {
		const int pos = int(s.size()) - 1;
		while (true) {
			const int opposite_side_idx = pos - 1 - c[node_id].len;
			if (opposite_side_idx >= 0 && s[opposite_side_idx] == s.back()) break;
			node_id = c[node_id].suffix_link; // 次の回文に移動
		}
		return node_id;
	}

	bool debug_id2string_dfs(int v, int id, vector<char>& charas) {
		if (v == id) return true;
		for (auto kv : c[v].link) {
			if (debug_id2string_dfs(kv.second, id, charas)) {
				charas.push_back(kv.first);
				return true;
			}
		}
		return false;
	}

public:
	PalindromicTree() {
		node* size_m1 = create_node(); // 長さ-1のノードを作成
		size_m1->suffix_link = 0; // -1 の親suffixは自分自身
		size_m1->len = -1;
		node* size_0 = create_node(); // 長さ0のノードを作成
		size_0->suffix_link = 0; // 親は長さ-1のノード
		size_0->len = 0;

		active_idx = 0;
	}

	int get_active_idx() const {
		return active_idx;
	}
	node* get_node(int id) {
		return &c[id];
	}

	void add(char ch) {
		s.push_back(ch);

		// ch + [A] + ch が回文となるものを探す
		const int a = find_prev_palindrome_idx(active_idx);

		//新しいノードへのリンクが発生するか試す
		const auto inserted_result = c[a].link.insert(make_pair(ch, int(c.size())));
		active_idx = inserted_result.first->second; // insertの成否に関わらず、iteratorが指す先は新しい回文のindex
		if (!inserted_result.second) {
			c[active_idx].count++; // その回文が現れた回数が増加
			return; // 既にリンクが存在したので、新しいノードを作る必要がない
		}

		// 実際に新しいノードを作成
		node* nnode = create_node();
		nnode->count = 1;
		nnode->len = c[a].len + 2; // ch + [A] + ch だから、長さは len(A) + 2

								   // suffix_linkの設定
		if (nnode->len == 1) {
			// この時だけsuffix_linkはsize 0に伸ばす
			nnode->suffix_link = 1;
		}
		else {
			// ch + [B] + ch が回文になるものを探す。ただし長さはaより小さいもの
			const int b = find_prev_palindrome_idx(c[a].suffix_link);
			nnode->suffix_link = c[b].link[ch];
		}
	}

	//各文字列が何回現れるか計算する
	// O(n)
	vector<int> build_frequency() {
		vector<int> frequency(c.size());
		//常に親ノードのid < 子ノードのidが成り立つので、idを大きい順から回せばよい
		for (int i = int(c.size()) - 1; i > 0; i--) {
			frequency[i] += c[i].count;
			frequency[c[i].suffix_link] += frequency[i];
		}
		return frequency;
	}

	// debug用
	// idがどのような回文を表しているのかを返す
	// O(n)
	string debug_id2string(int id) {
		if (id == 0) {
			return "(-1)";
		}
		else if (id == 1) {
			return "(0)";
		}

		vector<char> charas;
		debug_id2string_dfs(0, id, charas);
		debug_id2string_dfs(1, id, charas);

		string ret(charas.begin(), charas.end());
		int start = int(charas.size()) - 1;
		if (c[id].len % 2 == 1) start--;
		for (int i = start; i >= 0; i--) ret.push_back(charas[i]);

		return ret;
	}

	void display_frequencies() {
		auto freq = build_frequency();
		printf("frequencies of each palindrome...\n");
		for (int i = 0; i < int(c.size()); i++) {
			const string palindrome = debug_id2string(i);
			printf("  %s : %d\n", palindrome.c_str(), freq[i]);
		}
	}
};
int main() {
	PalindromicTree pt;

	string s = "abcabccbc";

	{
		for (auto c : s) {
			pt.add(c); // 1文字ずつ登録していく
			pt.display_frequencies();
		}
		auto freq = pt.build_frequency();
		for (int i = 0; i < pt.c.size(); i++) {
			cout << pt.debug_id2string(i) << " ";
			cout << freq[i] << endl;
		}
	}
}