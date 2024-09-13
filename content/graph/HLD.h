/**
 * Author: Benjamin Qi, Oleksandr Kulkov, chilli
 * Date: 2020-01-12
 * License: CC0
 * Source: https://codeforces.com/blog/entry/53170, https://github.com/bqi343/USACO/blob/master/Implementations/content/graphs%20(12)/Trees%20(10)/HLD%20(10.3).h
 * Description: Decomposes a tree into vertex disjoint heavy paths and light
 * edges such that the path from any leaf to the root contains at most log(n)
 * light edges. VALS\_EDGES being true means that values are stored in the edges.
 * Time: O(\log n)
 * Status: stress-tested against old HLD
 */
#pragma once

template <bool VALS_EDGES> struct HLD {
	int n, tim = 0;
	vector<vi> adj;
	vi par, siz, dep, rts, pos;
	HLD(vector<vi> adj_) : n(sz(adj_)), adj(adj_), par(n, -1),
		siz(n, 1), dep(n), rts(n),pos(n) { dfsSz(0); dfsHld(0); }
	void dfsSz(int v) {
		if (par[v] >= 0) adj[v].erase(find(all(adj[v]), par[v]));
		for (int& u : adj[v]) {
			par[u] = v, dep[u] = dep[v] + 1;
			dfsSz(u), siz[v] += siz[u];
			if (siz[u] > siz[adj[v][0]]) swap(u, adj[v][0]); } }
	void dfsHld(int v) {
		pos[v] = tim++;
		for (int u : adj[v]) {
			rts[u] = (u == adj[v][0] ? rts[v] : u), dfsHld(u); } }
	void processPath(int u, int v, auto op) {
		for (; rts[u] != rts[v]; v = par[rts[v]]) {
			if (dep[rts[u]] > dep[rts[v]]) swap(u, v);
			op(pos[rts[v]], pos[v] + 1); }
		if (dep[u] > dep[v]) swap(u, v);
		op(pos[u] + VALS_EDGES, pos[v] + 1);
	}
	void processSubtree(int v, auto op) {
		op(pos[v] + VALS_EDGES, pos[v] + siz[v]); } };