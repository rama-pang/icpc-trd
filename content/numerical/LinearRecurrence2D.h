/**
 * Author: user202729
 * Date: 2023-10-22
 * Description: Tools to work with 2D linear recurrence.
 */

#include"/home/user202729/icpc-trd/content/number-theory/ModularArithmetic.h"
#define RREFFINITEFIELD 1
#include"/home/user202729/icpc-trd/content/numerical/Rref.h"
#include"/home/user202729/icpc-trd/content/numerical/NumberTheoreticTransform.h"

void fillTable(auto& table, int numRow, int numCol, let& recurrence){
	// table should be pre-filled with initial terms
	// for example if table[r][c] = table[r-1][c] + table[r][c-2] then recurrence=[0 0 1; 1 0 -1]
	assert(recurrence.back().back()==-1);
	rep(r, 0, numRow){
		if(r>=sz(table)) table.push_back({0, r*(r+1)/2});
		rep(c, 0, numCol) if(c>=sz(table[r])){
			table[r].push_back(0);
			Mod answer {};
			rep(i, 0, sz(recurrence)) rep(j, 0, sz(recurrence[0])) if(i<=r and j<=c)
				answer+=recurrence.rbegin()[i].rbegin()[j]*table[r-i][c-j];
			table[r].back()=answer;
		}
	}
}

auto solveLinear_(auto a){
	rref(a);
	vector<decltype(a[0][0]+0)> answer(sz(a[0])-1);
	let assignDummy=[&](int col){ // can comment out if it's okay to find arbitrarily solution
		let value=answer[col]=col==sz(answer)-1; // assign arbitrarily
		for(auto& row: a) row.back()-=value*row[col];
	};
	int coveredVar=sz(a[0])-1;
	down(rowIndex, sz(a)){
		let& row=a[rowIndex];
		let col=find(all(row), 1)-row.begin();
		if(col==sz(a[0])-1){ answer.clear(); return answer; }
		if(col==sz(a[0])) continue; // whole row 0
		assert(row[col]==1);

		--coveredVar;
		while(coveredVar>col) assignDummy(coveredVar--);
		answer[col]=row.back(); // assign to pivot variable
	}
	while(coveredVar) assignDummy(--coveredVar);
	return answer;
}

void findRecurrence(auto const& table, int sizeI, int sizeJ){
	// find 2D recurrence from small number of entries that uses sizeI * sizeJ previous terms
	vector<vector<Mod>> matrix;
	rep(i, 0, sz(table)+1-sizeI) rep(j, 0, sz(table[0])+1-sizeJ){
		matrix.push_back({});
		rep(k, i, i+sizeI) rep(l, j, j+sizeJ) matrix.back().push_back(table[k][l]);
	}
	auto v=solveLinear_(matrix); v.push_back(-1);
	rep(r, 0, sizeI){
		cerr<<'{';
		rep(c, 0, sizeJ) cerr<<v[r*sizeJ+c]<<',';
		cerr<<"},";
	}
	cerr<<'\n';
}

void computeNumerator(let& table, let& recurrence){
	// given table of naively computed values and the recurrence, compute the numerator
	assert(recurrence.back().back()==-1);
	cerr<<"Numerator:\n";
	rep(r, 0, sz(table)) {
		rep(c, 0, sz(table[0])){
			Mod answer {};
			rep(i, 0, sz(recurrence)) rep(j, 0, sz(recurrence[0])) if(i<=r and j<=c)
				answer+=recurrence.rbegin()[i].rbegin()[j]*table[r-i][c-j];
			cerr<<answer<<' ';
		}
		cerr<<'\n';
	}
}

Mod linearRec2D(let& table, auto tr, auto row, auto col){
	// tr is the recurrence in the format above. Note that this is reverse of that in LinearRecurrence.h.
	let n=sz(tr)-1;
	assert(sz(table)==n); assert(n>0);
	assert(sz(table[0])>col);

	for(auto& row: tr) reverse(all(row));
	auto i=polyinv(tr[n], ceillog2(col+1));
	i.resize(col+1);
	assert(i[0]==-1); for(auto& x: i) x=-x;
	let conv1=[&](vm a, vm b){ a=conv(move(a), move(b)); a.resize(col+1); return a; };
	let add1=[&](vm& a, vm const& b){ a.resize(col+1); rep(i, 0, sz(a)) a[i]+=b[i]; };
	tr.pop_back(); for(auto& row: tr) row=conv1(row, i);
	reverse(all(tr));

	auto combine = [&](vector<vm> a, vector<vm> b) {
		vector<vm> res(n*2-1);
		rep(i,0,sz(a)) rep(j,0,sz(b)) add1(res[i + j], conv1(a[i], b[j]));
		while(sz(res)>n){
			rep(j,0,n) add1(res.end()[-j-2], conv1(res.back(), tr[j]));
			res.pop_back();
		}
		return res;
	};

	vector<vm> pol{{1}}, e{{0}, {1}};
	for (auto p=row; p; p>>=1, e=combine(e, e)) if (p&1) pol = combine(move(pol), e);

	Mod res = 0;
	rep(i,0,sz(pol)) rep(j, 0, col+1) res += pol[i][j] * table[i][col-j];
	return res;
}
