/**
 * Author: rama_pang
 * Description: Suffix automaton. used for multiple pattern matching.
 * Status: tested on https://www.luogu.com.cn/problem/P4770
 */

template<int ALPHABET_SIZE = 26>
struct SuffixAutomaton {
  struct Node {
    int link, length;
    array<int, ALPHABET_SIZE> nxt;
    Node() : link(0), length(0), nxt({}) {}
  };

  vector<Node> t;
  SuffixAutomaton() {
    t.resize(2); // [imaginary string, empty string]
    fill(begin(t[0].nxt), end(t[0].nxt), 1);
    t[0].length = -1;
  }

  int NewNode() {
    t.emplace_back();
    return sz(t) - 1;
  }

  int Extend(int p, int c) {
    if (t[p].nxt[c] != 0) {
      int q = t[p].nxt[c];
      if (t[p].length + 1 == t[q].length) {
        return q;
      }
      int r = NewNode();
      t[r].length = t[p].length + 1;
      t[r].link = t[q].link;
      t[r].nxt = t[q].nxt;
      t[q].link = r;
      while (t[p].nxt[c] == q) {
        t[p].nxt[c] = r;
        p = t[p].link;
      }
      return r;
    }
    int cur = NewNode();
    t[cur].length = t[p].length + 1;
    while (t[p].nxt[c] == 0) {
      t[p].nxt[c] = cur;
      p = t[p].link;
    }
    int q = t[p].nxt[c];
    if (t[p].length + 1 == t[q].length) {
      t[cur].link = q;
    } else {
      int r = NewNode();
      t[r].length = t[p].length + 1;
      t[r].nxt = t[q].nxt;
      t[r].link = t[q].link;
      t[q].link = t[cur].link = r;
      while (t[p].nxt[c] == q) {
        t[p].nxt[c] = r;
        p = t[p].link;
      }
    }
    return cur;
  }
};
