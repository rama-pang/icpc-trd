#include "../utilities/template.h"

let mod=998244353;
#include "../../content/numerical/NumberTheoreticTransform.h"

vector<Mod> simpleConv(vector<Mod> a, vector<Mod> b) {
	int s = sz(a) + sz(b) - 1;
	if (a.empty() || b.empty()) return {};
	vector<Mod> c(s);
	rep(i,0,sz(a)) rep(j,0,sz(b))
		c[i+j] +=  a[i] * b[j];
	for(auto &x: c) if (x < 0) x += mod;
	return c;
}

int ra() {
    static unsigned X;
    X *= 123671231;
    X += 1238713;
    X ^= 1237618;
    return (X >> 1);
}

int main() {
	Mod res = 0, res2 = 0;
	int ind = 0, ind2 = 0;
	vector<Mod> a, b;
	rep(it,0,6000) {
		a.resize(ra() % 10);
		b.resize(ra() % 10);
		for(auto &x: a) x = (ra() % 100 - 50+mod)%mod;
		for(auto &x: b) x = (ra() % 100 - 50+mod)%mod;

		if(not a.empty() and a[0]!=0){
			let f=simpleConv(a, polyinv(a, ceillog2(sz(a))));
			rep(i, 0, ceillog2(sz(a))) assert(f[i]==(i==0));
		}

		for(auto &x: simpleConv(a, b)) res += x * ind++ ;
		for(auto &x: conv(a, b)) res2 += x * ind2++ ;
		a.resize(16);
        vector<Mod> a2 = a;
        ntt(a2);
        rep(k, 0, sz(a2)) {
            Mod sum = 0;
            rep(x, 0, sz(a2)) { sum = (sum + a[x] * root.pow(k * x * ll(mod - 1) / sz(a))) ; }
            assert(sum == a2[k]);
        }
	}
	assert(res==res2);
	cout<<"Tests passed!"<<endl;
}
