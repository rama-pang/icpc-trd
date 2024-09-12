/**
 * Author: Lucian Bicsi
 * Date: 2017-10-31
 * License: CC0
 * Source: folklore
 * Description: Zero-indexed max-tree. Bounds are inclusive to the left and exclusive to the right. Can be changed by modifying $T$, $f$ and unit. See LazySegmentTree on example usage.
 * Time: O(\log N)
 * Status: Same as LazySegmentTree.h
 */
#pragma once

template<class T, class L, auto op, auto mapping, auto compose>
struct Tree {
  int n;
  vector<T> val;
  vector<L> lazy;
  Tree(int n) : n(n), val(2 * n), lazy(2 * n) {}
  void apply(int i, L upd) {
    val[i] = mapping(upd, val[i]);
    lazy[i] = compose(upd, lazy[i]);
  }
  void push(int x) {  // x ∈ [n..2n)
    down(i, 31 ^ __builtin_clz(x)) {
      let y = x >> (i + 1);
      rep(c, y * 2, y * 2 + 2) apply(c, lazy[y]);
      lazy[y] = {};
    }
  }
  void merge(int x) {
    while (x >>= 1) {
      assert(lazy[x] == L{});
      val[x] = op(val[x * 2], val[x * 2 + 1]);
    }
  }  // x ∈ [n..2n)
  void build() { down(x, n) val[x] = op(val[x * 2], val[x * 2 + 1]); }
  void update(int x, T v) { x += n; push(x); val[x] = v; merge(x); }
  T query(int l, int r) {  // query [l, r)
    assert(0 <= l && l < r && r <= n);
    l += n; r += n; push(l); push(r - 1);
    if (l + 1 == r) return val[l];
    T x = val[l++], y = val[--r];
    for (; l < r; l >>= 1, r >>= 1) {
      if (l & 1) x = op(x, val[l++]);
      if (r & 1) y = op(val[--r], y);
    }
    return op(x, y);
  }
  void update(int l, int r, L upd) {  // update [l, r)
    assert(0 <= l && l < r && r <= n);
    l += n; r += n; let u = l, v = r - 1; push(u); push(v);
    for (; l < r; l >>= 1, r >>= 1) {
      if (l & 1) apply(l++, upd);
      if (r & 1) apply(--r, upd);
    }
    push(u); push(v); merge(u); merge(v);
  }
};
