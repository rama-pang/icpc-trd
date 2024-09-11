/**
 * Author: Lucian Bicsi, Simon Lindholm
 * Date: 2017-10-31
 * License: CC0
 * Description: Given $f$ and $N$, finds the smallest fraction $p/q \in [0, 1]$
 * such that $f(p/q)$ is true, and $p, q \le N$.
 * You may want to throw an exception from $f$ if it finds an exact solution,
 * in which case $N$ can be removed.
 * Usage: fracBS([](Frac f) { return f.p>=3*f.q; }, 10); // {1,3}
 * Time: O(\log(N))
 * Status: stress-tested for n <= 300
 */

struct Frac { ll p, q; };
Frac fracBS(auto f, ll n) {
	bool dir = 1, a = 1, b = 1;
	Frac lo{0, 1}, hi{1, 1}; // Set hi to 1/0 to search (0, n]
	if (f(lo)) return lo;
	assert(f(hi));
	while (a or b) {
		ll adv = 0, step = 1; // move hi if dir, else lo
		for (int si = 0; step; step = (step * 2) >> si) {
			adv += step;
			Frac mid{lo.p * adv + hi.p, lo.q * adv + hi.q};
			if (abs(mid.p) > n or mid.q > n or dir != f(mid)) {
				adv -= step; si = 2;
			}
		}
		hi.p += lo.p * adv;
		hi.q += lo.q * adv;
		dir = !dir;
		swap(lo, hi);
		a = b; b = !!adv;
	}
	return dir ? hi : lo;
}