/**
 * Author: rama_pang
 * Description: Suffix automaton. used for multiple pattern matching.
 * Status: tested on https://tlx.toki.id/problems/apio-2014/A
 */

class Eertree {
 public:
  int sz;
  string S;
  int suff_max;
  vector<int> len;
  vector<int> occ;
  vector<int> link;
  vector<vector<int>> to;

  Eertree()
      : sz(2),
        S(),
        suff_max(1),
        len(2),
        occ(2),
        link(2),
        to(2, vector<int>(26, -1)) {
    len[0] = -1, link[0] = 0;
    len[1] = 0, link[1] = 0;
  }
  int NewNode() {
    len.emplace_back();
    occ.emplace_back();
    link.emplace_back();
    to.emplace_back(vector<int>(26, -1));
    return sz++;
  }
  int Add(char c) {
    S.push_back(c);
    int pos = (int)S.size() - 1;
    int cur = suff_max;
    while (pos - 1 - len[cur] < 0 || S[pos - 1 - len[cur]] != c) {
      cur = link[cur];
    }
    if (to[cur][c - 'a'] != -1) {
      suff_max = to[cur][c - 'a'];
      occ[suff_max]++;
      return 0;
    }
    suff_max = NewNode();
    occ[suff_max] = 1;
    len[suff_max] = len[cur] + 2;
    to[cur][c - 'a'] = suff_max;
    if (len[suff_max] == 1) {
      link[suff_max] = 1;
      return 1;
    }
    cur = link[cur];
    while (pos - 1 - len[cur] < 0 || S[pos - 1 - len[cur]] != c) {
      cur = link[cur];
    }
    link[suff_max] = to[cur][c - 'a'];
    return 1;
  }
};
