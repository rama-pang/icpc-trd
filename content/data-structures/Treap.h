/**
 * Author: someone on Codeforces
 * Date: 2017-03-14
 * Source: folklore
 * Description: A short self-balancing tree. It acts as a
 *  sequential container with log-time splits/joins, and
 *  is easy to augment with additional data.
 * Time: $O(\log N)$
 * Status: stress-tested
 */
#pragma once

struct Node {
	int val, y=int(engine()), c = 1; // val: value stored, y: priority, c: count node in subtree
	Node *l = 0, *r = 0;
	void pull();
	void push();
};
int cnt(Node* n) { return n ? n->c : 0; }
void Node::pull() { c = cnt(l) + cnt(r) + 1; }
void each(Node* n, auto f) {
	if (n) { n->push(); each(n->l, f); f(n->val); each(n->r, f); }
}
pair<Node*, Node*> split(Node* n, int k) { // left tree has k nodes
	if (!n) return {};
	n->push();
	if (cnt(n->l) >= k) { // "n->val >= k" for lower_bound(k) (<k in first, >=k in second)
		auto pa = split(n->l, k);
		n->l = pa.second;
		n->pull();
		return {pa.first, n};
	} else {
		auto pa = split(n->r, k - cnt(n->l) - 1); // and just "k"
		n->r = pa.first;
		n->pull();
		return {n, pa.second};
	}
}
Node* merge(Node* l, Node* r) {
	if (!l) return r;
	if (!r) return l;
	l->push(), r->push();
	if (l->y > r->y) {
		l->r = merge(l->r, r);
		l->pull();
		return l;
	} else {
		r->l = merge(l, r->l);
		r->pull();
		return r;
	}
}
Node* ins(Node* t, Node* n, int pos) {
	auto pa = split(t, pos);
	return merge(merge(pa.first, n), pa.second);
}
// Example application: move the range [l, r) to index k
void move(Node*& t, int l, int r, int k) {
	Node *a, *b, *c;
	tie(a,b) = split(t, l); tie(b,c) = split(b, r - l);
	if (k <= l) t = merge(ins(a, b, k), c);
	else t = merge(a, ins(c, b, k - r));
}
