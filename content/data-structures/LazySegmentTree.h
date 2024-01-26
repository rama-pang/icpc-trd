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

const int inf = 1e9;
struct Node {
	using T = int; // data type
	struct L { int mset, madd; }; // lazy type
	const T tneut = -inf;     // neutral elements
	const L lneut = {inf, 0};
	T f (T a, T b) { return max(a, b); } // (any associative fn)
	T apply (T a, L b) {
		return b.mset != inf ? b.mset + b.madd : a + b.madd;
	} // Apply lazy to data
	L comb(L a, L b) {
		if (b.mset != inf) return b;
		return {a.mset, a.madd + b.madd};
	} // Combine lazy (a is old, b is new)

	Node *l = 0, *r = 0;
	int lo, hi; T val = tneut; L lazy = lneut;
	Node(int lo,int hi):lo(lo),hi(hi){}//Large interval of tneut
	Node(vector<T>& v, int lo, int hi) : lo(lo), hi(hi) {
		if (lo + 1 < hi) {
			int mid = lo + (hi - lo)/2;
			l = new Node(v, lo, mid); r = new Node(v, mid, hi);
			val = f(l->val, r->val);
		}
		else val = v[lo];
	}
	T query(int Le, int Ri) {
		if (Ri <= lo || hi <= Le) return tneut;
		if (Le <= lo && hi <= Ri) return apply(val, lazy);
		push();
		return f(l->query(Le, Ri), r->query(Le, Ri));
	}
	void upd(int Le, int Ri, L x) {
		if (Ri <= lo || hi <= Le) return;
		if (Le <= lo && hi <= Ri) lazy = comb(lazy, x);
		else {
			push(), l->upd(Le, Ri, x), r->upd(Le, Ri, x);
			val = f(l->query(lo, hi), r->query(lo, hi));
		}
	}
	void set(int Le, int Ri, int x) { upd(Le, Ri, {x, 0}); }
	void add(int Le, int Ri, int x) { upd(Le, Ri, {inf, x}); }
	void push() {
		if (!l) {
			int mid = lo + (hi - lo)/2;
			l = new Node(lo, mid), r = new Node(mid, hi);
		}
		l->lazy = comb(l->lazy, lazy);
		r->lazy = comb(r->lazy, lazy);
		lazy = lneut;
		val = f(l->query(lo, hi), r->query(lo, hi));
	}
};
