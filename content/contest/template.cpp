#if not LOCAL
#define NDEBUG 1
#endif
#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (auto i = a; i < (b); ++i)
#define down(x, a) for (auto x = a; x--;)
#define all(x) begin(x), end(x)
#define sz(x) int(size(x))
#define let auto const
using ll = long long;
using lint = ll;
using pii = pair<int, int>;
using vi = vector<int>;
int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit); }
template <class T> struct YComb { T f; 
	template <class... A> auto operator()(A&&... a) const {
    return f(ref(*this), forward<A>(a)...); } };
auto iota(auto l, auto r) { return views::iota(l, r); }
auto iota(auto r) { return views::iota(0, r); }
template <class T>
requires ranges::range<T>
auto& operator>>(istream& s, T&& v) {
  ranges::for_each(v, [&](auto&& x) { s >> x; });
  return s; }
template <class A, class B>
auto& operator>>(istream& s, pair<A, B>& v) {
  return s >> v.first >> v.second; }
template <class... A>
auto& operator>>(istream& s, tuple<A...>& v) {
  apply([&](auto&... x) { ((s >> x), ...); }, v);
  return s; }
template <class T>
requires ranges::range<T>
auto& operator<<(ostream& s, T&& v) {
  ranges::for_each(v, [&](auto&& x) { s << x << ' '; });
  return s; }
template <class A, class B>
auto& operator<<(ostream& s, pair<A, B> const& v) {
  return s << v.first << ' ' << v.second; }
template <class... A>
auto& operator<<(ostream& s, tuple<A...> const& v) {
  apply([&](auto&... x) { ((s << x << ' '), ...); }, v);
  return s; }
#define lambda(x, y) [&](let& x) { return (y); }
#define lambda2(x, y, z) [&](let& x, let& y) { return (z); }
#define compare_by(e) lambda2(x, y, lambda(it, e)(x) < lambda(it, e)(y))
#define apply(f, v, e...) ([&] { let _tmp = v; return f(all(_tmp), e); }())