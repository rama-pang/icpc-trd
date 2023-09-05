/**
 * Author: Lukas Polacek
 * Date: 2009-09-28
 * License: CC0
 * Source: folklore
 * Description: Operators for modular arithmetic. You need to set {\tt mod} to
 * some number first and then you can use the structure.
 */
#pragma once

// not yet tested!

#include "euclid.h"

const int mod = 17; // change to something else
struct Mod {
	int x;
	Mod(int xx=0) : x(xx%mod) { if(x<0) x+=mod; }
	void operator+=(Mod b) { if((x+=b.x)>=mod) x-=mod; }
	void operator-=(Mod b) { if((x-=b.x)<0) x+=mod; }
	void operator*=(Mod b) { x=int((x * b.x) % mod); }
		
	[[nodiscard]] Mod pow(auto p) const {
		assert(p>=0);
		Mod a=*this;
		Mod ans = 1; for (; p; p >>= 1, a *= a) if (p&1) ans *= a;
		return ans;
	}

	[[nodiscard]] Mod inv() {
		ll z, y, g = euclid(x, mod, z, y);
		assert(g == 1); return z;
	}
	void operator/=(Mod b) { *this *= b.inv(); }

#define A(O) [[nodiscard]] friend Mod operator O(Mod a, Mod b) { a O##= b; return a; }
	A(+) A(-) A(*) A(/)
#undef A

#define C(O) [[nodiscard]] bool operator O(Mod b) const { return x O b.x; }
	C(==) C(!=) C(<) C(>) C(<=) C(>=)
#undef C
};
