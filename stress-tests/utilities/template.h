// copied from contest/template.cpp, for standalone inclusion.
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
