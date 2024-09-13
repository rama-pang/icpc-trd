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
signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
}
template <class T> struct YComb {
  T f;
  template <class... A>
  auto operator()(A&&... a) const {
    return f(ref(*this), forward<A>(a)...);
  }
};
template <class T> concept Print =
  !is_convertible_v<decay_t<T>, string> &&
  (R::range<T> || requires { tuple_size<decay_t<T>>::value; });
template <Print T>
auto& operator>>(istream& s, T&& v) {
  let f=[&](auto&&...x){((s >> x), ...);};
  if constexpr(R::range<T>)R::for_each(v, f);
  else { apply(f, v); } return s; }
template <Print T>
auto& operator<<(ostream& s, T&& v) {
  let f=[&](auto&&...x){((s << x << ' '), ...);};
  if constexpr(R::range<T>)R::for_each(v, f);
  else { apply(f, v); } return s; }