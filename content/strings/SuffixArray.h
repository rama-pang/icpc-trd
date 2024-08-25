/**
 * Author: atcoder library
 * Description: Suffix array in O(n log n) time.
 * Status: probably tested by atcoder.
 */
#pragma once

// Given a string `s` of length $n$, it returns the suffix array of `s`.
// Here, the suffix array `sa` of `s` is a permutation of $0, \cdots, n-1$
// such that `s[sa[i]..n) < s[sa[i+1]..n)` holds for all $i = 0,1, \cdots ,n-2$.
vector<int> suffix_array(const vector<int> &s) {
  let n = sz(s);
  vector<int> sa(n), rnk = s, tmp(n);
  iota(all(sa), 0);
  for (int k = 1; k < n; k *= 2) {
    auto cmp = [&](int x, int y) {
      if (rnk[x] != rnk[y]) return rnk[x] < rnk[y];
      int rx = x + k < n ? rnk[x + k] : -1;
      int ry = y + k < n ? rnk[y + k] : -1;
      return rx < ry;
    };
    sort(all(sa), cmp);
    tmp[sa[0]] = 0;
    rep(i, 1, n) tmp[sa[i]] = tmp[sa[i - 1]] + cmp(sa[i - 1], sa[i]);
    swap(tmp, rnk);
  }
  return sa;
}

// Given a string `s` of length $n$, it returns the LCP array of `s`.
// Here, the LCP array of `s` is the array of length $n-1$, such that
// the $i$-th element is the length of the LCP (Longest Common Prefix)
// of `s[sa[i]..n)` and `s[sa[i+1]..n)`.
vector<int> lcp_array(const vector<int> &s, const vector<int> &sa) {
  int n = sz(s), h = 0;
  assert(n >= 1);
  vector<int> rnk(n), lcp(n - 1);
  rep(i, 0, n) { rnk[sa[i]] = i; }
  rep(i, 0, n) {
    if (h > 0) h--;
    if (rnk[i] == 0) continue;
    int j = sa[rnk[i] - 1];
    for (; j + h < n && i + h < n; h++) {
      if (s[j + h] != s[i + h]) break;
    }
    lcp[rnk[i] - 1] = h;
  }
  return lcp;
}

struct LCP {
  int N;
  vector<int> sainv;  // len = N
  RMQ<int> rmq;
  LCP(const vector<int> s) : N(sz(s)), sainv{}, rmq{{}} {
    auto sa = suffix_array(s);
    auto lcp = lcp_array(s, sa);
    sainv.resize(N);
    rep(i, 0, N) sainv[sa[i]] = i;
    rmq = {lcp};
  }
  int lcplen(int l1, int l2) const {
    if (l1 == l2) return N - l1;
    if (l1 == N or l2 == N) return 0;
    l1 = sainv[l1], l2 = sainv[l2];
    if (l1 > l2) swap(l1, l2);
    return rmq(l1, l2);
  }
};
