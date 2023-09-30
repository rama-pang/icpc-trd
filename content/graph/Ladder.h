/**
 * Author: user202729 
 * Date: 2023-09-30
 * License: CC0
 * Description: Data structure for computing n-th ancestor in $O(1)$ operation per query.
 * Time: $O(N \log N + Q)$
 * Status: tested at https://cpc.compfest.id/contests/sandbox-scpc/submissions/4522
 */
#pragma once

struct Ladder{
	vector<array<int, 20>> jump;  // set this to be large enough
	vector<int> ladder, ladderIndex;

	Ladder(vector<int> const& par, int root): jump(sz(par)), ladderIndex(sz(par), -1) {
		assert(par[root]<0);

		vector<vector<int>> add(sz(par));
		rep(i, 0, sz(add)){
			if(par[i]>=0) add[par[i]].push_back(i);
		}

		vector<int> maxDepthBelow(sz(add)), deepestChild(sz(add), -1);
		YComb([&](auto dfs, int i)->int{
			jump[i][0]=par[i];
			rep(layer, 1, sz(jump[i])){
				jump[i][layer]=
					jump[i][layer-1]<0 ? -1:
					jump[jump[i][layer-1]][layer-1];
			}
			for(auto child: add[i]){
				let t=dfs(child)+1;
				if(t>maxDepthBelow[i]){
					maxDepthBelow[i]=t;
					deepestChild[i]=child;
				}
			}
			return maxDepthBelow[i];
		})(root);

		ladder.reserve(sz(par)*2);
		YComb([&](auto dfs, int i)->void{
			int j=i;
			let oldSize=sz(ladder);
			down(_, maxDepthBelow[i]+1){
				ladder.push_back(j);
				if(j>=0) j=par[j];
			}
			reverse(ladder.begin()+oldSize, ladder.end());
			assert(ladderIndex[i]<0);
			ladderIndex[i]=sz(ladder)-1;
			j=i;
			while(deepestChild[j]>=0){
				j=deepestChild[j];
				assert(ladderIndex[j]<0);
				ladderIndex[j]=sz(ladder);
				ladder.push_back(j);
			}
			j=i;
			while(j>=0){
				for(auto child: add[j]) if(child!=deepestChild[j]) dfs(child);
				j=deepestChild[j];
			}
		})(root);

		for(int x: ladderIndex) assert(x>=0);
	}

	int doJump(int node, int count) const{
		assert(node>=0);
		if(count==0) return node;
		let layer=31^__builtin_clz(count);
		count-=1<<layer;
		node=jump[node][layer];
		return node<0 ? -1: ladder[ladderIndex[node]-count];
	}
};

