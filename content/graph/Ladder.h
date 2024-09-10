/**
 * Author: user202729 
 * Date: 2023-09-30
 * License: CC0
 * Description: Data structure for computing n-th ancestor in $O(1)$ operation per query.
 * Time: $O(N \log N + Q)$
 * Status: tested at https://cpc.compfest.id/contests/sandbox-scpc/problems/I
 */
#pragma once

struct Ladder{
	vector<array<int, 20>> jump;  // set this to be large enough
	vi ladder, li;

	Ladder(vi const& par, int root): jump(sz(par)), li(sz(par), -1) {
		assert(par[root]<0);

		vector<vi> add(sz(par));
		rep(i, 0, sz(add)){
			if(par[i]>=0) add[par[i]].push_back(i);
		}

		vi md(sz(add)), dc(sz(add), -1); // maxDepthBelow, deepestChild
		YComb([&](auto dfs, int i)->int{
			jump[i][0]=par[i];
			rep(l, 1, sz(jump[i])){
				let t=jump[i][l-1];
				jump[i][l]= t<0 ? -1: jump[t][l-1];
			}
			for(auto child: add[i]){
				let t=dfs(child)+1;
				if(t>md[i]) md[i]=t, dc[i]=child;
			}
			return md[i];
		})(root);

		ladder.reserve(sz(par)*2);
		YComb([&](auto dfs, int i)->void{
			int j=i;
			down(_, md[i]+1){
				ladder.push_back(j);
				if(j>=0) j=par[j];
			}
			reverse(ladder.end()-md[i]-1, ladder.end());
			li[i]=sz(ladder)-1; j=i;
			while(dc[j]>=0)
				j=dc[j], li[j]=sz(ladder), ladder.push_back(j);
			j=i;
			while(j>=0){
				for(auto child: add[j]) if(child!=dc[j]) dfs(child);
				j=dc[j];
			}
		})(root);

		for(int x: li) assert(x>=0);
	}

	int doJump(int node, int count) const{
		assert(node>=0);
		if(count==0) return node;
		let l=31^__builtin_clz(count);
		node=jump[node][l];
		return node<0 ? -1: ladder[li[node]-count+(1<<l)];
	}
};

