/**
 * Author: hitonanode
 * Status: tested (https://judge.yosupo.jp/submission/231080).
 * original source at https://judge.yosupo.jp/submission/41769
 * Description: Run Enumerate for strings in O(n log n) time (n = 2e5 -> ~135 ms in yosupo)
 *
 * `lyndon\_factorization`:
 * Lyndon factorization based on Duval's algorithm in O(n)
 * A string is called simple (or a Lyndon word), if it is strictly smaller
 * than any of its own nontrivial suffixes.
 * The Lyndon decomposition of string $s$ is a factorization $s = w_1 w_2 \cdots w_k$,
 * where all strings $w_i$ are simple, and are in non-increasing order
 * $w_1 \geq w_2 \geq \cdots \geq w_k$.
 *
 * `longest\_lyndon\_prefixes`
 * Compute the longest Lyndon prefix for each suffix s[i:N] in O(n log n)
 * A Lyndon prefix is the longest prefix that is a Lyndon word.
 *
 * `run\_enumerate`
 * Compute all runs in given string, returning tuples $(l,r,p)$ in O(n log n)
 * Given a string $S$, the tuple $(l,r,p)$ is a run of string $S$ if:
 * (1) $0 \leq l < r \leq |S|$
 * (2) $1 \leq p \leq |S|$
 * (3) $r - l \geq 2p$
 * (4) $p$ is the smallest positive integer where $S[i]=S[i+p]$ holds for all $l \leq i < r-p$.
 * (5) The above four properties doesn't hold for tuple $(l-1,r,p)$ and $(l,r+1,p)$.
 *
 * Facts about runs:
 * (1) There are at most $n$ runs.
 * (2) The sum of $(r-l)/p$ for all runs are at most $3n$.
 * (3) The sum of 2-repeats $(r-l-2p+1)$ obtained from runs are at most $n \log n$.
 */
vector<pii> lyndon_factorization(const vi &S) {
  let N = sz(S); vector<pii> ret;
  for (int l = 0; l < N;) {
    int i = l, j = i + 1;
    while (j < N && S[i] <= S[j]) i = (S[i] == S[j] ? i + 1 : l), j++;
    ret.emplace_back(l, j - i), l += j - i; }
  return ret; }
vi longest_lyndon_prefixes(const vi &s, const LCP &rh) {
  let N = sz(s); vi ret(N); vector<pii> st{{N, N}};
  for (int i = N - 1, j = i; i >= 0; i--, j = i) {
    while (sz(st) > 1) {
      int iv = st.back().first, jv = st.back().second;
      int l = rh.lcplen(i, iv);
      if (!(iv + l < N and s[i + l] < s[iv + l])) break;
      j = jv; st.pop_back(); }
    st.emplace_back(i, j);
    ret[i] = j - i + 1; }
  return ret; }
vector<tuple<int, int, int>> run_enumerate(vi s) {
  if (s.empty()) return {};
  LCP rh(s); reverse(all(s));
  LCP rrev(s); reverse(all(s));
  let N = sz(s); auto t = s;
  auto lo = *min_element(all(s)), hi = *max_element(all(s));
  for (auto &c : t) c = hi - (c - lo);
  auto l1 = longest_lyndon_prefixes(s, rh), l2 = longest_lyndon_prefixes(t, rh);
  vector<tuple<int, int, int>> ret;
  for (int i = 0; i < N; i++) {
    rep(_, 0, 2) {
      int j = i + (_ ? l2 : l1)[i], L = i - rrev.lcplen(N - i, N - j), R = j + rh.lcplen(i, j);
      if (R - L >= (j - i) * 2) ret.emplace_back(L, R, j - i); } }
  sort(all(ret)); ret.erase(unique(all(ret)), ret.end()); return ret; }