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

int main() {
	int h, w, i, j;
	cin >> h >> w;
	int a, b;
	cin >> a >> b;
	vs m(h);
	for (i = 0; i < h; i++) {
		cin >> m[i];
	}
	int c = 0;
	int tate = 0, yoko = 0, zen = 0;
	for (i = 0; i < h / 2; i++) {
		for (j = 0; j < w / 2; j++) {
			if (m[i][j] == 'S' && m[i][w - j - 1] == 'S' && m[h - i - 1][j] == 'S' && m[h - i - 1][w - j - 1] == 'S') {
				zen++;
				m[i][j] = m[i][w - j - 1] = m[h - i - 1][j] = m[h - i - 1][w - j - 1] = 'Z';
			}
		}
	}
	bool flag = false;
	for (i = 0; i < h; i++) {
		for (j = 0; j < w; j++) {
			if (m[i][j] == 'S') {
				flag = true;
			}
		}
	}
	if (!flag) {
		c = 1;
	}
	for (i = 0; i < h / 2; i++) {
		for (j = 0; j < w; j++) {
			if (m[i][j] == 'S' && m[h - i - 1][j] == 'S') {
				tate++;
				m[i][j] = m[h - i - 1][j] = 'T';
			}
		}
	}
	flag = true;
	if (!c) {
		flag = false;
		for (i = 0; i < h; i++) {
			for (j = 0; j < w; j++) {
				if (m[i][j] == 'S') {
					flag = true;
				}
			}
		}
	}
	if (!flag) {
		c = 2;
	}
	for (i = 0; i < h; i++) {
		for (j = 0; j < w / 2; j++) {
			if ((m[i][j] == 'S' || m[i][j] == 'T') && (m[i][w - j - 1] == 'S' || m[i][w - j - 1] == 'T')) {
				yoko++;
				m[i][j] = m[i][w - j - 1] = 'Y';
			}
		}
	}
	flag = true;
	if (!c) {
		flag = false;
		for (i = 0; i < h; i++) {
			for (j = 0; j < w; j++) {
				if (m[i][j] == 'S' || m[i][j] == 'T') {
					flag = true;
				}
			}
		}
	}
	if (!flag) {
		c = 3;
	}
	//cout << yoko << " " << tate << " " << zen << endl;
	int ans = 0;
	if (yoko * b < tate*a) {
		ans += tate*a;
		if (c == 2) {
			ans -= a;
		}
	}
	else {
		ans += yoko*b;
		if (c == 3) {
			ans -= b;
		}
	}
	if (c != 1) {
		ans += a + b;
	}
	ans += zen*(max(a, b) + a + b);
	cout << ans << endl;
}