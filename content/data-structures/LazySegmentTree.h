/**
 * Author: Simon Lindholm
 * Date: 2016-10-08
 * License: CC0
 * Source: IvanRenison
 * Description: Segment tree with ability to add or set values of large intervals, and compute max of intervals.
 * Can be changed to other things.
 * Use with a bump allocator for better performance, and SmallPtr or implicit indices to save memory.
 * Time: O(\log N).
 * Usage: Node* tr = new Node(v, 0, sz(v));
 * Status: stress-tested a bit, https://judge.yosupo.jp/submission/186354
 */
#pragma once

#include "../various/BumpAllocator.h"

struct Node {
  using T = int;  // data type
  struct L { int mmul, madd; };  // lazy type
  static inline const T tneut = 0;  // neutral elements
  static inline const L lneut = {1, 0};

  T op(T lft, T rgt) { return lft + rgt; }  // Combine data
  T mapping(L upd, T cur) {                 // Apply lazy to data
    return cur * upd.mmul + (hi - lo) * upd.madd; }
  L compose(L upd, L cur) {  // Compose lazy
    return L{cur.mmul * upd.mmul, cur.madd * upd.mmul + upd.madd }; }

  int lo, hi;  // current range is [lo, hi)
  unique_ptr<Node> l, r;
  T val = tneut;
  L lazy = lneut;

  Node(int lo, int hi) : lo(lo), hi(hi) {}  // Large interval of tneut
  Node(vector<T>& v, int lo, int hi) : lo(lo), hi(hi) {
    if (lo + 1 < hi) {
      int mid = lo + (hi - lo) / 2;
      l.reset(new Node(v, lo, mid));
      r.reset(new Node(v, mid, hi));
      val = op(l->val, r->val);
    } else val = v[lo];
  }
  T query(int lft, int rgt) {  // query [lft, rgt)
    if (rgt <= lo || hi <= lft) return tneut;
    if (lft <= lo && hi <= rgt) return mapping(lazy, val);
    push();
    return op(l->query(lft, rgt), r->query(lft, rgt));
  }
  void upd(int lft, int rgt, L upd) { // update [lft, rgt)
    if (rgt <= lo || hi <= lft) return;
    if (lft <= lo && hi <= rgt) lazy = compose(upd, lazy);
    else {
      push(), l->upd(lft, rgt, upd), r->upd(lft, rgt, upd);
      val = op(l->query(lo, hi), r->query(lo, hi));
    }
  }
  void push() {
    if (!l) {
      int mid = lo + (hi - lo) / 2;
      l.reset(new Node(lo, mid));
      r.reset(new Node(mid, hi));
    }
    l->lazy = compose(lazy, l->lazy);
    r->lazy = compose(lazy, r->lazy);
    lazy = lneut;
    val = op(l->query(lo, hi), r->query(lo, hi));
  }
};
