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


//#include "bits/stdc++.h"
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
const ll INF = 1e18 * 4;
#define MOD 1000000007
#define mod 1000000009
#define pi 3.14159265358979323846
#define Sp(p) cout<<setprecision(15)<< fixed<<p<<endl;
int dx[4] = { 1,0,-1,0 }, dy[4] = { 0,1,0,-1 };
int dx2[8] = { 1,1,0,-1,-1,-1,0,1 }, dy2[8] = { 0,1,1,1,0,-1,-1,-1 };

void printbit(int a) {
	for (int i = 9; i >= 1; i--) {
		int b = (1 << (i - 1));
		if (b&a) {
			cout << 1;
		}
		else {
			cout << 0;
		}
	}
	cout << " ";
}


vii dfs(vii ban, vii can, int i0, int j0) {
	/*
	printf("i:%d j:%d ban[i][j]:%d can[i][j]:", i0, j0, ban[i0][j0]);
	printbit(can[i0][j0]);
	cout << endl;
	*/
	int in, jn;
	int k;
	if (j0 != 8) {
		in = i0;
		jn = j0 + 1;
	}
	else {
		in = i0 + 1;
		jn = 0;
	}
	int bitcnt = 0, tmp = 1, kb = 0;
	for (int k = 0; k < 9; k++) {
		if (can[i0][j0] & tmp) {
			bitcnt++;
			kb = k;
		}
		tmp <<= 1;
	}
	if (bitcnt == 1) {
		ban[i0][j0] = kb + 1;
		int a = ban[i0][j0];
		for (k = 0; k < 9; k++) {
			if (j0 != k) {
				can[i0][k] &= ~(1 << (a - 1));
			}
			if (i0 != k) {
				can[k][j0] &= ~(1 << (a - 1));
			}
			if (can[k][j0] == 0 || can[i0][k] == 0) {
				ban[i0][j0] = -1;
				return ban;
			}
		}
		int i2 = i0 / 3 * 3, j2 = j0 / 3 * 3;
		for (k = 0; k < 3; k++) {
			for (int l = 0; l < 3; l++) {
				if (i2 + k != i0 || j2 + l != j0) {
					can[i2 + k][j2 + l] &= ~(1 << (a - 1));
				}
				if (can[i2 + k][j2 + l] == 0) {
					ban[i0][j0] = -1;
					return ban;
				}
			}
		}
	}
	if (bitcnt == 0) {
		ban[i0][j0] = -1;
		return ban;
	}

	if (i0 == 8 && j0 == 8) {
		return ban;
	}
	if (ban[i0][j0] != 0) {
		vii res = dfs(ban, can, in, jn);
		if (res[in][jn] == -1) {
			res[i0][j0] = -1;
		}
		return res;
	}
	for (int a = 1; a <= 9; a++) {
		if ((can[i0][j0] & (1 << (a - 1))) == 0) {
			continue;
		}
		vii ban2 = ban;
		vii can2 = can;
		ban2[i0][j0] = a;
		for (k = 0; k < 9; k++) {
			if (i0 != k) {
				can2[k][j0] &= ~(1 << (a - 1));
			}
			if (j0 != k) {
				can2[i0][k] &= ~(1 << (a - 1));
			}
			if (can2[k][j0] == 0 || can2[i0][k] == 0) {
				ban2[i0][j0] = -1;
				break;
			}
		}
		int i2 = i0 / 3 * 3, j2 = j0 / 3 * 3;
		for (k = 0; k < 3; k++) {
			for (int l = 0; l < 3; l++) {
				if (i2 + k != i0 || j2 + l != j0) {
					can2[i2 + k][j2 + l] &= ~(1 << (a - 1));
					if (can2[i2 + k][j2 + l] == 0) {
						ban2[i0][j0] = -1;
						break;
					}
				}
			}
		}
		if (ban2[i0][j0] == -1) {
			continue;
		}
		vii res = dfs(ban2, can2, in, jn);
		if (res[in][jn] != -1) {
			return res;
		}
	}
	ban[i0][j0] = -1;
	return ban;
}

int main() {
	int q;
	scanf("%d", &q);
	for (int i0 = 0; i0 < q; i0++) {
		int i, j, k, l;
		vii ban(9, vi(9));
		for (i = 0; i < 9; i++) {
			for (j = 0; j < 9; j++) {
				char c;
				scanf(" %c", &c);
				ban[i][j] = c - '0';
			}
		}
		int all = (1 << 9) - 1;
		vii can(9, vi(9, all));
		for (i = 0; i < 9; i++) {
			for (j = 0; j < 9; j++) {
				if (ban[i][j]) {
					can[i][j] = 1 << (ban[i][j] - 1);
					continue;
				}
				for (k = 0; k < 9; k++) {
					if (ban[i][k]) {
						can[i][j] &= ~(1 << (ban[i][k] - 1));
					}
					if (ban[k][j]) {
						can[i][j] &= ~(1 << (ban[k][j] - 1));
					}
				}
				int i2 = (i / 3) * 3, j2 = (j / 3) * 3;
				for (k = 0; k < 3; k++) {
					for (l = 0; l < 3; l++) {
						if (ban[i2 + k][j2 + l]) {
							can[i][j] &= ~(1 << (ban[i2 + k][j2 + l] - 1));
						}
					}
				}
				int bitcnt = 0, tmp = 1, kb = 0;
				for (k = 0; k < 9; k++) {
					if (can[i][j] & tmp) {
						bitcnt++;
						kb = k;
					}
					tmp <<= 1;
				}
				if (bitcnt == 1) {
					ban[i][j] = kb + 1;
				}
			}
		}
		/*
		for (i = 0; i < 9; i++) {
		for (j = 0; j < 9; j++) {
		printbit(can[i][j]);
		}
		cout << endl;
		}
		for (i = 0; i < 9; i++) {
		for (j = 0; j < 9; j++) {
		cout << ban[i][j];
		}
		cout << endl;
		}
		cout << endl;
		*/
		vii ans = dfs(ban, can, 0, 0);
		printf("Scenario #%d:\n", i0 + 1);
		for (i = 0; i < 9; i++) {
			for (j = 0; j < 9; j++) {
				printf("%d", ans[i][j]);
			}
			printf("\n");
		}
		printf("\n");
	}
}