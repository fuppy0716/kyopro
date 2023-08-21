class Zaatsu {
    bool is_build;
    vector<ll> elements;

  public:
    Zaatsu() : is_build(false) {}

    void add(ll x) {
        elements.push_back(x);
    }

    void add(vl x) {
        for (int i = 0; i < (int)x.size(); i++) {
            elements.push_back(x[i]);
        }
    }

    int build() {
        sort(elements.begin(), elements.end());
        UNIQUE(elements);
        is_build = true;
        return elements.size();
    }

    int find(ll x) {
        assert(is_build);
        return lower_bound(elements.begin(), elements.end(), x) - elements.begin();
    }

    ll original(int i) {
        assert(is_build);
        return elements[i];
    }
};