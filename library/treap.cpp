struct dice {
    mt19937 mt;
    dice() : mt(chrono::steady_clock::now().time_since_epoch().count()) {}
    // [0, x)の一様乱数
    ll operator()(ll x) { return this->operator()(0, x); }
    // [x, y)の一様乱数
    ll operator()(ll x, ll y) {
        uniform_int_distribution<ll> dist(x, y - 1);
        return dist(mt);
    }
    vl operator()(int n, ll x, ll y) {
        vl res(n);
        for (int i = 0; i < n; i++)
            res[i] = this->operator()(x, y);
        return res;
    }
} rnd;

std::random_device seed_gen;
std::mt19937 engine(seed_gen());

namespace treap {
// https://www.slideshare.net/iwiwi/2-12188757
// セグ木に似た感じで、配列に関する操作を行うことができる
// 使用例: https://judge.yosupo.jp/submission/204808
constexpr int MAX_PRI = 1e8;

// モノイドの型, lazy の型
template <typename S, typename F>
struct Node {
    // 自分自身の値
    // この値は配列の値に相当するものであり、インデックスに当たるものではないことに注意
    // 子の左右の振り分けにはインデックスが使われ、この値は使われない。インデックスは陽に管理はされず、部分木のサイズで代用される
    S val;
    // 優先度
    int pri;
    // 左右の子
    Node *lch;
    Node *rch;

    // 部分木のサイズ
    int cnt;
    // 部分木の値の集約結果
    // lazy は常に dat には反映済みとする。子に lazy が伝搬された時に lazy を単位元に戻す。
    S dat;

    bool rev;
    F lazy;

    Node(S v, S s, F f, int p = rnd(MAX_PRI)) : val(v), pri(p), cnt(1), dat(s), rev(false), lazy(f) {
        lch = NULL;
        rch = NULL;
    }
};

template <typename S, typename F>
struct Treap {
    // 自分の値、左の子の集約結果、右の子の集約結果を引数に取り、自分の集約結果を返す関数
    using Op = function<S(S, S, S)>;
    // モノイドに lazy を反映する関数。最後の int は部分木のサイズ
    using Mapping = function<S(S, F, int)>;
    // 一つ目の引数が元々ある lazy, 二つ目が追加される lazy
    using Composition = function<F(F, F)>;

    using N = Node<S, F>;

    N *root;
    Op op;
    Mapping mapping;
    Composition composition;
    S e;
    F id;

    Treap(Op op, Mapping mapping, Composition composition, S e, F id) : op(op), mapping(mapping), composition(composition), e(e), id(id) {
        root = NULL;
    }

    int size() {
        return count(root);
    }

    void insert(int k, S val) {
        root = insert(root, k, val);
    }

    void erase(int k) {
        root = erase(root, k);
    }

    void reverse(int l, int r) {
        root = reverse(root, l, r);
    }

    S query(int l, int r) {
        return query(root, l, r);
    }

    void update(int l, int r, F f) {
        root = update(root, l, r, f);
    }

  private:
    int count(const N *node) {
        return node ? node->cnt : 0;
    }

    S get_dat(const N *node) {
        return node ? node->dat : e;
    }

    N *refresh(N *node) {
        if (node) {
            node->cnt = count(node->lch) + count(node->rch) + 1;
            node->dat = op(node->val, get_dat(node->lch), get_dat(node->rch));
        }
        return node;
    }

    N *push_down(N *node) {
        // node->dat と node->val に node->lazy は反映されているという前提
        if (node && node->rev) {
            swap(node->lch, node->rch);
            if (node->lch) {
                node->lch->rev ^= true;
            }
            if (node->rch) {
                node->rch->rev ^= true;
            }
            node->rev = false;
        }
        if (node && node->lazy != id) {
            if (node->lch) {
                node->lch->lazy = composition(node->lch->lazy, node->lazy);
                node->lch->dat = mapping(node->lch->dat, node->lazy, count(node->lch));
                node->lch->val = mapping(node->lch->val, node->lazy, 1);
            }
            if (node->rch) {
                node->rch->lazy = composition(node->rch->lazy, node->lazy);
                node->rch->dat = mapping(node->rch->dat, node->lazy, count(node->rch));
                node->rch->val = mapping(node->rch->val, node->lazy, 1);
            }
            node->lazy = id;
        }
        return refresh(node);
    }

    N *merge(N *l, N *r) {
        if (!l || !r) {
            return l ? l : r;
        }
        push_down(l);
        push_down(r);

        if (l->pri > r->pri) {
            l->rch = merge(l->rch, r);
            return refresh(l);
        } else {
            r->lch = merge(l, r->lch);
            return refresh(r);
        }
    }

    pair<N *, N *> split(N *t, int k) {
        // t を [0, k) と [k, size) に分解する
        if (!t) {
            return {NULL, NULL};
        }
        push_down(t);

        if (k <= count(t->lch)) {
            auto s = split(t->lch, k);
            t->lch = s.second;
            return {s.first, refresh(t)};
        } else {
            // 1 は t 自身の分
            auto s = split(t->rch, k - count(t->lch) - 1);
            t->rch = s.first;
            return {refresh(t), s.second};
        }
    }

    N *insert(N *t, int k, S val, int pri = rnd(MAX_PRI)) {
        // t が根になっている木の k 番目に値が val でモノイドが S で優先度が pri のノードを挿入
        auto [l, r] = split(t, k);
        return merge(merge(l, new N(val, val, id, pri)), r);
    }

    N *erase(N *t, int k) {
        // t が根になっている木の k 番目の要素を削除
        auto [l, mr] = split(t, k);
        auto [_, r] = split(mr, 1);
        return merge(l, r);
    }

    N *reverse(N *t, int l, int r) {
        // [l, r) の要素を反転
        if (l >= r) {
            return t;
        }
        auto [tlm, tr] = split(t, r);
        auto [tl, tm] = split(tlm, l);
        tm->rev ^= true;
        t = merge(merge(tl, tm), tr);
        return t;
    }

    S query(N *t, int l, int r) {
        if (l >= r) {
            return e;
        }
        // [l, r) のクエリ
        auto [tlm, tr] = split(t, r);
        auto [tl, tm] = split(tlm, l);
        S ret = get_dat(tm);
        t = merge(merge(tl, tm), tr);
        return ret;
    }

    N *update(N *t, int l, int r, F f) {
        if (l >= r) {
            return t;
        }
        // [l, r) のクエリ
        auto [tlm, tr] = split(t, r);
        auto [tl, tm] = split(tlm, l);
        tm->lazy = composition(tm->lazy, f);
        tm->dat = mapping(tm->dat, f, count(tm));
        tm->val = mapping(tm->val, f, 1);
        t = merge(merge(tl, tm), tr);
        return t;
    }
};
}; // namespace treap
using namespace treap;
