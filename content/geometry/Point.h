/**
 * Author: Ulf Lundstrom
 * Date: 2009-02-26
 * License: CC0
 * Source: My head with inspiration from tinyKACTL
 * Description: Class to handle points in the plane.
 * 	T can be e.g. double or long long. (Avoid int.)
 * Status: Works fine, used a lot
 */
#pragma once

int sgn(auto x) { return (x > 0) - (x < 0); }
template<class T>
struct Point {
	using P=Point;
	T x, y;
#define C(O) bool operator O(P p) const { return tie(x,y) O tie(p.x,p.y); }
	C(<) C(==)
#undef C
	P operator+(P p) const { return P{x+p.x, y+p.y}; }
	P operator-(P p) const { return P{x-p.x, y-p.y}; }
	P operator*(T d) const { return P{x*d, y*d}; }
	P operator/(T d) const { return P{x/d, y/d}; }
	T dot(P p) const { return x*p.x + y*p.y; }
	T cross(P p) const { return x*p.y - y*p.x; }
	T cross(P a, P b) const { return (a-*this).cross(b-*this); }
	tuple<bool, T, T> decompose(P a, P b) const {
		let d=a.cross(b); if(d==0) return {};
		return {true, cross(b)/d, a.cross(*this)/d};
	}
	T norm() const { return x*x + y*y; }
	auto len() const { return sqrt(norm()); }
	// angle to x-axis in interval [-pi, pi]
	double angle() const { return atan2(y, x); }
	P perp() const { return P{-y, x}; } // rotates 90 degrees ccw
	// returns point rotated 'a' radians ccw
	P rotate(double a) const {
		return P{x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)}; }
	friend ostream& operator<<(ostream& os, P p) {
		return os << "(" << p.x << "," << p.y << ")"; }
};
