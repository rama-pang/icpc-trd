/**
 * Author: Ulf Lundstrom
 * Date: 2009-03-21
 * License: CC0
 * Source:
 * Description:\\
\begin{minipage}{75mm}
Returns the shortest distance between point p and the line segment from point s to e.
\end{minipage}
\begin{minipage}{15mm}
\vspace{-10mm}
\includegraphics[width=\textwidth]{content/geometry/SegmentDistance}
\end{minipage}
 * Usage: 
 * 	Point<double> a, b(2,2), p(1,1);
 * 	bool onSegment = segDist(a,b,p) < 1e-10;
 * Status: tested
 */
#pragma once

#include "Point.h"

typedef Point<double> P;
double segDist(P& s, P& e, P& p) {
	if (s==e) return (p-s).len();
	auto d = (e-s).norm(), t = min(d,max(.0,(p-s).dot(e-s)));
	return ((p-s)*d-(e-s)*t).len()/d;
}
