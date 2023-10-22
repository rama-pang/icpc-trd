/**
 * Author: Codeforces
 * Date: 2023-10-22
 * Source: https://codeforces.com/blog/entry/10355
 * Description: Rope data structure, STL extension.
 */
#include<ext/rope>
using namespace __gnu_cxx;
rope<int> v(3, 0); // initial list not supported
vector<int> a{1, 2, 3, 4};
rope<int> w(a.data(), sz(a));
v.push_back(3);
assert(sz(v.substr(1, 2))==2);
v.erase(1, 2);
assert(sz(v)==2);
rope<int> cur=v.substr(0, 1);
v.insert(0, cur);
for(auto x: v) return x;
