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
	struct T{
		int val; // TODO initial value
		int lazy;
		T() {}
		T(T a, T b){ val=max(a.val, b.val); }
		void apply(int l){
			// TODO
		}
	};
	vector<T> s; int n;
	Tree(int n) : s(2*n), n(n) {}
	void push(int x){ // x ∈ [n..2n[
		down(i,31^__builtin_clz(x)){
			let y=x>>(i+1);
			rep(c, y*2, y*2+2) s[c].apply(s[y].lazy);
			s[y].lazy=0; // TODO unit value
		}
	}
	void merge(int x){
		while (x>>=1) {
			assert(s[x].lazy==Lazy::none);
			s[x] = T(s[x*2], s[x*2+1]);
		}
	} // x ∈ [n..2n[

	void build() { down(p, n) s[p] = f(s[p*2], s[p*2+1]); }
	void update(int x, T val) {
		x+=n; push(x); s[x].val = val; merge(x);
	}
	T query(int l, int r) {
		assert(l<r); l+=n; r+=n;
		push(l); push(r-1);
		if(l+1==r) return s[l];
		T x = s[l++], y = s[--r];
		for(; l<r; l>>=1, r>>=1){
			if (l&1) x = f(x, s[l++]);
			if (r&1) y = f(s[--r], y);
		}
		return f(x, y);
	}

	void update(int l, int r, T lazy) {
		l+=n; r+=n;
		let u=l, v=r-1;
		push(u); push(v);
		for(; l<r; l>>=1, r>>=1){
			if(l&1) s[l++].apply(val);
			if(r&1) s[--r].apply(val);
		}
		push(u); push(v);
		merge(u); merge(v);
	}
};
