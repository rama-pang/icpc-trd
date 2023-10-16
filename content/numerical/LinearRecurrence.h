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
 */
#pragma once

#include "../number-theory/ModularArithmetic.h"
#include "NumberTheoreticTransform.h"

#define FAST 1

Mod linearRec(vm S, vm tr, ll p) {
	int n = sz(tr);
	assert(sz(S)==n);

#if FAST
	auto m=tr;
	for(auto& x: m) x=-x;
	m.push_back(1);
#endif

	auto combine = [&](vm a, vm b) {
#if FAST
		let r=conv(move(a), move(b));
		return polymod(r, m, polydiv(r, m));
#else
		vm res(n * 2 + 1);
		rep(i,0,sz(a)) rep(j,0,sz(b))
			res[i + j] += a[i] * b[j];
		for (int i = 2 * n; i > n; --i) rep(j,0,n)
			res[i - 1 - j] += res[i] * tr[j];
		res.resize(n + 1);
		return res;
#endif
	};

	vm pol{1}, e{0, 1};
	for (++p; p; p>>=1, e=combine(e, e)) if (p&1) pol = combine(move(pol), e);

	Mod res = 0;
	rep(i,0,sz(pol)-1) res += pol[i + 1] * S[i];
	return res;
}
