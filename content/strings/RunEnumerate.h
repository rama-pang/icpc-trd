/**
 * Author: hitonanode
 * Description: Run Enumerate for strings in O(n log n) time.
 * Status: tested (https://judge.yosupo.jp/submission/230946).
 * original source at https://judge.yosupo.jp/submission/41769
 */

#pragma once

// Lyndon factorization based on Duval's algorithm
// A string is called simple (or a Lyndon word), if it is strictly smaller
// than any of its own nontrivial suffixes.
// Examples of simple strings are a,b,ab,aab,abb,abcd,abac.
// The Lyndon decomposition of string $s$ is a factorization $s = w_1 w_2 \cdots w_k$,
// where all strings $w_i$ are simple, and are in non-increasing order $w_1 \geq w_2 \geq \cdots \geq w_k$.
// Returns the list of substrings of the Lyndon factorization.
vector<pair<int, int>> lyndon_factorization(const vector<int> &S) {
  let N = sz(S);
  vector<pair<int, int>> ret;
  for (int l = 0; l < N;) {
    int i = l, j = i + 1;
    while (j < N && S[i] <= S[j]) i = (S[i] == S[j] ? i + 1 : l), j++;
    ret.emplace_back(l, j - i), l += j - i;
  }
  return ret;
}

// Compute the longest Lyndon prefix for each suffix s[i:N].
// A Lyndon prefix is the longest prefix that is a Lyndon word.
// Our implementation is $O(N \log N)$
// Example:
// - `teletelepathy` -> [1,4,1,2,1,4,1,2,1,4,1,2,1]
vector<int> longest_lyndon_prefixes(const vector<int> &s, const LCP &rh) {
  let N = sz(s);
  vector<pair<int, int>> st{{N, N}};
  vector<int> ret(N);
  for (int i = N - 1, j = i; i >= 0; i--, j = i) {
    while (sz(st) > 1) {
      int iv = st.back().first, jv = st.back().second;
      int l = rh.lcplen(i, iv);
      if (!(iv + l < N and s[i + l] < s[iv + l])) break;
      j = jv;
      st.pop_back();
    }
    st.emplace_back(i, j);
    ret[i] = j - i + 1;
  }
  return ret;
}

// Compute all runs in given string, returning tuples $(l,r,p)$.
// Complexity: $O(N \log N)$ in this implementation (N = 2e5 -> ~300 ms in yosupo)
// Given a string $S$, the tuple $(l,r,p)$ is a run of string $S$ if
// - $0 \leq l < r \leq |S|$
// - $1 \leq p \leq |S|$
// - $r - l \geq 2p$
// - $p$ is the smallest positive integer where $S[i]=S[i+p]$ holds for all $l \leq i < r-p$.
// - The above four properties doesn't hold for tuple $(l-1,r,p)$ and $(l,r+1,p)$.
// Facts about runs:
// - There are at most $n$ runs.
// - The sum of $(r-l)/p$ for all runs are at most $3n$.
// - The sum of 2-repeats $(r-l-2p+1)$ obtained from runs are at most $n \log n$.
vector<tuple<int, int, int>> run_enumerate(vector<int> s) {
  if (s.empty()) return {};
  LCP rh(s);
  reverse(all(s));
  LCP rrev(s);
  reverse(all(s));
  auto t = s;
  auto lo = *min_element(all(s)), hi = *max_element(all(s));
  for (auto &c : t) c = hi - (c - lo);
  auto l1 = longest_lyndon_prefixes(s, rh), l2 = longest_lyndon_prefixes(t, rh);
  let N = sz(s);
  vector<tuple<int, int, int>> ret;
  for (int i = 0; i < N; i++) {
    rep(_, 0, 2) {
      int j = i + (_ ? l2 : l1)[i], L = i - rrev.lcplen(N - i, N - j), R = j + rh.lcplen(i, j);
      if (R - L >= (j - i) * 2) ret.emplace_back(L, R, j - i);
    }
  }
  sort(all(ret));
  ret.erase(unique(all(ret)), ret.end());
  return ret;
}
