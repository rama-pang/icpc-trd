/**
 * Author: Lucian Bicsi
 * Date: 2017-10-31
 * License: CC0
 * Source: Wikipedia
 * Description: Recovers any $n$-order linear recurrence relation from the first
 * $2n$ terms of the recurrence.
 * Useful for guessing linear recurrences after brute-forcing the first terms.
 * Should work on any field, but numerical stability for floats is not guaranteed.
 * Output will have size $\le n$.
 * Usage: berlekampMassey({0, 1, 1, 3, 5, 11}) // {1, 2}
 * Time: O(N^2)
 * Status: bruteforce-tested mod 5 for n <= 5 and all s
 */
#pragma once

#include "../number-theory/ModularArithmetic.h"

vector<Mod> berlekampMassey(vector<Mod> s) {
	int n = sz(s), L = 0, m = 0;
	vector<Mod> C(n), B(n), T;
	C[0] = B[0] = 1;

	Mod b = 1;
	rep(i,0,n) { ++m;
		Mod d = s[i];
		rep(j,1,L+1) d += C[j] * s[i - j];
		if (d==0) continue;
		T = C; Mod coef = d/b;
		rep(j,m,n) C[j] -= coef * B[j - m];
		if (2 * L > i) continue;
		L = i + 1 - L; B = T; b = d; m = 0;
	}

	C.resize(L + 1); C.erase(C.begin());
	for (Mod& x : C) x = -x;
	return C;
}
