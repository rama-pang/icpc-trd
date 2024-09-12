#if not LOCAL
#define NDEBUG 1
#endif
#include <bits/stdc++.h>
using namespace std;
namespace R = ranges;
namespace V = views;
#define rep(i,a,b) for(auto i=a; i<(b); ++i)
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
    return f(ref(*this),forward<A>(a)...);}};
template <class A, class B> auto&
operator>>(istream& s, pair<A, B>& v) {
  return s >> v.first >> v.second; }
template <class... A> auto&
operator>>(istream& s, tuple<A...>& v) {
  apply([&](auto&&... x) { ((s >> x), ...); }, v);
  return s; }
template <R::range T> auto&
operator>>(istream& s, T&& v) {
  R::for_each(v, [&](auto&& x) { s >> x; });
  return s; }
template <class A, class B> auto&
operator<<(ostream& s, pair<A, B> const& v) {
  return s << v.first << ' ' << v.second; }
template <class... A> auto&
operator<<(ostream& s, tuple<A...> const& v) {
  apply([&](auto&&... x) { ((s << x << ' '), ...); }, v);
  return s; }
template <R::range T> auto&
operator<<(ostream& s, T&& v) {
  R::for_each(v, [&](auto&& x) { s << x << ' '; });
  return s; }
template <R::input_range... T> struct zip_view
  : R::view_interface<zip_view<T...>> {
  static bool any_match(auto&& l, auto&& r) {
    return [&]<size_t... I>(index_sequence<I...>) { return
    (... | (get<I>(l) == get<I>(r))); }(index_sequence_for<T...>{}); }
  template <class... U> struct iterator {
    using iterator_category = input_iterator_tag;
    using value_type = tuple<R::range_value_t<T>...>;
    using reference = tuple<R::range_reference_t<T>...>;
    using difference_type = ptrdiff_t;
    iterator& operator++() { apply([](auto&&... a) {
      ((++a), ...); }, i);return *this; }
    iterator operator++(int) { auto copy = *this; ++*this; return copy; }
    reference operator*() const { return apply(
      [](auto&&... a) { return reference(*a...); }, i); }
    bool operator==(auto&& o) const { return any_match(i, o.i); }
    tuple<U...> i; };
  auto begin(){return apply([](auto&&... a){
    return iterator<decltype(R::begin(a))...>({R::begin(a)...});},m);}
  auto end(){return apply([](auto&&... a){
    return iterator<decltype(R::end(a))...>({R::end(a)...});},m);}
  zip_view(T&&... t) : m(forward<T>(t)...) {} tuple<T...> m; };
template<R::input_range...T>auto zip(T&&... t){
  return zip_view<T...>(forward<T>(t)...);}
struct enumerate{template <R::input_range T>
  auto operator()(T&& t) const { return zip(V::iota(0), forward<T>(t)); }
  template <R::input_range T> friend auto
  operator|(T&& t, enumerate e) { return e(forward<T>(t)); }
} enumerate;