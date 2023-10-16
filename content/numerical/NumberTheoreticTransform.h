/**
 * Author: chilli
 * Date: 2019-04-16
 * License: CC0
 * Source: based on KACTL's FFT
 * Description: ntt(a) computes $\hat f(k) = \sum_x a[x] g^{xk}$ for all $k$, where $g=\text{root}^{(mod-1)/N}$.
 * N must be a power of 2.
 * Useful for convolution modulo specific nice primes of the form $2^a b+1$,
 * where the convolution result has size at most $2^a$. For arbitrary modulo, see FFTMod.
   \texttt{conv(a, b) = c}, where $c[x] = \sum a[i]b[x-i]$.
   For manual convolution: NTT the inputs, multiply
   pointwise, divide by n, reverse(start+1, end), NTT back.
 * Inputs must be in [0, mod).
 * Time: O(N \log N)
 * Status: stress-tested, tested on https://judge.yosupo.jp/problem/inv_of_formal_power_series etc.
 */
#pragma once

#include "../number-theory/ModularArithmetic.h"

// let mod = (119 << 23) + 1; // = 998244353
const Mod root = 62;
// For p < 2^30 there is also e.g. 5 << 25, 7 << 26, 479 << 21
// and 483 << 21 (same root). The last two are > 10^9.
using vm=vector<Mod>;
void ntt(vm &a) {
	int n = sz(a), L = 31 ^ __builtin_clz(n);
	assert(n==1<<L);
	static vm rt(2, 1);
	for (static int k = 2, s = 2; k < n; k *= 2, s++) {
		rt.resize(n);
		Mod z[] = {1, root.pow(mod >> s)};
		rep(i,k,2*k) rt[i] = rt[i / 2] * z[i & 1];
	}
	vi rev(n);
	rep(i,0,n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
	rep(i,0,n) if (i < rev[i]) swap(a[i], a[rev[i]]);
	for (int k = 1; k < n; k *= 2)
		for (int i = 0; i < n; i += 2 * k) rep(j,0,k) {
			Mod z = rt[j + k] * a[i + j + k], &ai = a[i + j];
			a[i + j + k] = ai - z;
			ai += z;
		}
}
void intt(vm &a) {
	let inv = Mod(1)/sz(a);
	reverse(a.begin()+1, a.end());
	for(auto& x: a) x*=inv;
	ntt(a);
}
int ceillog2(int n){ return 31^__builtin_clz(n*2-1); }
vm conv(vm L, vm R) {
	if (L.empty() || R.empty()) return {};
	int s = sz(L) + sz(R) - 1, n = 1<<ceillog2(s);
	L.resize(n), R.resize(n);
	ntt(L), ntt(R);
	rep(i,0,n) L[i] *= R[i];
	intt(L);
	L.resize(s); return L;
}

vm polyinv(vm q, int d) { // get inverse series mod x^2^d. q must not be empty and q[0]!=0. Can set d=ceillog2(sz(q))
	if(d==0) return {1/q[0]};
	let m=1<<(d-1), n=m*2;
	q.resize(n);
	vm a(m+all(q)); q.resize(m);
	vm f=polyinv(q, d-1), b=conv(move(q), f);
	a=conv(move(a), f);
	a.resize(m);
	rep(i, 0, m) a[i]=(i==m-1 ? 0: -b[i+m])-a[i];
	a=conv(move(a), f);
	f.insert(f.end(), a.begin(), a.begin()+m);
	return f;
}

struct Polydiv{
	int m, n; // n: maximum size of a
	vm i;
	Polydiv(vm const& b, int n): m(sz(b)), n(n){
		assert(b.back()!=0);
		let d = n-m+1;
		if(d>0) i=polyinv({b.rbegin(), b.rbegin()+min(m,d)}, ceillog2(d));
	}
	vm operator()(vm const& a)const{
		assert(sz(a)<=n);
		let d = sz(a)-m+1;
		if(d<=0) return {};
		assert(a.back()!=0);
		vm q=conv({a.rbegin(), a.rbegin()+d}, {i.begin(), i.begin()+d});
		q.resize(d); reverse(all(q));
		return q;
	}
};
vm polydiv(vm const& a, vm const& b) {
	return Polydiv(b,sz(a))(a);
}
vm polymod(vm a, vm b, vm q) {
	b.pop_back();
	let n=sz(b);
	a.resize(n);
	if(n<sz(q)) q.resize(n);
	let t=conv(move(q), move(b));
	rep(i, 0, min(n, sz(t))) a[i]-=t[i];
	while(not a.empty() and a.back()==0) a.pop_back();
	return a;
}
