/**
 * Author: rama_pang
 * Description: Palindromic automaton. 
 * Status: tested on https://tlx.toki.id/problems/apio-2014/A
 */

template <int ALPHABET_SIZE = 26>
struct Eertree {
  struct Node {
    int link, length, occ;
    array<int, ALPHABET_SIZE> nxt;
    Node() : link(0), length(0), occ(0) { fill(all(nxt), -1); }
  };

  int suff_max;   // maximum palindromic suffix
  vector<int> s;  // string
  vector<Node> t;
  Eertree() {
    t.resize(2);  // [-1 string, 0 string]
    t[0].length = -1;
    suff_max = 1;  // 0 string
  }

  int NewNode() {
    t.emplace_back();
    return sz(t) - 1;
  }

  int Add(int c) {
    s.push_back(c);
    int pos = sz(s) - 1;
    int cur = suff_max;
    while (pos - 1 - t[cur].length < 0 || s[pos - 1 - t[cur].length] != c) {
      cur = t[cur].link;
    }
    if (t[cur].nxt[c] != -1) {
      suff_max = t[cur].nxt[c];
      t[suff_max].occ++;
      return 0;
    }
    suff_max = NewNode();
    t[suff_max].occ = 1;
    t[suff_max].length = t[cur].length + 2;
    t[cur].nxt[c] = suff_max;
    if (t[suff_max].length == 1) {
      t[suff_max].link = 1;
      return 1;
    }
    cur = t[cur].link;
    while (pos - 1 - t[cur].length < 0 || s[pos - 1 - t[cur].length] != c) {
      cur = t[cur].link;
    }
    t[suff_max].link = t[cur].nxt[c];
    return 1;
  }
};
