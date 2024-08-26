/**
 * Author: rama_pang
 * Description: Suffix automaton.
 * On Trie, must use BFS ordering to achieve linear time.
 * link is suffix links, 
 * length is maximum length in the endpos-equivalent state,
 * nxt is the transition.
 * Status: tested on https://www.luogu.com.cn/problem/P4770 and https://www.luogu.com.cn/problem/P6139.
 * Can refer to https://oi-wiki.org/string/general-sam/#%E8%BF%87%E7%A8%8B,
 * https://www.cnblogs.com/Xing-Ling/p/12038349.html, or
 * https://assets.hkoi.org/training2022/automata.pdf.
 */

template <int ALPHABET_SIZE = 26>
struct SuffixAutomaton {
  struct Node {
    int link, length;
    array<int, ALPHABET_SIZE> nxt;
    Node() : link(0), length(0), nxt({}) {}
  };

  vector<Node> t;
  SuffixAutomaton() {
    t.resize(2);  // [0: invalid, 1: empty string]
    fill(begin(t[0].nxt), end(t[0].nxt), 1);
    t[0].length = -1;
  }

  int NewNode() {
    t.emplace_back();
    return t.size() - 1;
  }

  int Extend(int p, int c) {  // p is current state, c is new character
    auto AddCont = [&]() {
      int q = t[p].nxt[c];
      if (t[p].length + 1 == t[q].length) return q;
      int r = NewNode();
      t[r].nxt = t[q].nxt, t[r].length = t[p].length + 1;
      t[r].link = exchange(t[q].link, r);
      while (t[p].nxt[c] == q) t[exchange(p, t[p].link)].nxt[c] = r;
      return r;
    };
    if (t[p].nxt[c] != 0) return AddCont();
    int cur = NewNode();
    t[cur].length = t[p].length + 1;
    while (t[p].nxt[c] == 0) t[exchange(p, t[p].link)].nxt[c] = cur;
    auto cont = AddCont();
    t[cur].link = cont;
    return cur;
  }
};
