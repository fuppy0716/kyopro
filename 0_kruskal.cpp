#ifndef _GLIBCXX_NO_ASSERT
#include <cassert>
#endif
#include <cctype>
#include <cerrno>
#include <cfloat>
#include <ciso646>
#include <climits>
#include <clocale>
#include <cmath>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#if __cplusplus >= 201103L
#include <ccomplex>
#include <cfenv>
#include <cinttypes>
#include <cstdalign>
#include <cstdbool>
#include <cstdint>
#include <ctgmath>
#include <cwchar>
#include <cwctype>
#endif
// C++
#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>

#if __cplusplus >= 201103L
#include <array>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <forward_list>
#include <future>
#include <initializer_list>
#include <mutex>
#include <random>
#include <ratio>
#include <regex>
#include <scoped_allocator>
#include <system_error>
#include <thread>
#include <tuple>
#include <typeindex>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#endif
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
#define pll pair<ll,ll>
#define pis pair<int,string>
#define psi pair<string,int>
const int inf = 1000000001;
const ll INF = 1e16;
#define MOD 1000000007
#define mod 1000000009
#define pi 3.14159265358979323846
#define Sp(p) cout<<setprecision(15)<<fixed<<p<<endl;
int dx[4] = { 1,0,-1,0 }, dy[4] = { 0,1,0,-1 };
int dx2[8] = { 1,1,0,-1,-1,-1,0,1 }, dy2[8] = { 0,1,1,1,0,-1,-1,-1 };


#define N 20010
#define R 50010
int n, m, r;
vector< pair<ll, pll> > M(R);
vl par(N);
vl ran(N);

//nóvëfÇ≈èâä˙âª
void init(int n) {
	int i;
	for (i = 0; i < n; i++) {
		par[i] = i;
		ran[i] = 0;
	}
}

//ñÿÇÃç™ÇãÅÇﬂÇÈ
int find(int x) {
	if (par[x] == x) {
		return x;
	}
	else {
		return par[x] = find(par[x]);
	}
}

//xÇ∆yÇÃëÆÇ∑ÇÈèWçáÇïπçá
void unite(int x, int y) {
	x = find(x);
	y = find(y);
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
}

//xÇ∆yÇ™ìØÇ∂èWçáÇ…ëÆÇ∑ÇÈÇ©î€Ç©
bool same(int x, int y) {
	return find(x) == find(y);
}

ll kruskal() {
	sort(M.begin(), M.end());
	init(n + m);
	ll res = 0;
	for (int i = 0; i < M.size(); i++) {
		if (!same(M[i].second.first, M[i].second.second)) {
			unite(M[i].second.first, M[i].second.second);
			res += M[i].first;
		}
	}
	return res;
}

int main() {
	ll q;
	cin >> q;
	int i0;
	for (i0 = 0; i0 < q; i0++) {
		int i, j;
		M.clear();
		cin >> n >> m >> r;
		for (i = 0; i < r; i++) {
			ll a, b, c;
			cin >> a >> b >> c;
			b += n;
			M.push_back(make_pair(-c, make_pair(a, b)));
		}
		cout << kruskal() + 10000 * (m + n) << endl;

	}
}