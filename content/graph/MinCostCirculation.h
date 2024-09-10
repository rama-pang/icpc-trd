/**
 * Author: rama_pang
 * Description: Minimum cost circulation. Can handle negative cycles.
 * Status: Tested on https://judge.yosupo.jp/problem/min_cost_b_flow (n \leq 100, m \leq 1000, 32ms).
 */
template <typename Flow, typename Cost, Flow SCALING_FACTOR = 2>
struct MinCostFlow {
  struct Edge {
    int src, dst;
    Flow flow, cap;
    Cost cost;
    int rev;
    Flow res_cap() { return cap - flow; }  // residual cap
  };

  int n;
  vector<vector<Edge>> g;
  vector<Flow> b;
  const Cost unreachable = numeric_limits<Cost>::max();
  Cost farthest;
  vector<Cost> pi, dist;  // pi = potential, dist = shortest path
  vector<Edge *> parent;  // shortest path parent
  priority_queue<pair<Cost, int>, vector<pair<Cost, int>>, greater<>> pq;
  vector<int> excess_vs, deficit_vs;

  MinCostFlow(int n) : n(n), g(n), b(n) {}
  Edge &rev(Edge &edge) { return g[edge.dst][edge.rev]; }
  pair<int, int> add_edge(int src, int dst, Flow lower, Flow upper, Cost cost) {
    assert(lower <= upper);
    int e = g[src].size(), re = src == dst ? e + 1 : g[dst].size();
    g[src].push_back(Edge{src, dst, 0, upper, cost, re});
    g[dst].push_back(Edge{dst, src, 0, -lower, -cost, e});
    return {src, e};
  }
  void add_supply(int v, Flow amount) { b[v] += amount; }
  void add_demand(int v, Flow amount) { b[v] -= amount; }
  void push(Edge &e, Flow amount) { e.flow += amount, rev(e).flow -= amount; }
  Cost res_cost(const Edge &e) { return e.cost + pi[e.src] - pi[e.dst]; }
  bool dual(const Flow delta) {
    dist.assign(n, unreachable);
    parent.assign(n, nullptr);
    excess_vs.erase(remove_if(all(excess_vs), [&](int v) { return b[v] < delta; }), end(excess_vs));
    deficit_vs.erase(remove_if(all(deficit_vs), [&](int v) { return b[v] > -delta; }), end(deficit_vs));
    for (auto v : excess_vs) pq.emplace(dist[v] = 0, v);
    farthest = 0;
    int deficit_count = 0;
    while (!pq.empty()) {
      auto [d, u] = pq.top();
      pq.pop();
      if (dist[u] != d) continue;
      farthest = d;
      if ((deficit_count += (b[u] <= -delta)) >= sz(deficit_vs)) break;
      for (auto &e : g[u]) {
        if (e.res_cap() < delta) continue;
        auto v = e.dst;
        auto dt = d + res_cost(e);
        if (dist[v] > dt) {
          pq.emplace(dist[v] = dt, v);
          parent[v] = &e;
        }
      }
    }
    pq = decltype(pq)();  // pq.clear() doesn't exist.
    rep(v, 0, n) pi[v] += min(dist[v], farthest);
    return deficit_count > 0;
  }
  void primal(const Flow delta) {
    for (auto t : deficit_vs) {
      if (dist[t] > farthest) continue;
      Flow f = -b[t];
      int v;
      for (v = t; parent[v] != nullptr; v = parent[v]->src) {
        f = min(f, parent[v]->res_cap());
      }
      f = min(f, b[v]);
      f -= f % delta;
      if (f <= 0) continue;
      for (v = t; parent[v] != nullptr;) {
        auto &e = *parent[v];
        push(e, f);
        int u = parent[v]->src;
        if (e.res_cap() <= 0) parent[v] = nullptr;
        v = u;
      }
      b[t] += f, b[v] -= f;
    }
  }
  void saturate_negative(const Flow delta) {
    for (auto &es : g) {
      for (auto &e : es) {
        auto rcap = e.res_cap();
        auto rcost = res_cost(e);
        rcap -= rcap % delta;
        if (rcost < 0 || rcap < 0) {
          push(e, rcap);
          b[e.src] -= rcap;
          b[e.dst] += rcap;
        }
      }
    }
    excess_vs.clear();
    deficit_vs.clear();
    rep(v, 0, n) {
      if (b[v] > 0) excess_vs.push_back(v);
      if (b[v] < 0) deficit_vs.push_back(v);
    }
  }
  optional<Cost> solve() {  // bool = whether solution exists
    pi.resize(n);
    Flow inf_flow = 1, delta = 1;
    for (auto t : b) inf_flow = max({inf_flow, t, -t});
    for (auto &es : g) for (auto &e : es) inf_flow = max({inf_flow, e.res_cap(), -e.res_cap()});
    while (delta < inf_flow) delta *= SCALING_FACTOR;
    for (; delta; delta /= SCALING_FACTOR) {
      saturate_negative(delta);
      while (dual(delta)) primal(delta);
    }
    Cost value = 0;
    for (auto &es : g) for (auto &e : es) value += e.flow * e.cost;
    value /= 2;  // double-counted both directions
    if (excess_vs.empty() && deficit_vs.empty()) {
      return value;
    }
    return nullopt;
  }
};