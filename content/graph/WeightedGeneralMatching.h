/**
 * Author:
 * Date:
 * License: CC0
 * Source: https://judge.yosupo.jp/submission/234606
 * Description:
 * Time: O(N^3)
 * Status:
 */
#define fi first
#define se second
#define pb push_back
const int N = 501; // + 1 due to 1-indexed!
struct Matching {
using T = ll; const T inf = 1e18;
struct edge { int u, v; T w; } g[N * 2][N * 2];
int n, nx, m[N * 2], sl[N * 2], st[N * 2], p[N * 2], fr[N * 2][N * 2], s[N * 2], vis[N * 2];
T l[N * 2]; vi fl[N * 2]; deque<int> q;
void init(int _n) {
  n = nx = _n; q.clear(); rep(u, 1, n * 2 + 1) {
    m[u] = sl[u] = p[u] = s[u] = vis[u] = 0;
    st[u] = u; l[u] = inf; fl[u].clear();
    rep(v, 1, n * 2 + 1) g[u][v] = edge{u, v, 0}, fr[u][v] = (u == v ? u : 0); } }
void addEdge(int u, int v, T w) { g[u][v].w = g[v][u].w = max(g[v][u].w, w); }
T di(edge e) { return l[e.u] + l[e.v] - g[e.u][e.v].w * 2; }
void up(int u, int x) { if (!sl[x] || di(g[u][x]) < di(g[sl[x]][x])) sl[x] = u; }
void ssl(int x) { sl[x] = 0; rep(u, 1, n + 1) if (g[u][x].w && st[u] != x && !s[st[u]]) up(u, x); }
void pu(int x) { if (x <= n) return q.pb(x); for (int i: fl[x]) pu(i); }
void sst(int x, int b) { st[x] = b; if (x <= n) return; for (int i: fl[x]) sst(i, b); }
int gp(int b, int xr) {
  int pr = find(all(fl[b]), xr) - fl[b].begin();
  return pr%2 ? reverse(1 + all(fl[b])), sz(fl[b]) - pr : pr; }
void sm(int u, int v) {
  m[u] = g[u][v].v; if (u <= n) return;
  int xr = fr[u][g[u][v].u], pr = gp(u, xr);
  rep(i, 0, pr) sm(fl[u][i], fl[u][i ^ 1]);
  sm(xr, v); rotate(fl[u].begin(), pr + all(fl[u])); }
void au(int u, int v) {
  int xnv = st[m[u]]; sm(u, v); if (!xnv) return;
  sm(xnv, st[p[xnv]]); au(st[p[xnv]], xnv); }
int gl(int u, int v) {
  static int t = 0; for (++t; u || v; swap(u, v)) {
    if (!u) continue; if (vis[u] == t) return u;
    vis[u] = t; u = st[m[u]]; if (u) u = st[p[u]];
  } return 0; }
void ad(int u, int lca, int v) {
  int b = n + 1; while (b <= nx && st[b]) ++b;
  if (b > nx) ++nx; l[b] = s[b] = 0; m[b] = m[lca];
  fl[b] = {lca}; for (int x = u, y; x != lca; x = st[p[y]])
    fl[b].pb(x), fl[b].pb(y = st[m[x]]), pu(y);
  reverse(1 + all(fl[b]));
  for (int x = v, y; x != lca; x = st[p[y]])
    fl[b].pb(x), fl[b].pb(y = st[m[x]]), pu(y);
  sst(b, b); rep(x, 1, nx + 1) g[b][x].w = g[x][b].w = 0;
  rep(x, 1, n + 1) fr[b][x] = 0; for (int xs: fl[b]) {
    rep(x, 1, nx + 1) if (!g[b][x].w || di(g[xs][x]) < di(g[b][x]))
      g[b][x] = g[xs][x], g[x][b] = g[x][xs];
    rep(x, 1, n + 1) if (fr[xs][x]) fr[b][x] = xs;
  } ssl(b); }
void e(int b) {
  for (int i: fl[b]) sst(i, i);
  int xr = fr[b][g[b][p[b]].u], pr = gp(b, xr);
  for (int i = 0; i < pr; i += 2) {
    int xs = fl[b][i], xns = fl[b][i + 1]; p[xs] = g[xns][xs].u;
    s[xs] = 1, s[xns] = sl[xs] = 0, ssl(xns); pu(xns);
  } s[xr] = 1, p[xr] = p[b];
  rep(i, pr + 1, sz(fl[b])) s[fl[b][i]] = -1, ssl(fl[b][i]);
  st[b] = 0; }
bool f(edge e) {
  int u = st[e.u], v = st[e.v];
  if (s[v] == -1) { p[v] = e.u, s[v] = 1;
    int nu = st[m[v]]; sl[v] = sl[nu] = s[nu] = 0, pu(nu);
  } else if (!s[v]) if (int lca = gl(u, v); !lca)
      return au(u,v), au(v,u), 1; else ad(u, lca, v); return 0; }
bool ma() {
  q.clear(); rep(x, 1, nx + 1) { s[x] = -1, sl[x] = 0;
    if (st[x] == x && !m[x]) p[x] = s[x] = 0, pu(x);
  } if (q.empty()) return 0; for (;;) {
    while (!q.empty()) { int u = q.front(); q.pop_front();
      if (s[st[u]] == 1) continue;
      rep(v, 1, n + 1) if (g[u][v].w && st[u] != st[v])
          if (!di(g[u][v])) { if (f(g[u][v])) return 1; }
          else up(u, st[v]);
    } T d = inf; rep(b, n + 1, nx + 1)
      if (st[b] == b && s[b] == 1) d = min(d, l[b] / 2);
    rep(x, 1, nx + 1) if (st[x] == x && sl[x])
        if (s[x] == -1) d = min(d, di(g[sl[x]][x]));
        else if (!s[x]) d = min(d, di(g[sl[x]][x]) / 2);
    rep(u, 1, n + 1)
      if (!s[st[u]]) { if (l[u] <= d) return 0; l[u] -= d; }
      else if (s[st[u]] == 1) l[u] += d;
    rep(b, n + 1, nx + 1) if (st[b] == b)
        if (!s[st[b]]) l[b] += d * 2;
        else if (s[st[b]] == 1) l[b] -= d * 2;
    q.clear(); rep(x, 1, nx + 1)
      if (st[x] == x && sl[x] && st[sl[x]] != x
        && !di(g[sl[x]][x])&&f(g[sl[x]][x])) return 1;
    rep(b,n+1,nx+1) if(st[b] == b && s[b] == 1 && !l[b]) e(b); } }
void solve() { while (ma()); } }; // M.m[u] is matched vertex of u
