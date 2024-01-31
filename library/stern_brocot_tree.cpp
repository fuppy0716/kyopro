
struct Rational {
    // 分数 p / q, 負の時は p が負
    ll p, q;

    Rational(ll p = 0, ll q = 1) {
        if (p == 0) {
            assert(q != 0);
            this->p = 0, this->q = 1;
        } else {
            ll g = std::gcd(p, q);
            p /= g, q /= g;
            if (q < 0) p = -p, q = -q;
            this->p = p, this->q = q;
        }
    }
};

// Stern–Brocot tree
// https://satashun.hatenablog.com/entry/2018/12/13/163524
// Stern-Brocot tree と連分数分解の関係
// 連分数分解において [a_0; a_1, a_2, ..., a_k] と [a_0; a_1, ..., a_k - 1, 1] は同じ分数を表す
// 有利数 p/q を連分数分解すると [a_0; a_1, a_2, ..., a_k] になったとして（a_k != 1）、その子は
// [a_0; a_1, a_2, ..., a_k + 1] と [a_0; a_1, a_2, ..., a_k - 1, 2] になる。
// 左の子（小さい方）は k が偶数の時は前者、奇数の時は後者になる。
// 逆に親は末尾の数を -1 したものになる。
// verify: https://judge.yosupo.jp/submission/187466
struct SternBrocotTree {
    Rational rat;
    // rat から下がってたどり着ける範囲は開区間 (left, right)
    Rational left, right;
    // 連分数分解。1/1 を除いて末尾が 1 ではない表現
    vector<ll> a;
    // 深さ。1/1 が 0
    ll depth;

    SternBrocotTree(Rational rat_ = Rational(1, 1)) {
        assert(rat_.p != 0);
        assert(rat_.q != 0);
        vector<ll> target = calc_continued_fraction_decomposition(rat_);

        build_from_continued_fraction_decomposition(target);
    }

    void build_from_continued_fraction_decomposition(vector<ll> target) {
        // 1/1 から下がることでコンストラクトする
        // そうしないと left, right を適切に設定する方法がわからないので
        rat = Rational(1, 1);
        left = Rational(0, 1);
        right = Rational(1, 0);
        a = {1};
        depth = 0;

        rep(i, target.size()) {
            ll this_target = target[i];
            if (i != target.size() - 1) {
                this_target++;
            }

            if ((i + 1) % 2 == 0) {
                // 末尾に +1 は左の子への操作
                to_left(this_target - a[i]);
            } else {
                to_right(this_target - a[i]);
            }

            if (i != target.size() - 1) {
                a.back()--;
                a.push_back(1);
            }
        }
    }

    static vector<ll> calc_continued_fraction_decomposition(Rational rat) {
        // rat の連分数分解を返す
        // 末尾が 1 でない形式で返す
        ll p = rat.p, q = rat.q;
        vector<ll> ret;
        while (q != 0) {
            ret.push_back(p / q);
            p %= q;
            swap(p, q);
        }
        if (ret.back() == 1 and ret.size() > 1) {
            ret.pop_back();
            ret.back()--;
        }
        return ret;
    }

    SternBrocotTree lca(SternBrocotTree other) {
        vector<ll> ca;
        rep(i, min(a.size(), other.a.size())) {
            ll mi = min(a[i], other.a[i]);
            ca.push_back(mi);
            if (a[i] != other.a[i]) {
                // mi でかつ最後というのがなければ += 1
                bool add = true;
                if (a[i] == mi and i == a.size() - 1) {
                    add = false;
                }
                if (other.a[i] == mi and i == other.a.size() - 1) {
                    add = false;
                }
                if (add) {
                    ca.back()++;
                }

                break;
            }
        }

        SternBrocotTree ret;
        ret.build_from_continued_fraction_decomposition(ca);
        return ret;
    }

    bool to_up(ll k) {
        // 現在地点から上に k 回登る
        if (k > depth) {
            return false;
        }

        rrep(i, a.size()) {
            ll x = min(a[i] - 1, k);

            bool is_right = true;
            if ((i + 1) % 2 == 0) {
                // 偶数のとき、末尾に +1 は左の子に行く操作
                is_right = false;
            }

            if (is_right) {
                left.p -= right.p * x, left.q -= right.q * x;
                rat.p -= right.p * x, rat.q -= right.q * x;
            } else {
                right.p -= left.p * x, right.q -= left.q * x;
                rat.p -= left.p * x, rat.q -= left.q * x;
            }
            a.back() -= x;
            if (a.back() == 1 and a.size() > 1) {
                a.pop_back();
                a.back()++;
            }
            depth -= x;
            k -= x;
            if (k == 0) {
                break;
            }
        }
        return true;
    }

    void to_right(ll k) {
        // 現在地点から右の子に k 回移動する
        if (k == 0) {
            return;
        }
        if (a.size() % 2 == 0) {
            a.back()--;
            a.emplace_back(1);
        }
        a.back() += k;
        depth += k;

        // left は (k - 1) 回右に行ったところになる
        left = Rational(rat.p + (k - 1) * right.p, rat.q + (k - 1) * right.q);
        // rat は k 回右に行ったところになる
        rat = Rational(rat.p + k * right.p, rat.q + k * right.q);
    }

    void to_left(ll k) {
        // 現在地点から左の子に k 回移動する
        if (k == 0) {
            return;
        }
        if (a.size() % 2 == 1) {
            a.back()--;
            a.emplace_back(1);
        }
        a.back() += k;
        depth += k;

        // right は (k - 1) 回左に行ったところになる
        right = Rational(rat.p + (k - 1) * left.p, rat.q + (k - 1) * left.q);
        // rat は k 回左に行ったところになる
        rat = Rational(rat.p + k * left.p, rat.q + k * left.q);
    }

    vector<pair<bool, ll>> down_nums() {
        // a は連分数分解の形式なので、1/1 からどっち方向の下に何回下がったかの形式に変換
        // true は右、false は左を表す
        vector<pair<bool, ll>> ans;

        int added = 0;
        rrep(i, a.size()) {
            ll x = a[i] + added;
            bool dir;
            if ((i + 1) % 2 == 0) {
                // 偶数のとき、末尾に +1 は左の子に行く操作
                dir = false;
            } else {
                dir = true;
            }
            // x が 1 になるまでは上に登る
            if (x - 1 > 0) {
                ans.emplace_back(dir, x - 1);
            }
            // 繰り上がり
            added = 1;
        }
        reverse(all(ans));
        return ans;
    }
};