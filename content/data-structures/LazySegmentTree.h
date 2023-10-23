/**
 * Author: Simon Lindholm
 * Date: 2016-10-08
 * License: CC0
 * Source: me
 * Description: Segment tree with ability to add or set values of large intervals, and compute max of intervals.
 * Can be changed to other things.
 * Use with a bump allocator for better performance, and SmallPtr or implicit indices to save memory.
 * Note that the type of val must handle multiple values, and Op must be able to act on a collection.
 * Time: O(\log N).
 * Usage: Node* tr = new Node(v, 0, sz(v));
 * Status: stress-tested a bit
 */
#pragma once

#include "../various/BumpAllocator.h"

const int inf = 1e9;
struct Op { int set=inf, add=0; }; // in this example set is applied first, then add
Op const Identity {};
Op operator*(Op a, Op b){
	if(a.set==inf) return b.add+=a.add, b;
	return a;
}
int operator*(Op mod, int val){
	if(mod.set!=inf){val=mod.set;} return mod.add+val;
}
#define mergeVal max
let emptyVal=-inf;  // * identity of mergeVal
struct Node {
	Node *l = 0, *r = 0;
	int lo, hi;
	Op mod=Identity; int val = emptyVal;
	Node(int lo,int hi):lo(lo),hi(hi){} // Large empty interval
	Node(vi& v, int lo, int hi) : lo(lo), hi(hi) { // Initialize from segment of v
		if (lo + 1 < hi) {
			int mid = lo + (hi - lo)/2;
			l = new Node(v, lo, mid); r = new Node(v, mid, hi);
			val = mergeVal(l->val, r->val);
		} else val = v[lo]; // * set default value
	}
	int query(int L, int R) {
		if (R <= lo || hi <= L) return emptyVal;
		if (L <= lo && hi <= R) return val;
		push();
		return mergeVal(l->query(L, R), r->query(L, R));
	}
	void op(int L, int R, Op x) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) mod = x * mod, val = x * val;
		else {
			push(), l->op(L, R, x), r->op(L, R, x);
			val = mergeVal(l->val, r->val);
		}
	}
	void set(int L, int R, int x) {
		op(L, R, Op{.set=x, .add=0});
	}
	void add(int L, int R, int x) {
		op(L, R, Op{.set=inf, .add=x});
	}
	void push() {
		if (!l) {
			int mid = lo + (hi - lo)/2;
			l = new Node(lo, mid); r = new Node(mid, hi);
		}
		//if (mod != inf)
		l->op(lo,hi,mod), r->op(lo,hi,mod), mod = Identity;
	}
};
