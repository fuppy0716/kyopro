// https://qiita.com/hotman78/items/9c643feae1de087e6fc5
constexpr int B = 16;
template <typename T>
struct PersistentArray {
    // B = 3 の時、以下のような三分木の構造
    // 0
    // (1 2 3)
    // (4 7 10) (5 8 11) (6 9 12)

    struct Node {
        T data;
        Node *ch[B] = {};
    };

    // roots[i]: i 個目の変更操作を行なった後の木の根。最初の根は roots[0] である。
    vector<Node *> roots;

    PersistentArray() {
        roots.push_back(new Node());
    }

    PersistentArray(vector<T> v) {
        roots.push_back(new Node());
        for (int i = 0; i < (int)v.size(); i++) {
            set_without_copy(i, v[i], roots[0]);
        }
    }

    Node *set_without_copy(int i, T x, Node *node) {
        // 初期化処理以外で使うとバグる可能性が高いことに注意
        if (!node) node = new Node();

        if (i == 0) {
            node->data = x;
        } else {
            int ni = i % B;
            node->ch[ni] = set_without_copy(i / B, x, node->ch[ni]);
        }
        return node;
    }

    void set(int time, int i, T x) {
        // time 個目の変更操作を行った後の配列に対して、i 番目の要素を x にする。
        roots.push_back(set(i, x, roots[time]));
    }

    Node *set(int i, T x, Node *node) {
        Node *res = new Node();
        if (node) {
            // すでにノードが存在する場合は、そのノードをコピーする。
            memcpy(res->ch, node->ch, sizeof(node->ch));
            res->data = node->data;
        }

        if (i == 0) {
            res->data = x;
        } else {
            int ni = i % B;
            res->ch[ni] = set(i / B, x, res->ch[ni]);
        }
        return res;
    }

    T get(int time, int i) {
        // time 個目の変更操作を行った後の配列に対して、i 番目の要素を取得する。
        return get(i, roots[time]);
    }

    T get(int i, Node *node) {
        if (i == 0) {
            return node->data;
        } else {
            return get(i / B, node->ch[i % B]);
        }
    }

    void copy(int time) {
        // time 個目の変更操作を行った後の配列をコピーする。
        Node *copied = new Node();
        memcpy(copied->ch, roots[time]->ch, sizeof(roots[time]->ch));
        copied->data = roots[time]->data;
        roots.push_back(copied);
    }
};

// https://judge.yosupo.jp/submission/185911
template <typename T>
struct PersistentQueue {
    // i 個目の変更操作を行った後の配列自体を格納する。
    PersistentArray<T> arr;
    // front_idx[i]: i 個目の変更操作を行った後のキューの先頭のインデックス。
    // back_idx[i]: i 個目の変更操作を行った後のキューの末尾のインデックス。
    vector<int> front_idx, back_idx;

    PersistentQueue() {
        front_idx.push_back(0);
        back_idx.push_back(0);
    }

    void push(int time, T x) {
        // time 個目の変更操作を行った後のキューに対して、末尾に x を追加する。
        arr.set(time, back_idx[time], x);
        front_idx.push_back(front_idx[time]);
        back_idx.push_back(back_idx[time] + 1);
    }

    T front(int time) {
        // time 個目の変更操作を行った後のキューの先頭の要素を取得する。
        return arr.get(time, front_idx[time]);
    }

    T pop(int time) {
        // time 個目の変更操作を行った後のキューの先頭の要素を削除した新たな配列を返す。
        T ret = front(time);
        arr.copy(time);
        front_idx.push_back(front_idx[time] + 1);
        back_idx.push_back(back_idx[time]);
        return ret;
    }
};

// https://judge.yosupo.jp/submission/185917
class PersistentUnionFind {
  private:
    // i 個目の変更操作を行った後の配列自体を格納する。
    PersistentArray<int> par_;
    PersistentArray<int> ran_;

  public:
    int n;

    PersistentUnionFind(int _n) {
        n = _n;
        vi par_ini(n), ran_ini(n);
        for (int i = 0; i < n; i++) {
            par_ini[i] = i;
        }
        par_ = PersistentArray<int>(par_ini);
        ran_ = PersistentArray<int>(ran_ini);
    }

    int find(int time, int x) {
        // time 個目の変更操作を行った後の配列に対して、x の根を求める。
        if (par_.get(time, x) == x) {
            return x;
        } else {
            // 縮約は行なっていない
            return find(time, par_.get(time, x));
        }
    }

    void unite(int time, int x, int y) {
        // time 個目の変更操作を行なった後の配列に対して、x と y を併合する（変更操作）
        x = find(time, x);
        y = find(time, y);
        if (x == y) {
            par_.copy(time);
            ran_.copy(time);
            return;
        }

        int ran_x = ran_.get(time, x), ran_y = ran_.get(time, y);
        if (ran_x < ran_y) {
            par_.set(time, x, y);
            ran_.copy(time);
        } else {
            par_.set(time, y, x);
            if (ran_x == ran_y) {
                ran_.set(time, x, ran_x + 1);
            } else {
                ran_.copy(time);
            }
        }
    }

    bool same(int time, int x, int y) {
        // time 個目の変更操作を行った後の配列に対して、x と y が同じグループに属するかどうかを判定する。
        return find(time, x) == find(time, y);
    }
};
