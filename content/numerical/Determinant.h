/**
 * Author: Simon Lindholm
 * Date: 2016-09-06
 * License: CC0
 * Source: folklore
 * Description: Calculates determinant of a matrix. Destroys the matrix.
 * Time: $O(N^3)$
 * Status: somewhat tested
 */
#pragma once

double det(vector<vector<double>>& a) {
	int n = sz(a); double re = 1;
	rep(i,0,n) {
		int b = i;
		rep(j,i+1,n) if (fabs(a[j][i]) > fabs(a[b][i])) b = j;
		if (i != b) swap(a[i], a[b]), re *= -1;
		re *= a[i][i];
		if (re == 0) return 0;
		rep(j,i+1,n) {
			double v = a[j][i] / a[i][i];
			if (v != 0) rep(k,i+1,n) a[j][k] -= v * a[i][k];
		}
	}
	return re;
}
