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
