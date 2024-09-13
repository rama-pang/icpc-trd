/**
 * Author: rama_pang
 * Description: Centroid decomposition.
 * Usage: auto precomp = [](CenDec\& cen, int centroid) {}; CenDec cen(n, edges, precomp);
 * Time: O(n \log n)
 * Status: hopefully safe.
 */
struct CenDec {
  int n;
  function<void(CenDec&, int)> precomp;
  vector<int> siz, dead, cpar, cdep;
  vector<vector<pii>> adj;
  vector<vector<int>> cdist;
  CenDec(int n, vector<pii> edges, auto&& f)
      : n(n), precomp(forward<decltype(f)>(f)),
        siz(n), dead(n), cpar(n), cdep(n), adj(n) {
    rep(i, 0, n - 1) {
      auto [u, v] = edges[i];
      adj[u].push_back({2 * i, v});
      adj[v].push_back({2 * i + 1, u});
    }
  }
  int centroid(int x) {
    YComb([&](auto self, int x, int p) -> void {
      siz[x] = 1;
      for (auto [i, y] : adj[x])
        if (!dead[y] && y != p) self(y, x), siz[x] += siz[y];
    })(x, -1);
    int tot = siz[x];
    return YComb([&](auto self, int x) -> int {
      for (auto [i, y] : adj[x])
        if (!dead[y] && siz[y] < siz[x] && siz[y] * 2 > tot) return self(y);
      return x;
    })(x);
  }
  void decomp(int sub = 0, int cp = -1, int lev = 0) {
    int x = centroid(sub);
    dead[x] = 1, cpar[x] = cp, siz[x] = siz[sub], cdep[x] = lev;
    while (sz(cdist) <= cdep[x]) cdist.push_back(vector(n, int(0)));
    cdist[cdep[x]][x] = 0;
    let f = YComb([&](auto f, int x, int p) -> void {
      cdist[lev][x] = cdist[lev][p] + 1;
      for (auto [i, y] : adj[x]) if (!dead[y] && y != p) f(y, x);
    });
    for (auto [i, y] : adj[x]) if (!dead[y]) f(y, x);
    precomp(*this, x);
    for (auto [i, y] : adj[x]) if (!dead[y]) decomp(y, x, lev + 1);
  }
};