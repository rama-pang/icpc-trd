/**
 * Author: user202729
 * Date: 2023-10-09
 * License: CC0
 * Status: tested on https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3196, https://codeforces.com/contest/1155/problem/E
 * Description: Rref of a matrix over finite field.
 */

void rref(auto& a){
	int fix=0;
	rep(col, 0, sz(a[0])){
		rep(row, fix, sz(a)) if(a[row][col]!=0){
			swap(a[row], a[fix]);
			//if(row!=fix) det=-det;

			//det*=a[fix][col];
			let d=Mod(1)/a[fix][col];
			rep(j, col, sz(a[0])) a[fix][j]*=d;

			rep(i, 0, sz(a)) if(i!=fix){
				let d=a[i][col];
				rep(j, col, sz(a[0]))
					a[i][j]-=a[fix][j]*d;
			}

			++fix;
			break;
		}
	}
	//if(fix<sz(a)) det=0;
}
