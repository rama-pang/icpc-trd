/**
 * Author: Lucian Bicsi
 * Date: 2017-10-31
 * License: CC0
 * Source: folklore
 * Description: Zero-indexed max-tree. Bounds are inclusive to the left and exclusive to the right. Can be changed by modifying $T$, $f$ and unit.
 * Time: O(\log N)
 * Status: ?
 */
#pragma once

struct Tree {
  struct T { Mod val; int cnt; }; // data type
  struct L { Mod mmul, madd; };  // lazy type
  static inline const T tneut = {0, 0};  // neutral elements
  static inline const L lneut = {1, 0};

  T op(T lft, T rgt) {  // Combine data
    return {lft.val + rgt.val, lft.cnt + rgt.cnt}; }
  T mapping(L upd, T cur) {  // Apply lazy to data
    return {cur.val * upd.mmul + cur.cnt * upd.madd, cur.cnt}; }
  L compose(L upd, L cur) {  // Compose lazy
    return L{cur.mmul * upd.mmul, cur.madd * upd.mmul + upd.madd }; }

  int n;
  vector<T> val;
  vector<L> lazy;

  Tree(int n) : val(2 * n, tneut), lazy(2 * n, lneut), n(n) {}
  void apply(int i, L upd) {
    val[i] = mapping(upd, val[i]);
    lazy[i] = compose(upd, lazy[i]);
  }
  void push(int x) {  // x ∈ [n..2n)
    down(i, 31 ^ __builtin_clz(x)) {
      let y = x >> (i + 1);
      rep(c, y * 2, y * 2 + 2) apply(c, lazy[y]);
      lazy[y] = lneut;
    }
  }
  void merge(int x) {
    while (x >>= 1) {
      assert(lazy[x] == lneut); val[x] = op(val[x * 2], val[x * 2 + 1]);
    }
  }  // x ∈ [n..2n)

  void build() { down(p, n) val[p] = op(val[p * 2], val[p * 2 + 1]); }
  void update(int x, T v) { x += n; push(x); val[x] = v; merge(x); }
  T query(int l, int r) {  // query [l, r)
    assert(l < r); l += n; r += n; push(l); push(r - 1);
    if (l + 1 == r) return val[l];
    T x = val[l++], y = val[--r];
    for (; l < r; l >>= 1, r >>= 1) {
      if (l & 1) x = op(x, val[l++]);
      if (r & 1) y = op(val[--r], y);
    }
    return op(x, y);
  }
  void update(int l, int r, L upd) {  // update [l, r)
    l += n; r += n; let u = l, v = r - 1; push(u); push(v);
    for (; l < r; l >>= 1, r >>= 1) {
      if (l & 1) apply(l++, upd);
      if (r & 1) apply(--r, upd);
    }
    push(u); push(v); merge(u); merge(v);
  }
};
