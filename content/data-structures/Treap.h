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

vector<int> spare; struct Data{ static vector<Data> data; struct Node{
	int i=-1;
	static Node create(int val){
		Node result;
		if(spare.empty()) result.i=sz(data), data.push_back({}), data.back().val=val;
		else result.i=spare.back(), result->val=val, spare.pop_back();
		return result;
	}
	explicit operator bool(){return i>=0;}
	Data* operator->(){return &data[i];}
#define n (*this)
	int cnt(){return n ? n->c: 0;}
	void pull(){n->c=n->l.cnt()+n->r.cnt()+1;}
	void push(){}
	pair<Node, Node> splitBySize(int k){ // left tree has k nodes
		if(!n) return {};
		push();
		if(n->l.cnt()>=k){ // "n->val >= k" for lower_bound(k) (<k in first, >=k in second)
			auto pa=n->l.splitBySize(k);
			n->l=pa.second;
			pull();
			return {pa.first, n};
		}else{
			auto pa=n->r.splitBySize(k-n->l.cnt()-1); // and just "k"
			n->r=pa.first;
			pull();
			return {n, pa.second};
		}
	}
	Node merge(Node r){
		if(!n) return r;
		if(!r) return n;
		n.push(), r.push();
		if(n->y>r->y){
			n->r=n->r.merge(r);
			n.pull();
			return n;
		}else{
			r->l=n.merge(r->l);
			r.pull();
			return r;
		}
	}
#undef n
};
	Node l{}, r{};
	int val, y=int(engine()), c=1; // val: value stored, y: priority, c: count node in subtree
};
vector<Data> Data::data; using Node=Data::Node;

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
