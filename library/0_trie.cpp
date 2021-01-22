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


// https://yukicoder.me/submissions/607332 (queryの使用例)
// https://atcoder.jp/contests/arc087/submissions/19517611 (dfsの使用例)
// https://onlinejudge.u-aizu.ac.jp/beta/review.html#OUPC2020/5146784 (trie木上の木DP．dfsで木DPを，queryでprefixに対する検索をしている)
// https://atcoder.jp/contests/dwacon5th-final/submissions/19549436 (xor_min, subの使用例)
template<int char_size>
struct TrieNode {
    // 持たせたい好きな状態を持たせよう

    // 持たせたい好きな状態を持たせよう
    int next_idx[char_size]; // Trie木上での次の状態のインデックス，存在しない時は-1
    vector<int> exist_char; // 続きのノードが存在する文字
    vector<int> state_idx; // ちょうどこのノードと同じ文字列のインデックス（同じ文字列が複数回追加される時もあるので）
    int sub_num = 0; // このノード以下に存在する追加された文字列の数（!= ノードの数）

    TrieNode() {
        for (int i = 0; i < char_size; i++) next_idx[i] = -1;
    }
};

template<int char_size, int initial_char>
struct Trie {
    using Node = TrieNode<char_size>;

    vector<Node> nodes;
    int str_num=0; // 追加された文字列の数（!= ノードの数）
    vector<string> strs; // 追加された文字列とそのidの対応表，idが連番じゃない時はunordered_mapに変えて頑張って
    Trie() {
        nodes.push_back(Node());
    }

    void add(string& s, int str_idx, int node_idx, int id) {
        // sと完全に一致するノード
        if (str_idx == s.size()) {
            nodes[node_idx].state_idx.push_back(id);
            nodes[node_idx].sub_num++;
            return;
        }
        // sの次の文字に対応するノードがまだない
        if (nodes[node_idx].next_idx[s[str_idx] - initial_char] == -1) {
            nodes[node_idx].next_idx[s[str_idx] - initial_char] = nodes.size();
            nodes[node_idx].exist_char.push_back(s[str_idx] - initial_char);
            nodes.push_back(Node());
        }
        add(s, str_idx+1, nodes[node_idx].next_idx[s[str_idx] - initial_char], id);
        nodes[node_idx].sub_num++;
    }

    void add(string& s, int id=-1) {
        if (id == -1) id = str_num;
        add(s, 0, 0, id);
        str_num++;
        strs.push_back(s);
    }

    // MLE注意かも
    int sub(string& s, int str_idx, int node_idx) {
        // sと完全に一致するノード
        if (str_idx == s.size()) {
            assert(nodes[node_idx].state_idx.size() > 0);
            // 適当に最後に突っ込まれたidを削除している
            int id = nodes[node_idx].state_idx.back();
            nodes[node_idx].state_idx.pop_back();
            nodes[node_idx].sub_num--;
            return id;
        }

        int next_node_idx = nodes[node_idx].next_idx[s[str_idx] - initial_char];
        int id = sub(s, str_idx+1, next_node_idx);
        nodes[node_idx].sub_num--;
        assert(nodes[node_idx].sub_num >= 0);

        // sの次の文字に対応するノードは消えたが，このノードは消えないとき（このノードが根 or 他にも子がいる）
        if (nodes[next_node_idx].sub_num == 0 and (nodes[node_idx].sub_num > 0 or node_idx == 0)) {
            nodes[node_idx].next_idx[s[str_idx] - initial_char] = -1;
            rep (i, nodes[node_idx].exist_char.size()) {
                if (nodes[node_idx].exist_char[i] == s[str_idx] - initial_char) {
                    nodes[node_idx].exist_char.erase(nodes[node_idx].exist_char.begin() + i);
                    break;
                }
            }
        }
        return id;
    }
    
    // 削除した文字列のidを返す
    int sub(string& s) {
        int id = sub(s, 0, 0);
        str_num--;
        strs[id].clear();
        strs[id].shrink_to_fit();
        return id;
    }

    void query(string& s, int str_idx, int node_idx) {
        for (int id: nodes[node_idx].state_idx) {
            // s[0, str_idx)にちょうど一致する追加された文字列たちに対する処理
        }
        if (str_idx == s.size()) {
            // ちょうどsと一致するノードが見つかったよ！
            return;
        }

        if (nodes[node_idx].next_idx[s[str_idx] - initial_char] == -1) {
            // これ以上sのprefixに共通するノードはない
            return;
        }
        return query(s, str_idx + 1, nodes[node_idx].next_idx[s[str_idx] - initial_char]);
    }

    // sのprefixに対する何らかの処理をしたい時
    void query(string s) {
        query(s, 0, 0);
    }
    
    void dfs(int node_idx, int depth) {
        // 今の頂点に関する何らかの処理
        // 今の頂点に関する何らかの処理（終わり）

        for (int c: nodes[node_idx].exist_char) {
            assert(nodes[node_idx].next_idx[c] != -1);
            dfs(nodes[node_idx].next_idx[c], depth + 1);
        }
    }

    // 根からdfsしたい時
    void dfs() {
        dfs(0, 0);
    }

    string xor_min(string& s, int str_idx, int node_idx, string& t) {
        if (str_idx == s.size()) {
            // ちょうどsと一致するノードが見つかったよ！
            return t;
        }

        if (nodes[node_idx].next_idx[s[str_idx] - initial_char] != -1) {
            t += s[str_idx];
            return xor_min(s, str_idx + 1, nodes[node_idx].next_idx[s[str_idx] - initial_char], t);
        }
        else {
            char c = '0' + ('1' - s[str_idx]);
            t += c;
            return xor_min(s, str_idx + 1, nodes[node_idx].next_idx[c - initial_char], t);
        }
    }

    // sとxorした時に最も小さくなる文字列を探索
    string xor_min(string& s) {
        assert(initial_char == '0' and char_size == 2);
        assert(str_num > 0);
        string res;
        return xor_min(s, 0, 0, res);
    }
};
