/**
 * Author: koosaga
 * Description: Given a undirected graph \((V, E)\), decompose into tree if
 * treewidth \(\leq 2\), or return false otherwise. The decomposition satisfies:
 * \(\bigcup_i \texttt{bags[i]} = [V]\), 
 * \(\forall u, \{x | u \in \texttt{bags[x]}\}\) is a connected subtree,
 * \(\forall (u, v) \in E \exists x, u, v \in \texttt{bags[x]}\),
 * \(|\texttt{bags[x]}|\leq\) treewidth + 1 = 3.
 * Time: O(M \log N)
 */

struct treeDecomp {
  bool valid;
  vector<int> par;
  vector<vector<int>> bags;
};

treeDecomp tree_decomposition(int n, vector<pii> edges) {
  vector<set<int>> gph(n);
  for (auto &[u, v] : edges) {
    gph[u].insert(v);
    gph[v].insert(u);
  }
  treeDecomp ret;
  ret.valid = false;
  ret.par.resize(n, -1);
  ret.bags.resize(n);
  queue<int> que;
  rep(i, 0, n) {
    if (sz(gph[i]) <= 2) que.push(i);
  }
  auto rem_edge = [&](int u, int v) {
    gph[u].erase(gph[u].find(v));
    gph[v].erase(gph[v].find(u));
  };
  int piv = 0;
  vector<int> ord(n, -1);
  vector<pii> pcand(n, pii(-1, -1));
  while (sz(que)) {
    int x = que.front();
    que.pop();
    if (ord[x] != -1) continue;
    ret.bags[x].push_back(x);
    ord[x] = piv++;
    if (sz(gph[x]) == 1) {
      int y = *gph[x].begin();
      rem_edge(x, y);
      ret.bags[x].push_back(y);
      if (sz(gph[y]) <= 2) que.push(y);
      pcand[x] = pii(y, y);
    }
    if (sz(gph[x]) == 2) {
      int u = *gph[x].begin();
      int v = *gph[x].rbegin();
      rem_edge(x, u);
      rem_edge(x, v);
      gph[u].insert(v);
      gph[v].insert(u);
      ret.bags[x].push_back(u);
      ret.bags[x].push_back(v);
      if (sz(gph[u]) <= 2) que.push(u);
      if (sz(gph[v]) <= 2) que.push(v);
      pcand[x] = pii(u, v);
    }
  }
  if (piv != n) return ret;
  ret.valid = true;
  int root = -1;
  for (int i = 0; i < n; i++) {
    auto [x, y] = pcand[i];
    if (x == -1) {
      (root != -1) ? (ret.par[i] = root) : (root = i);
    } else {
      ret.par[i] = (ord[x] < ord[y]) ? x : y;
    }
  }
  return ret;
}
