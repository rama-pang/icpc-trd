/**
 * Author: Lucian Bicsi
 * Date: 2018-02-14
 * License: CC0
 * Source: Chinese material
 * Description: Generates the $p$'th term of an $n$-order
 * linear recurrence $S[i] = \sum_j S[i-j-1]tr[j]$,
 * given $S[0 \ldots \ge n-1]$ and $tr[0 \ldots n-1]$.
 * Faster than matrix multiplication.
 * Useful together with Berlekamp--Massey.
 * $p$ is 0-indexed, if $p < n$ then return $S[p]$.
 * Usage: linearRec({0, 1}, {1, 1}, p) // p'th Fibonacci number
 * Time: O(n^2 \log p)
 * Status: bruteforce-tested mod 5 for n <= 5, tested on https://www.spoj.com/problems/ITRIX12E/
 *  tested on https://contest.ucup.ac/contest/1356/problem/7187
 */
#pragma once

#include "../number-theory/ModularArithmetic.h"
#include "NumberTheoreticTransform.h"

Mod linearRec(vm S, vm tr, ll p) {
	int n = sz(tr);
	assert(sz(S)==n);

#if not SLOW
	auto m=tr;
	for(auto& x: m) x=-x;
	reverse(all(m));
	m.push_back(1);
#endif

	auto combine = [&](vm a, vm b) {
#if SLOW
		vm res(n*2-1);
		rep(i,0,sz(a)) rep(j,0,sz(b))
			res[i + j] += a[i] * b[j];
		while(sz(res)>n){
			rep(j,0,n) res.end()[-j-2] += res.back() * tr[j];
			res.pop_back();
		}
		return res;
#else
		let r=conv(move(a), move(b));
		return polymod(r, m, polydiv(r, m));
#endif
	};

	vm pol{1}, e{0, 1};
	for (; p; p>>=1, e=combine(e, e)) if (p&1) pol = combine(move(pol), e);

	Mod res = 0;
	rep(i,0,sz(pol)) res += pol[i] * S[i];
	return res;
}
