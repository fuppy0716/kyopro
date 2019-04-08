#include <bits/stdc++.h>
using namespace std;

int main() {
  random_device rnd;     // 非決定的な乱数生成器を生成
  mt19937 mt(rnd());     //  メルセンヌ・ツイスタの32ビット版、引数は初期シード値
  uniform_int_distribution<> rand100(0, 99);        // [0, 99] 範囲の一様乱数
  for (int i = 0; i < 20; ++i) {
    cout << rand100(mt) << "\n";
  }
}
