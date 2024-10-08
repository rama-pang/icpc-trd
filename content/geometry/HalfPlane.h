/**
 * Author: rama_pang
 * Description: Half-Plane Intersection.
 * Time: O(n \log n)
 * Status: stress-tested
 */

namespace HalfPlane {
using T = long double;
using pi = pair<T, T>;
static constexpr T eps = 1e-8;
static bool z(T x) { return fabs(x) < eps; }
static T ccw(pi a, pi b, pi c) {
  return (b.first - a.first) * (c.second - a.second) -
         (b.second - a.second) * (c.first - a.first);
}
struct line {
  T a, b, c;
  bool operator<(const line &l) const {
    bool flag1 = pi(a, b) > pi(0, 0);
    bool flag2 = pi(l.a, l.b) > pi(0, 0);
    if (flag1 != flag2) return flag1 > flag2;
    T t = ccw(pi(0, 0), pi(a, b), pi(l.a, l.b));
    return z(t) ? c * hypot(l.a, l.b) < l.c * hypot(a, b) : t > 0;
  }
  pi slope() { return pi(a, b); }
};
pi cross(line a, line b) {
  T det = a.a * b.b - b.a * a.b;
  return pi((a.c * b.b - a.b * b.c) / det, (a.a * b.c - a.c * b.a) / det);
}
bool bad(line a, line b, line c) {
  if (ccw(pi(0, 0), a.slope(), b.slope()) <= 0) return false;
  pi crs = cross(a, b);
  return crs.first * c.a + crs.second * c.b >= c.c;
}
pair<bool, vector<pi>> solve(vector<line> v) {  // ax + by <= c;
  sort(v.begin(), v.end());
  deque<line> dq;
  for (auto &i : v) {
    if (!dq.empty() && z(ccw(pi(0, 0), dq.back().slope(), i.slope()))) continue;
    while (dq.size() >= 2 && bad(dq[dq.size() - 2], dq.back(), i))
      dq.pop_back();
    while (dq.size() >= 2 && bad(i, dq[0], dq[1])) dq.pop_front();
    dq.push_back(i);
  }
  while (dq.size() > 2 && bad(dq[dq.size() - 2], dq.back(), dq[0]))
    dq.pop_back();
  while (dq.size() > 2 && bad(dq.back(), dq[0], dq[1])) dq.pop_front();
  vector<pi> tmp;
  for (int i = 0; i < dq.size(); i++) {
    line cur = dq[i], nxt = dq[(i + 1) % dq.size()];
    if (ccw(pi(0, 0), cur.slope(), nxt.slope()) <= eps) return {false, {}};
    tmp.push_back(cross(cur, nxt));
  }
  return {true, tmp};
}
};  // namespace HalfPlane
