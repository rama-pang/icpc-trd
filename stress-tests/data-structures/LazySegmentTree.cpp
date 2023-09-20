#include "../utilities/template.h"

#include "../../content/data-structures/LazySegmentTree.h"

volatile int res;
int main() {
	int N = 10;
	vi v(N);
	iota(all(v), 0);
	mt19937 engine;
	shuffle(all(v), engine);
	Node* tr = new Node(v,0,N);
	rep(i,0,N) rep(j,0,N) if (i <= j) {
		int ma = -inf;
		rep(k,i,j) ma = max(ma, v[k]);
		assert(ma == tr->query(i,j));
	}
	rep(it,0,1000000) {
		int i = uniform_int_distribution(0, N)(engine), j=uniform_int_distribution(0, N)(engine);
		if (i > j) swap(i, j);
		int x = uniform_int_distribution(-5, 4)(engine);

		int r = uniform_int_distribution(0, 99)(engine);
		if (r < 30) {
			::res = tr->query(i, j);
			int ma = -inf;
			rep(k,i,j) ma = max(ma, v[k]);
			assert(ma == ::res);
		}
		else if (r < 70) {
			tr->add(i, j, x);
			rep(k,i,j) v[k] += x;
		}
		else {
			tr->set(i, j, x);
			rep(k,i,j) v[k] = x;
		}
	}
	cout<<"Tests passed!"<<endl;
}
