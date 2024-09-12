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

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
}

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
#define W(f) apply([](auto&&...a){return f;},i)
#define D(x) W(iterator<decltype(x(a))...>({x(a)...}))
template<class... A>struct zip_view
  : R::view_interface<zip_view<A...>> {
  template<class...B>struct iterator{tuple<B...> i;
    using iterator_category = input_iterator_tag;
    using value_type = tuple<R::range_value_t<A>...>;
    using reference = tuple<R::range_reference_t<A>...>;
    using difference_type = ptrdiff_t;
    iterator& operator++() { W(((++a), ...)); return *this; }
    iterator operator++(int) { auto a = *this; ++*this; return a; }
    reference operator*() const { return W(reference(*a...)); }
    bool operator==(auto&& o) const { return [&]<size_t...I>
    (index_sequence<I...>) { return ((get<I>(i)==get<I>(o.i))|...);
    }(index_sequence_for<B...>{}); } };
  auto begin(){return D(R::begin);} auto end(){return D(R::end); }
  zip_view(A&&... a) : i(forward<A>(a)...) {} tuple<A...> i; };
#undef W
#undef D
template<R::input_range...A>auto zip(A&&... a){
  return zip_view<A...>(forward<A>(a)...); }
template<R::input_range A>auto enumerate(A&& a) {
  return zip(V::iota(0), forward<A>(a)); }