/**
 * Author: user202729
 * Date: 2023-10-10
 * License: CC0
 * Description: Solves $A * x = b$. The passed-in matrix is $n$-row $m+1$-column, last column is $b$.
 *  Return empty vector if no solution.
 *  Currently only suitable for finite field.
 * Status: tested on https://codeforces.com/contest/1155/problem/E
 */
#include"Rref.h"

auto solveLinear(auto a){
	rref(a);
	vector<decltype(a[0][0]+0)> answer(sz(a[0])-1);
	//let assignDummy=[&](int col){ // can comment out if it's okay to find arbitrarily solution
	//	let value=answer[col]=0; // assign arbitrarily
	//	for(auto& row: a) row.back()-=value*row[col];
	//};
	//int coveredVar=sz(a[0])-1;
	down(rowIndex, sz(a)){
		let& row=a[rowIndex];
		let col=find(all(row), 1)-row.begin();
		if(col==sz(a[0])-1){ answer.clear(); return answer; }
		if(col==sz(a[0])) continue; // whole row 0
		assert(row[col]==1);

		//--coveredVar;
		//while(coveredVar>col) assignDummy(coveredVar--);
		answer[col]=row.back(); // assign to pivot variable
	}
	//while(coveredVar) assignDummy(--coveredVar);
	return answer;
}
