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
const ll INF=1e16;
#define MOD 1000000007
#define mod 1000000009
#define pi 3.14159265358979323846
#define Sp(p) cout<<setprecision(15)<<fixed<<p<<endl;
int dx[4]={1,0,-1,0}, dy[4]={0,1,0,-1};
#define N 50001
#define K 100001
vi T(K),X(K),Y(K);
vi par(3*N); //e
vi ran(3*N); //–Ø‚Ì[‚³

//n—v‘f‚Å‰Šú‰»
void init(int n){
	int i;
	loop(i,0,n){
		par[i]=i;
		ran[i]=0;
	}
}

//–Ø‚Ìª‚ð‹‚ß‚é
int find(int x){
	if(par[x]==x){
		return x;
	}else{
		return par[x]=find(par[x]);
	}
}

//x‚Æy‚Ì‘®‚·‚éW‡‚ð•¹‡
void unite(int x,int y){
	x=find(x);
	y=find(y);
	if(x==y){
		return;
	}
	if(ran[x]<ran[y]){
		par[x]=y;
	}else{
		par[y]=x;
		if(ran[x]==ran[y]){
			ran[x]++;
		}
	}
}

//x‚Æy‚ª“¯‚¶W‡‚É‘®‚·‚é‚©”Û‚©
bool same(int x,int y){
	return find(x)==find(y);
}

int main(){
	int n,k,i;
	cin>>n>>k;
	loop(i,0,k){
		cin>>T[i]>>X[i]>>Y[i];
	}
	init(n*3);
	int ans=0;
	loop(i,0,k){
		int t=T[i];
		int x=X[i]-1,y=Y[i]-1;
		
		if(x<0 || x>=n || y<0 || y>=n){
			ans++;
			continue;
		}
		
		if(t==1){
			if(same(x,y+n) || same(x,y+2*n)){
				ans++;
			}
			else{
				unite(x,y);
				unite(x+n,y+n);
				unite(x+2*n,y+2*n);
			}
		}else{
			if(same(x,y) || same(x,y+2*n)){
				ans++;
			}else{
				unite(x,y+n);
				unite(x+n,y+2*n);
				unite(x+2*n,y);
			}
		}
	}
	cout<<ans<<endl;
}
