/**
 * Author: Simon Lindholm
 * Date: 2016-12-09
 * License: CC0
 * Source: http://www.mimuw.edu.pl/~mucha/pub/mucha_sankowski_focs04.pdf
 * Description: Matching for general graphs.
 * Fails with probability $N / mod$.
 * Time: O(N^3)
 * Status: not very well tested
 */
#pragma once

int matInv(vector<vector<Mod>>& A) {
	int n = sz(A); vi col(n);
	vector<vector<Mod>> tmp(n, vector<Mod>(n));
	rep(i,0,n) tmp[i][i] = 1, col[i] = i;

	rep(i,0,n) {
		int r = i, c = i;
		rep(j,i,n) rep(k,i,n) if (A[j][k] != 0) {
      r = j, c = k;
      break;
    }    
		if (A[r][c] == 0) return i;
		A[i].swap(A[r]), tmp[i].swap(tmp[r]);
		rep(j,0,n) swap(A[j][i], A[j][c]), swap(tmp[j][i], tmp[j][c]);
		swap(col[i], col[c]);
		Mod v = A[i][i].inv();
		rep(j,i+1,n) {
			Mod f = A[j][i] * v;
			A[j][i] = 0;
			rep(k,i+1,n) A[j][k] -= f*A[i][k];
			rep(k,0,n) tmp[j][k] -= f*tmp[i][k];
		}
		rep(j,i+1,n) A[i][j] *= v;
		rep(j,0,n) tmp[i][j] *= v;
		A[i][i] = 1;
	}

	/// forget A at this point, just eliminate tmp backward
	down(i, n) rep(j,0,i) {
		Mod v = A[j][i];
		rep(k,0,n) tmp[j][k] -= v*tmp[i][k];
	}

	rep(i,0,n) rep(j,0,n) A[col[i]][col[j]] = tmp[i][j];
	return n;
}

vector<pii> generalMatching(int n, const vector<pii> &ed) {
	vector<vector<Mod>> mat(n, vector<Mod>(n)), A;
	for (auto [a, b] : ed) {
		Mod r = rnd();
		mat[a][b] = r, mat[b][a] = -r;
	}
	int r = matInv(A = mat), m = 2 * n - r, fi, fj;
	assert(r % 2 == 0); // return r/2; // size of matching

	if (m != n) do {
		mat.resize(m, vector<Mod>(m));
		rep(i,0,n) {
			mat[i].resize(m);
			rep(j,n,m) {
				Mod r = rnd();
				mat[i][j] = r, mat[j][i] = -r;
			}
		}
	} while (matInv(A = mat) != m);

	vi has(m, 1);
	vector<pii> re;
	rep(it, 0, m/2) {
		rep(i, 0, m) if (has[i]) {
			rep(j, i+1, m) if (A[i][j] != 0 && mat[i][j] != 0) {
				fi = i, fj = j; goto done;
			} assert(0); done:
			if (fj < n) re.emplace_back(fi, fj);
			has[fi] = has[fj] = 0;
			rep(sw, 0, 2) {
				Mod a = A[fi][fj].inv();
				rep(i, 0, m) if (has[i] && A[i][fj] != 0) {
					Mod b = A[i][fj] * a;
					rep(j, 0, m) A[i][j] -= A[fi][j] * b;
				}
				swap(fi, fj);
			}
		}
	}
	return re;
}
