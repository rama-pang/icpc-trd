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

struct treeDecomp { bool valid; vi par; vector<vi> bags; };
treeDecomp tree_decomposition(int n, vector<pii> edges) {
  vector<set<int>> adj(n);
  for (auto [u, v] : edges) {
    adj[u].insert(v);
    adj[v].insert(u);
  }
  treeDecomp ret;
  ret.valid = false;
  ret.par.resize(n, -1);
  ret.bags.resize(n);
  queue<int> que;
  rep(i, 0, n) if (sz(adj[i]) <= 2) que.push(i);
  auto rem_edge = [&](int u, int v) {
    adj[u].erase(adj[u].find(v));
    adj[v].erase(adj[v].find(u));
  };
  int piv = 0;
  vi ord(n, -1);
  vector<pii> pcand(n, pii(-1, -1));
  while (sz(que)) {
    int x = que.front();
    que.pop();
    if (ord[x] != -1) continue;
    ret.bags[x].push_back(x);
    ord[x] = piv++;
    if (sz(adj[x]) == 1) {
      int y = *adj[x].begin();
      rem_edge(x, y);
      ret.bags[x].push_back(y);
      if (sz(adj[y]) <= 2) que.push(y);
      pcand[x] = pii(y, y);
    }
    if (sz(adj[x]) == 2) {
      int u = *adj[x].begin();
      int v = *adj[x].rbegin();
      rem_edge(x, u);
      rem_edge(x, v);
      adj[u].insert(v);
      adj[v].insert(u);
      ret.bags[x].push_back(u);
      ret.bags[x].push_back(v);
      if (sz(adj[u]) <= 2) que.push(u);
      if (sz(adj[v]) <= 2) que.push(v);
      pcand[x] = pii(u, v);
    }
  }
  if (piv != n) return ret;
  ret.valid = true;
  int root = -1;
  rep(i, 0, n) {
    auto [x, y] = pcand[i];
    if (x == -1) {
      (root != -1) ? (ret.par[i] = root) : (root = i);
    } else {
      ret.par[i] = (ord[x] < ord[y]) ? x : y;
    }
  }
  return ret;
}