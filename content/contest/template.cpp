#if not LOCAL
#define NDEBUG 1
#endif
#include <bits/stdc++.h>
using namespace std;
namespace R = ranges;
namespace V = views;

#define rep(i, a, b) for (auto i = a; i < (b); ++i)
#define down(x, a) for (auto x = a; x--;)
#define all(x) R::begin(x), R::end(x)
#define sz(x) int(R::size(x))
#define let auto const

using ll = long long;
using lint = ll;
using pii = pair<int, int>;
using vi = vector<int>;

template <class T> struct YComb { T f;
	template <class... A> auto operator()(A&&... a) const {
    return f(ref(*this), forward<A>(a)...); } };
auto iota(auto l, auto r) { return V::iota(l, r); }
auto iota(auto r) { return V::iota(0, r); }
template <R::range T>
auto& operator>>(istream& s, T&& v) {
  R::for_each(v, [&](auto&& x) { s >> x; });
  return s; }
template <class A, class B>
auto& operator>>(istream& s, pair<A, B>& v) {
  return s >> v.first >> v.second; }
template <class... A>
auto& operator>>(istream& s, tuple<A...>& v) {
  apply([&](auto&... x) { ((s >> x), ...); }, v);
  return s; }
template <R::range T>
auto& operator<<(ostream& s, T&& v) {
  R::for_each(v, [&](auto&& x) { s << x << ' '; });
  return s; }
template <class A, class B>
auto& operator<<(ostream& s, pair<A, B> const& v) {
  return s << v.first << ' ' << v.second; }
template <class... A>
auto& operator<<(ostream& s, tuple<A...> const& v) {
  apply([&](auto&... x) { ((s << x << ' '), ...); }, v);
  return s; }

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
}
