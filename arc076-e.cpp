int main() {
	ll r, c, n;
	scanf("%lld%lld%lld", &r, &c, &n);
	int i, j;
	vector< pair<pll, pll> > vp;
	for (i = 0; i < n; i++) {
		ll x1, x2, y1, y2;
		scanf("%lld%lld%lld%lld", &x1, &y1, &x2, &y2);
		if ((x1 == 0 || x1 == r || y1 == 0 || y1 == c) &&
			(x2 == 0 || x2 == r || y2 == 0 || y2 == c)) {
			pii temp1 = pll(x1, y1);
			pii temp2 = pll(x2, y2);
			vp.push_back(make_pair(temp1, temp2));
		}
	}
	n = vp.size();
	vector<pll> l1, l2, l3, l4;
	for (i = 0; i < n; i++) {
		ll x1 = vp[i].first.first;
		ll x2 = vp[i].second.first;
		ll y1 = vp[i].first.second;
		ll y2 = vp[i].second.second;
		if (x1 == 0) {
			l4.push_back(pll(y1, i));
		}
		else if (x1 == r) {
			l2.push_back(pll(y1, i));
		}
		else if (y1 == 0) {
			l1.push_back(pll(x1, i));
		}
		else if (y1 == c) {
			l3.push_back(pll(x1, i));
		}

		if (x2 == 0) {
			l4.push_back(pll(y2, i));
		}
		else if (x2 == r) {
			l2.push_back(pll(y2, i));
		}
		else if (y2 == 0) {
			l1.push_back(pll(x2, i));
		}
		else {
			l3.push_back(pll(x2, i));
		}
	}
	sort(l1.begin(), l1.end());
	sort(l2.begin(), l2.end());
	sort(l3.begin(), l3.end());
	reverse(l3.begin(), l3.end());
	sort(l4.begin(), l4.end());
	reverse(l4.begin(), l4.end());
	ll cnt = 0;
	vl used(n, false);
	vector<pll> l;
	l.insert(l.end(), l1.begin(), l1.end());
	l.insert(l.end(), l2.begin(), l2.end());
	l.insert(l.end(), l3.begin(), l3.end());
	l.insert(l.end(), l4.begin(), l4.end());
	stack<int> st;
	for (i = 0; i < 2 * n; i++) {
		if (!used[l[i].second]) {
			st.push(l[i].second);
			used[l[i].second] = true;
		}
		else {
			if (st.top() == l[i].second) {
				st.pop();
				used[l[i].second] = false;
			}
			else {
				cout << "NO" << endl;
				return 0;
			}
		}
	}
	cout << "YES" << endl;
	return 0;
}