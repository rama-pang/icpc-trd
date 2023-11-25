/**
 * Author: rama_pang
 * Source: https://judge.yosupo.jp/submission/66608
 * Description: Finds a dominator tree of digraph, given a root node. 
 * \texttt{outside\_dom[i]} is the immediate dominator of node $i$, 
 * or -1 if it doesn't exist (or $i$ is root).
 * A node $d$ dominates $u$ iff you must visit $d$ to go to $u$ from root.
 * Time: O(V + E)
 * Status: Tested on https://judge.yosupo.jp/problem/dominatortree 
 * and https://tlx.toki.id/problems/inc-2023/I
 */

struct dominator_tree {
  int n, t;
  vector<int> arr, par, rev, sdom, dom, dsu, label;
  vector<vector<int>> g, rg, bucket;
  dominator_tree(int n) : n(n), t(0) {
    arr = par = rev = sdom = dom = vector<int>(n, -1);
    dsu = label = vector<int>(n, 0);
    g = rg = bucket = vector<vector<int>>(n);
  }
  void add_edge(int u, int v) { g[u].push_back(v); }
  void dfs(int u) {
    arr[u] = label[t] = sdom[t] = dsu[t] = t;
    rev[t] = u;
    t++;
    for (auto w : g[u]) {
      if (arr[w] == -1) {
        dfs(w);
        par[arr[w]] = arr[u];
      }
      rg[arr[w]].push_back(arr[u]);
    }
  }
  int find(int u, int x = 0) {
    if (u == dsu[u]) return x ? -1 : u;
    int v = find(dsu[u], x + 1);
    if (v < 0) return u;
    if (sdom[label[dsu[u]]] < sdom[label[u]]) label[u] = label[dsu[u]];
    dsu[u] = v;
    return x ? v : label[u];
  }
  vector<int> run(int root) {
    dfs(root);
    iota(all(dom), 0);
    down(i, t) {
      for (auto w : rg[i]) sdom[i] = min(sdom[i], sdom[find(w)]);
      if (i) bucket[sdom[i]].push_back(i);
      for (auto w : bucket[i]) {
        int v = find(w);
        dom[w] = sdom[v] == sdom[w] ? sdom[w] : v;
      }
      if (i > 1) dsu[i] = par[i];
    }
    rep(i, 1, t) {
      if (dom[i] != sdom[i]) dom[i] = dom[dom[i]];
    }
    vector<int> outside_dom(n, -1);
    rep(i, 1, t) outside_dom[rev[i]] = rev[dom[i]];
    return outside_dom;
  }
};
