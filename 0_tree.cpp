
class CentroidDecomposition {
public:
	int n; //���_��
	vii G; //�O���t�̗אڃ��X�g�\��
	vector<bool> isused; //���̒��_�����łɕ����Ɏg���Ă��邩
	vi subtreesize; //�����؂̃T�C�Y,�X�V�����
	vi parent;
	vi centroid; //�d�S�����ɒǉ�����Ă���
	vector<char> ans;

	CentroidDecomposition(int n) : n(n) {
		G.resize(n); isused.resize(n);
		subtreesize.resize(n); parent.resize(n);
		ans.resize(n);
	}

	void add_edge(int u, int v) {
		G[u].push_back(v); G[v].push_back(u);
	}

	int search_centroid(int now, int par, int size) {
		subtreesize[now] = 1;
		parent[now] = par;
		bool iscentroid = true;
		for (int i = 0; i < G[now].size(); i++) {
			int child = G[now][i];
			if (child == par) continue;
			if (isused[child]) continue;
			int child_size = search_centroid(child, now, size);
			if (child_size > size / 2) iscentroid = false;
			subtreesize[now] += child_size;
		}
		if (size - subtreesize[now] > size / 2) {
			iscentroid = false;
		}
		if (iscentroid) {
			centroid.push_back(now);
		}
		return subtreesize[now];
	}

	//���ɂ���ĕς��
	void solve(int root, char c, int size) {
		search_centroid(root, -1, size);
		int cent = centroid.back();
		isused[cent] = true;
		ans[cent] = c;
		rep(i, G[cent].size()) {
			int ch = G[cent][i];
			if (isused[ch]) {
				continue;
			}
			if (parent[ch] == cent) {
				solve(ch, c + 1, subtreesize[ch]);
			}
			else {
				solve(ch, c + 1, size - subtreesize[cent]);
			}
		}
		return;
	}


};


//���_�ɒl���ڂ��Ă��鎞
//https://yukicoder.me/submissions/410940
//�ӂɒl���ڂ��Ă��鎞
//https://yukicoder.me/submissions/410947
//https://atcoder.jp/contests/abc133/submissions/9120584
//���_�ɒl���ڂ��Ă��鎞�C�����؃N�G��
//https://atcoder.jp/contests/iroha2019-day2/submissions/9039015
//http://beet-aizu.hatenablog.com/entry/2017/12/12/235950
class HLD {
private:
  void dfs_sz(int v) {
    for(int &u:G[v])
      if(u==par[v]) swap(u,G[v].back());
    if(~par[v]) G[v].pop_back();

    for(int &u:G[v]){
      par[u]=v;
      dep[u]=dep[v]+1;
      dfs_sz(u);
      sub[v]+=sub[u];
      if(sub[u]>sub[G[v][0]]) swap(u,G[v][0]);
    }
  }

  void dfs_hld(int v,int c,int &pos) {
    vid[v]=pos++;
    inv[vid[v]]=v;
    type[v]=c;
    for(int u:G[v]){
      if(u==par[v]) continue;
      head[u]=(u==G[v][0]?head[v]:u);
      dfs_hld(u,c,pos);
    }
  }

public:
  vector< vector<int> > G;
  vector<int> vid, head, sub, par, dep, inv, type;

  HLD(int n):
    G(n),vid(n,-1),head(n),sub(n,1),
    par(n,-1),dep(n,0),inv(n),type(n){}

  void add_edge(int u,int v) {
    G[u].emplace_back(v);
    G[v].emplace_back(u);
  }

  void build(vector<int> rs={0}) {
    int c=0,pos=0;
    for(int r:rs){
      dfs_sz(r);
      head[r]=r;
      dfs_hld(r,c++,pos);
    }
  }

  int lca(int u,int v){
    while(1){
      if(vid[u]>vid[v]) swap(u,v);
      if(head[u]==head[v]) return u;
      v=par[head[v]];
    }
  }

  int distance(int u,int v){
    return dep[u]+dep[v]-2*dep[lca(u,v)];
  }

  // for_each(vertex)
  // [l, r) <- attention!!
  template<typename F>
  void for_each(int u, int v, const F& f) {
    while(1){
      if(vid[u]>vid[v]) swap(u,v);
      f(max(vid[head[v]],vid[u]),vid[v]+1);
      if(head[u]!=head[v]) v=par[head[v]];
      else break;
    }
  }

  template<typename T,typename Q,typename F>
  T for_each(int u,int v,T ti,const Q &q,const F &f){
    T l=ti,r=ti;
    while(1){
      if(vid[u]>vid[v]){
        swap(u,v);
        swap(l,r);
      }
      l=f(l,q(max(vid[head[v]],vid[u]),vid[v]+1));
      if(head[u]!=head[v]) v=par[head[v]];
      else break;
    }
    return f(l,r);
  }

  // for_each(edge)
  // [l, r) <- attention!!
  template<typename F>
  void for_each_edge(int u, int v,const F& f) {
    while(1){
      if(vid[u]>vid[v]) swap(u,v);
      if(head[u]!=head[v]){
        f(vid[head[v]],vid[v]+1);
        v=par[head[v]];
      }else{
        if(u!=v) {
          f(vid[u]+1,vid[v]+1);
        }
        break;
      }
    }
  }
};


//���t���؂̃n�b�V��
//�؂̓��^����Ɏg��
#include <random>
vl rand1(100010);
vl rand2(100010);

void make_rand() {
	random_device rnd;
	mt19937 mt(rnd());
	uniform_int_distribution<> randinf(0, inf);
	rep(i, 100010) {
		rand1[i] = randinf(mt);
		rand2[i] = randinf(mt);
	}
}

pll hs(vii &G, int now, int parent, int depth) {
	pll res = pll(1, 1);
	rep(i, G[now].size()) {
		if (G[now][i] == parent) {
			continue;
		}
		pll temp = hs(G, G[now][i], now, depth + 1);
		(res.first *= (temp.first + rand1[depth])) %= mod;
		(res.second *= (temp.second + rand2[depth])) %= mod;
	}
	return res;
}
