#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using lint = long long;
using pii = pair<int, int>;
using vi = vector<int>;

template <class F>
class YComb_ {
  F f_;
 public:
  template <class T>
  explicit YComb_(T&& f) : f_(forward<T>(f)) {}
  template <class... Args>
  decltype(auto) operator()(Args&&... args) {
    return f_(ref(*this), forward<Args>(args)...);
  }
};

template <class F>
decltype(auto) YComb(F&& f) {
  return YComb_<decay_t<F>>(forward<F>(f));
}

#define let auto const

#define repeat(x, a, b) for (auto x = a; x < (b); x++)
#define down(x, a) for (auto x = a; x--;)
#define len(x) int(size(x))
#define all(x) begin(x), end(x)

#define rep repeat
#define sz len

template <class T>
auto& operator>>(istream& s, vector<T>& v) {
  for (auto& x : v) s >> x;
  return s;
}

template <class A, class B>
auto& operator>>(istream& s, pair<A, B>& v) {
  return s >> v.first >> v.second;
}

template <class T>
auto& operator<<(ostream& s, vector<T> const& v) {
  for (auto& x : v) s << x << ' ';
  return s;
}

template <class A, class B>
auto& operator<<(ostream& s, pair<A, B> const& v) {
  return s << v.first << ' ' << v.second;
}

#define lambda(x, y) [&](let& x) { return (y); }
#define lambda2(x, y, z) [&](let& x, let& y) { return (z); }
#define compare_by(e) lambda2(x, y, lambda(it, e)(x) < lambda(it, e)(y))
#define apply(f, v, e...) ([&] { let _tmp = v; return f(all(_tmp), e); }())

auto iota(int l, int r) {
  assert(l <= r);
  vector<int> a(r - l);
  iota(all(a), l);
  return a;
}

auto iota(int r) { return iota(0, r); }

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  
  
}
