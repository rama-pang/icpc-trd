#if not LOCAL
#define NDEBUG 1
#endif
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(auto i = a; i < (b); ++i)
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
	cin.exceptions(cin.failbit);
}

// extra

template<class T> struct YComb_{
	T f;
	template<class... Args> auto operator()(Args&&... args)const{
		return f(ref(*this), forward<Args>(args)...);
	}
};
template<class T> YComb_<T> YComb(T f){ return {move(f)}; }

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
