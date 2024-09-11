/**
 * Author: koosaga
 * Description: Calculates DP value for all roots. Need to implement four functions:
 * (1) E: identity 
 * (2) take\_vertex: add vertex on top of merged edges
 * (3) up\_root: update child DP to consider parent edge values
 * (4) merge: merge two child edges
 * It's good if merges are commutative (its not necessary but be careful of specifics)
 * Time: O(N)
 * Status: hopefully safe.
 */
elem E() { return elem{Mod(0), Mod(0)}; }
elem take_vertex(elem DP, int v) { return elem{DP[0] + a[v], DP[1] + Mod(1)}; }
elem up_root(elem DP, int e) { return elem{DP[0] * b[e] + DP[1] * c[e], DP[1]}; }
elem merge(elem a, elem b) { return elem{a[0] + b[0], a[1] + b[1]}; }
void dfs(int x, vector<vector<pi>> &adj, vi &ord, vi &pae) {
  ord.push_back(x);
  for (auto [i, y] : adj[x]) {
    adj[y].erase(find(all(adj[y]), pi{i ^ 1, x}));
    pae[y] = (i ^ 1);
    dfs(y, adj, ord, pae);
  }
}
vector<elem> solve(int n, vector<pi> edges) {
  vector<vector<pi>> adj(n);
  rep(i, 0, n-1) {
    auto [u, v] = edges[i];
    adj[u].push_back({2 * i, v});
    adj[v].push_back({2 * i + 1, u});
  }
  vi ord, pae(n, -1);
  dfs(0, adj, ord, pae);
  vector<elem> dp(n, E()), rev_dp(n, E()), sol(n, E());
  reverse(all(ord));
  for (auto z : ord) {
    for (auto [i, y] : adj[z]) {
      dp[z] = merge(dp[z], up_root(dp[y], i));
    }
    dp[z] = take_vertex(dp[z], z);
  }
  reverse(all(ord));
  for (auto z : ord) {
    vector<elem> pref(sz(adj[z]) + 1, E()), suff(sz(adj[z]) + 1, E());
    if (~pae[z]) pref[0] = up_root(rev_dp[z], pae[z]);
    rep(i, 0, sz(adj[z])) {
      auto [e, y] = adj[z][i];
      pref[i + 1] = suff[i] = up_root(dp[y], e);
      pref[i + 1] = merge(pref[i], pref[i + 1]);
    }
    down(i, sz(adj[z])) suff[i] = merge(suff[i], suff[i + 1]);
    rep(i, 0, sz(adj[z])) {
      auto [e, y] = adj[z][i];
      rev_dp[y] = take_vertex(merge(pref[i], suff[i + 1]), z);
    }
  }
  rep(x, 0, n) {
    if (~pae[x]) sol[x] = up_root(rev_dp[x], pae[x]);
    for (auto [i, y] : adj[x]) sol[x] = merge(sol[x], up_root(dp[y], i));
    sol[x] = take_vertex(sol[x], x);
  }
  return sol;
}
