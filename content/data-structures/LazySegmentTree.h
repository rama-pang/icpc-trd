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
 * Status: stress-tested a bit, https://judge.yosupo.jp/submission/234225
 */
#pragma once

#include "../various/BumpAllocator.h"

template<class T, class L, auto op, auto mapping, auto compose>
struct Node {
  int lo, hi;  // current range is [lo, hi)
  unique_ptr<Node> l, r;
  T val {};
  L lazy {};
  Node(int lo, int hi) : lo(lo), hi(hi) {}  // Large interval of T {}
  Node(vector<T>& v, int lo, int hi) : lo(lo), hi(hi) {
    if (lo + 1 < hi) {
      int mid = lo + (hi - lo) / 2;
      l.reset(new Node(v, lo, mid));
      r.reset(new Node(v, mid, hi));
      val = op(l->val, r->val);
    } else val = v[lo];
  }
  void apply(L upd) {val = mapping(upd, val), lazy = compose(upd, lazy); }
  T query(int lft, int rgt) {  // query [lft, rgt)
    if (rgt <= lo || hi <= lft) return {};
    if (lft <= lo && hi <= rgt) return val;
    push();
    return op(l->query(lft, rgt), r->query(lft, rgt));
  }
  void upd(int lft, int rgt, L upd) { // update [lft, rgt)
    if (rgt <= lo || hi <= lft) return;
    if (lft <= lo && hi <= rgt) return apply(upd);
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
    l->apply(lazy), r->apply(lazy);
    lazy = {}, val = op(l->query(lo, hi), r->query(lo, hi));
  }
};
struct T { Mod val=0; int cnt=0; }; // data type
struct L { Mod mmul=1, madd=0; };  // lazy type
T op(T lft, T rgt) {  // Combine data
  return {lft.val + rgt.val, lft.cnt + rgt.cnt}; }
T mapping(L upd, T cur) {  // Apply lazy to data
  return {cur.val * upd.mmul + cur.cnt * upd.madd, cur.cnt}; }
L compose(L upd, L cur) {  // Compose lazy
  return L{cur.mmul * upd.mmul, cur.madd * upd.mmul + upd.madd }; }
using Tree = Node<T, L, op, mapping, compose>;
