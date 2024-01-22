// https://judge.yosupo.jp/submission/185446
template <typename T>
pair<vii, int> cartesian_tree(vector<T> a) {
    // cartesion tree を構築する
    // 親から子への有向グラフと、根の頂点インデックスを返す
    // 最小の要素を根とする

    int n = a.size();
    stack<int> st;
    vi par(n, -1);
    vii G(n);
    vector<int> popped;
    rep(i, n) {
        if (st.empty() or a[st.top()] < a[i]) {
            st.push(i);
            continue;
        }

        popped.clear();
        while (!st.empty() and a[st.top()] > a[i]) {
            popped.push_back(st.top());
            st.pop();
        }
        rrep(i, (int)popped.size() - 1) {
            int v = popped[i];
            int u = popped[i + 1];
            par[v] = u;
            G[u].push_back(v);
        }
        par[popped.back()] = i;
        G[i].push_back(popped.back());

        st.push(i);
    }
    while (st.size() > 1) {
        int v = st.top();
        st.pop();
        int u = st.top();
        par[v] = u;
        G[u].push_back(v);
    }

    int root = -1;
    rep(i, n) {
        if (par[i] == -1) {
            root = i;
            break;
        }
    }
    return make_pair(G, root);
}
