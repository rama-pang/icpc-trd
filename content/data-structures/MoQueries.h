/**
 * Author: Simon Lindholm
 * Date: 2019-12-28
 * License: CC0
 * Source: https://github.com/hoke-t/tamu-kactl/blob/master/content/data-structures/MoQueries.h
 * Description: Answer interval or tree path queries by finding an approximate TSP through the queries,
 * and moving from one query to the next by adding/removing points at the ends.
 * If values are on tree edges, change \texttt{step} to add/remove the edge $(a, c)$ and remove the initial \texttt{add} call (but keep \texttt{in}).
 * You should implement the following functions:
 * void add(int ind, int end) { ... } // add a[ind] (end = 0 (left) or 1 (right))
 * void del(int ind, int end) { ... } // remove a[ind]
 * int calc() { ... } // compute current answer
 * Time: O(N \sqrt Q)
 * Status: stress-tested
 */
#pragma once

template <class Add, class Del, class Calc>
vi mo(vector<pii> Q, Add add, Del del, Calc calc) {
  int L = 0, R = 0, blk = 350;  // ~N/sqrt(Q)
  vi s(sz(Q)), re = s;
#define K(x) pii(x.first / blk, x.second ^ -(x.first / blk & 1))
  iota(all(s), 0); sort(all(s), [&](int s, int t) { return K(Q[s]) < K(Q[t]); });
#undef K
  for (int qi : s) {
    pii q = Q[qi];
    while (L > q.first) add(--L, 0);
    while (R < q.second) add(R++, 1);
    while (L < q.first) del(L++, 0);
    while (R > q.second) del(--R, 1);
    re[qi] = calc();
  }
  return re;
}

template <class Add, class Del, class Calc>
vi moTree(vector<array<int, 2>> Q, vector<vi>& ed, int root, Add add, Del del, Calc calc) {
  int N = sz(ed), pos[2] = {}, blk = 350;  // ~N/sqrt(Q)
  vi s(sz(Q)), re = s, I(N), L(N), R(N), in(N), par(N);
  add(0, 0); in[0] = 1;
  auto dfs = [&](int x, int p, int dep, auto& f) -> void {
    par[x] = p; L[x] = N;
    if (dep) I[x] = N++;
    for (int y : ed[x]) if (y != p) f(y, x, !dep, f);
    if (!dep) I[x] = N++;
    R[x] = N;
  };
  dfs(root, -1, 0, dfs);
#define K(x) pii(I[x[0]] / blk, I[x[1]] ^ -(I[x[0]] / blk & 1))
  iota(all(s), 0); sort(all(s), [&](int s, int t) { return K(Q[s]) < K(Q[t]); });
#undef K
  for (int qi : s) rep(end, 0, 2) {
      int &a = pos[end], b = Q[qi][end], i = 0;
      auto step = [&](int c) {
        if (in[c]) { del(a, end); in[a] = 0; }
        else { add(c, end); in[c] = 1; }
        a = c; };
      while (!(L[b] <= L[a] && R[a] <= R[b])) I[i++] = b, b = par[b];
      while (a != b) step(par[a]);
      while (i--) step(I[i]);
      if (end) re[qi] = calc();
  }
  return re;
}
