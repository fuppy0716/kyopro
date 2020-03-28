typedef string::const_iterator State;
class ParseError {};

ll number(State&);
ll factor(State&);
ll term(State&);
ll expression(State&);

ll number(State &begin) {
  ll ret = 0;
  while (isdigit(*begin)) {
    ret *= 10;
    ret += *begin - '0';
    begin++;
  }
  return ret;
}

ll factor(State &begin) {
  if (*begin == '(') {
    begin++; // '('を飛ばす。
    ll ret = expression(begin);
    begin++; // ')'を飛ばす。
    return ret;
  } else {
    return number(begin);
  }
}

ll term(State &begin) {
  ll ret = factor(begin);
  for (;;) {
    if (*begin == '*') {
      begin++;
      ret *= factor(begin);
    }
    else if (*begin == '/') {
      begin++;
      ret /= factor(begin);
    }
    else {
      break;
    }
  }
  return ret;
}

ll expression(State &begin) {
  ll ret = term(begin);
  for (;;) {
    if (*begin == '+') {
      begin++;
      ret += term(begin);
    }
    else if (*begin == '-') {
      begin++;
      ret -= term(begin);
    }
    else {
      break;
    }
  }
  return ret;
}


int main () {
  string s;
  cin >> s;
  s.push_back('=');
  State begin = s.begin();
  ll ans = expression(begin);
  cout << ans << endl;  
}
