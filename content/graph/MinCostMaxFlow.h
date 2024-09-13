/**
 * Author: rama_pang
 * Description: Min-cost max-flow. Note that negative cost cycles are not supported.
 * Status: Tested on kattis:mincostmaxflow
 */

template <typename T>
struct mcmf {
  struct edge { int to, rev; T cap, cost; };
  static constexpr T INF = numeric_limits<T>::max() / 4;
  int n; vector<T> dist;
  vector<vector<edge>> adj;
  vector<pair<int, int>> prv;  // (node, reverse edge index)
  mcmf(int n) : n(n), adj(n), dist(n), prv(n) {}
  void add_edge(int s, int e, T cap, T cost) {
    adj[s].push_back({e, sz(adj[e]), cap, cost});
    adj[e].push_back({s, sz(adj[s]) - 1, 0, -cost}); }
  bool spfa(int src, int sink, int n) {  // note: doesn't check negative cycle
    fill(all(dist), INF); bool ok = 0;
    queue<int> que; vector<bool> inque(n, false);
    dist[src] = 0; inque[src] = 1; que.push(src);
    while (!que.empty()) {
      int v = que.front(); que.pop(); inque[v] = 0;
      if (v == sink) ok = 1;
      rep(i, 0, sz(adj[v])) {
        auto e = adj[v][i];
        if (e.cap > 0 && dist[e.to] > dist[v] + e.cost) {
          dist[e.to] = dist[v] + e.cost;
          prv[e.to] = {v, i};
          if (!inque[e.to]) {
            inque[e.to] = 1;
            que.push(e.to); } } } }
    return ok; }
  bool dijkstra(int src, int sink, int n) {
    priority_queue<pair<T, int>> pq;
    vector<T> new_dist(n, INF); bool ok = 0;
    new_dist[src] = 0; pq.emplace(0, src);
    while (sz(pq)) {
      auto [dt, v] = pq.top(); dt *= -1; pq.pop();
      if (new_dist[v] != dt) continue;
      if (v == sink) ok = 1;
      rep(i, 0, sz(adj[v])) {
        auto e = adj[v][i];
        T new_weight = e.cost + dist[v] - dist[e.to];
        if (e.cap > 0 && new_dist[e.to] > new_dist[v] + new_weight) {
          new_dist[e.to] = new_dist[v] + new_weight;
          prv[e.to] = {v, i};
          pq.emplace(-new_dist[e.to], e.to); } } }
    if (ok) rep(i, 0, n) dist[i] = min(dist[i] + new_dist[i], INF);
    return ok; }
  pair<T, T> costflow(int src, int sink) {
    T cost = 0, flow = 0;
    // spfa(src, sink, n); // uncomment if costs are negative
    while (dijkstra(src, sink, n)) {
      T cap = INF;
      for (int to = sink; to != src; to = prv[to].first) {
        auto [x, i] = prv[to];
        cap = min(cap, adj[x][i].cap); }
      cost += cap * (dist[sink] - dist[src]); flow += cap;
      for (int to = sink; to != src; to = prv[to].first) {
        auto [x, i] = prv[to];
        int rev = adj[x][i].rev;
        adj[x][i].cap -= cap;
        adj[to][rev].cap += cap; } }
    return {cost, flow}; }
};