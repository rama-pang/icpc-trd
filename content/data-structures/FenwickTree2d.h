/**
 * Author: Simon Lindholm
 * Date: 2017-05-11
 * License: CC0
 * Source: folklore
 * Description: Computes sums $a[i,j]$ for all $i<I$, $j<J$, and increases single elements $a[i,j]$.
 *  Requires that the elements to be updated are known in advance (call fakeUpdate() before init()).
 * Time: $O(\log^2 N)$. (Use persistent segment trees for $O(\log N)$.)
 * Status: stress-tested (except FT3 which is tested once at 1106-jak-regional/F_old.cpp but that one is TLE)
 */
#pragma once

#include "FenwickTree.h"

struct FT2 {
	vector<vi> ys; vector<FT> ft;
	FT2(int limx) : ys(limx) {} // 0 ≤ x < limx, use O(limx) memory
	void fakeUpdate(int x, int y) {
		for (; x < sz(ys); x |= x + 1) ys[x].push_back(y);
	}
	void init() {
		for (vi& v : ys) sort(all(v)), ft.push_back(sz(v));
	}
	int ind(int x, int y) {
		return int(lower_bound(all(ys[x]), y) - ys[x].begin()); }
	void update(int x, int y, ll dif) {
		for (; x < sz(ys); x |= x + 1)
			ft[x].update(ind(x, y), dif);
	}
	ll query(int x, int y) {
		ll sum = 0;
		for (; x; x &= x - 1)
			sum += ft[x-1].query(ind(x-1, y));
		return sum;
	}
};

struct FT3{ // also with x-coordinate compression
	vector<int> xs;FT2 f={0};
	void fakeUpdate1(int x){xs.push_back(x);}
	void init(){ sort(all(xs)),f={sz(xs)}; }
	void fakeUpdate2(int x,int y){ f.fakeUpdate(ind(x),y); }
	// then call ft.f.init();
	void update(int x,int y,int dif){ f.update(ind(x),y,dif); }
	int query(int x,int y){ return f.query(ind(x),y); }
	int ind(int x){ return int(lower_bound(all(xs),x)-xs.begin());}
};
