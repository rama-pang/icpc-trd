/**
 * Author: user202729
 * Date: 2023-10-09
 * License: CC0
 * Source: folklore
 * Status: not tested very well
 * Description: Operators for modular arithmetic. You need to set {\tt mod} to
 * some number first and then you can use the structure.
 */
#pragma once

#include "euclid.h"

struct Mod {
	int x;
	Mod(int y=0) : x(y%mod) { if(x<0) x+=mod; }
	//static Mod raw(int y){ Mod r; r.x=y; return r; }
	void operator+=(Mod b) { if((x+=b.x)>=mod) x-=mod; }
	void operator-=(Mod b) { if((x-=b.x)<0) x+=mod; }
	Mod operator-() const { return 0-*this; }
	void operator*=(Mod b) { x=int(ll(x) * b.x % mod); }
	explicit operator int() const{return x;}
	[[nodiscard]] Mod pow(auto p) const {
		assert(p>=0);
		Mod a=*this, ans = 1;
		for (; p; p >>= 1, a *= a) if (p&1) ans *= a;
		return ans;
	}
	[[nodiscard]] Mod inv() const {
		assert(x); return pow(mod-2);
		//ll z, y, g = euclid(mod, x, z, y); assert(g == 1); return int(y);
	}
	void operator/=(Mod b) { *this *= b.inv(); }
	auto operator<=>(const Mod&)const=default;
	friend auto& operator<<(ostream& s, Mod x){
		return s<<x.x-mod*(x>mod/2)<<'_';
	}
#define A(O) [[nodiscard]] friend Mod operator O(Mod a, Mod b) { a O##= b; return a; }
	A(+) A(-) A(*) A(/)
#undef A
};
