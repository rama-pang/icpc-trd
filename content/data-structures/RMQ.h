/**
 * Author: Johan Sannemo, pajenegod
 * Date: 2015-02-06
 * License: CC0
 * Source: Folklore
 * Description: Range Minimum Queries on an array. Returns
 * min(V[a], V[a + 1], ... V[b - 1]) in constant time.
 * Usage:
 *  RMQ rmq(values);
 *  rmq(inclusive, exclusive);
 * Time: $O(|V| \log |V| + Q)$
 * Status: stress-tested
 */
#pragma once

template<class T>
struct RMQ {
	vector<vector<T>> jump;
	RMQ(vector<T> V) : jump{move(V)} {
		let l=sz(jump[0]);
		for (int pw = 1, k = 1; pw * 2 <= l; pw *= 2, ++k) {
			jump.emplace_back(l - pw * 2 + 1);
			rep(j,0,sz(jump[k]))
				jump[k][j] = min(jump[k - 1][j], jump[k - 1][j + pw]);
		}
	}
	T operator()(int a, int b) const {
		assert(a < b); // or return inf if a == b
		int dep = 31 ^ __builtin_clz(b - a);
		return min(jump[dep][a], jump[dep][b - (1 << dep)]);
	}
};
