/**
 * Author: user202729
 * Date: 2023-10-09
 * License: CC0
 * Status: tested on
 *  https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3196
 *  https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&category=0&problem=4714
 *  https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&category=0&problem=4775
 *  https://codeforces.com/contest/1155/problem/E
 *  https://open.kattis.com/problems/equationsolver
 * Description: Rref of a matrix.
 */
#pragma once
void rref(auto& a){
	int fix=0;
	rep(col, 0, sz(a[0])){
#if RREFFINITEFIELD
		rep(row, fix, sz(a)) if(a[row][col]!=0)
#else
		let row=int(max_element(a.begin()+fix, a.end(), [&](let& x, let& y){return abs(x[col])<abs(y[col]);})-a.begin());
		if(row<sz(a) and abs(a[row][col])>epsilon)
#endif
		{
			swap(a[row], a[fix]);
			//if(row!=fix) det=-det;

			//det*=a[fix][col];
			let d=1/a[fix][col];
			rep(j, col, sz(a[0])) a[fix][j]*=d;

			rep(i, 0, sz(a)) if(i!=fix){
				let d=a[i][col];
				rep(j, col, sz(a[0]))
					a[i][j]-=a[fix][j]*d;
			}

			++fix;
#if RREFFINITEFIELD
			break;
#endif
		}
	}
	//if(fix<sz(a)) det=0;
}
