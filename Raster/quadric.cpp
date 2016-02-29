//
//  quadric.cpp
//  Raster
//
//  Created by Matthew Dillard on 2/28/16.
//

#include "quadric.h"

std::istream& operator>>(std::istream& is, quadric::equation& eq) {
	std::string s;
	std::stringstream ss;
	
	is >> s;
	
	for (char &c : s) {
		if (c == '(' || c == ',' || c == ')')
			c = ' ';
	}
	
	ss << s;
	
	ss >> eq.A >> eq.B >> eq.C >> eq.D >> eq.E >> eq.F >> eq.G >> eq.H >> eq.I >> eq.J;
	
	return is;
}

std::ostream& operator<<(std::ostream& os, const quadric::equation& eq) {
	os << '(' << eq.A << ',' << eq.B << ',' << eq.C << ',' << eq.D << ',' << eq.E << ',' << eq.F << ',' << eq.G << ',' << eq.H << ',' << eq.I << ',' << eq.J << ')';
	return os;
}


quadric::quadric(const colordata& colors,
				 const FLOAT3& pos,
				 const equation& quadratic) {
	m_colors = new colordata(colors);
	m_pos = new FLOAT3(pos);
	m_eq = new equation(quadratic);
}

quadric::~quadric() {
	delete m_colors;
	delete m_pos;
	delete m_eq;
	
	m_colors = 0;
	m_eq = 0;
	m_pos = 0;
}


shape::shapetype quadric::getType() const {
	return shapetype::quadric;
}


FLOAT3 quadric::getNormal(const FLOAT3 &p) const {
	FLOAT3 relative{p - *m_pos}, normal{};
	normal.x = 2 * m_eq->A * relative.x + m_eq->E * relative.z + m_eq->F * relative.y + m_eq->G;
	normal.y = 2 * m_eq->B * relative.y + m_eq->D * relative.z + m_eq->F * relative.x + m_eq->H;
	normal.z = 2 * m_eq->C * relative.z + m_eq->D * relative.y + m_eq->E * relative.x + m_eq->I;
	return normal.normalize();
}


float quadric::intersectRay(const FLOAT3& cam, const FLOAT3& ray) const {
	FLOAT3 rCam, rRay, V1, V2, V3, V4, V5, V6, V7, V8;
	float A, B, C, root, D1, D2;
	
	// Calculate the positions of the camera and the ray relative to the quadric
	rCam = cam - *m_pos;
	rRay = ray;
	
	// Precalculate these values for our quadratic equation
	V1 = (rRay * rRay);
	V2 = 2 * FLOAT3{rRay.x * rRay.y, rRay.y * rRay.z, rRay.x * rRay.z};
	V3 = (rCam * rRay);
	V4 = FLOAT3{rRay.x * rCam.y + rCam.x * rRay.y, rCam.y * rRay.z + rRay.y * rCam.z, rCam.x * rRay.z + rRay.x * rCam.z};
	V5 = rRay;
	V6 = (rCam * rCam);
	V7 = 2 * FLOAT3{rCam.x * rCam.y, rCam.y * rCam.z, rCam.x * rCam.z};
	V8 = 2 * rCam;
	
	// Calculate the quadratic coefficients
	A = m_eq->ABC().dot(V1) + m_eq->DEF().dot(V2);
	B = m_eq->ABC().dot(V3) + m_eq->DEF().dot(V4) + m_eq->GHI().dot(V5);
	C = m_eq->ABC().dot(V6) + m_eq->DEF().dot(V7) + m_eq->GHI().dot(V8) + m_eq->J;
	
	// Calculate the root value for our quadratic formula
	root = (B * B) - (A * C);
	
	// No collision if the root is imaginary
	if (root < 0)
		return -1.0;
	
	// Take its root if it's real
	root = sqrtf(root);
	
	// Calculate both intersections
	D1 = (-B + root)/A;
	D2 = (-B - root)/A;
	
	// Return closest intersection
	if (D1 < D2)
		return D1;
	return D2;
}
