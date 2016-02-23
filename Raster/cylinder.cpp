//
//  cylinder.cpp
//  Raster
//
//  Created by Matthew Dillard on 2/8/16.
//

#include "cylinder.h"

cylinder::cylinder(const FLOAT3& gc, const FLOAT3& ac, const FLOAT3& dc, const FLOAT3& sc, const float& s, const FLOAT3& p, const FLOAT3& d, const float& r) {
	m_glow = new FLOAT3(gc);
	m_ambient = new FLOAT3(ac);
	m_diffuse = new FLOAT3(dc);
	m_specular = new FLOAT3(sc);
	m_shininess = new float(s);
	m_pos = new FLOAT3(p);
	m_dir = new FLOAT3(d.normalize());
	m_radius = new float(r);
}

cylinder::~cylinder() {
	delete m_glow;
	m_glow = 0;
	
	delete m_ambient;
	m_ambient = 0;
	
	delete m_diffuse;
	m_diffuse = 0;
	
	delete m_specular;
	m_specular = 0;
	
	delete m_shininess;
	m_shininess = 0;
	
	delete m_pos;
	m_pos = 0;
	
	delete m_dir;
	m_dir = 0;
	
	delete m_radius;
	m_radius = 0;
}


shape::shapetype cylinder::getType() const {
	return shape::shapetype::cylinder;
}


FLOAT3 cylinder::getNormal(const FLOAT3 &p) const {
	return {};
}


float cylinder::intersectRay(const FLOAT3& eye, const FLOAT3& ray) const {
	//At^2 + Bt + C = 0
	// Δp = p - pa
	// term1 = (v − (v ⋅ va) va)
	// term2 = (Δp − (Δp ⋅ va) va)
	// A = (term1)^2
	// B = 2(term1 ⋅ term2)
	// C = (term2)^2 − r^2

	FLOAT3 deltaP, term1, term2;
	float A, B, C, root, D1, D2;
	
	deltaP = eye - *m_pos;
	term1 = ray - (*m_dir * m_dir->dot(ray));
	term2 = deltaP - (*m_dir * m_dir->dot(deltaP));
	
	A = term1.dot(term1);
	B = term1.dot(term2);
	C = term2.dot(term2) - (*m_radius * *m_radius);
	
	root = (B * B) - (A * C);
	
	if (root < 0)
		return -1.0;
	
	root = sqrtf(root);
	
	D1 = (-B + root)/A, D2 = (-B - root)/A;
	
	if (D1 < D2)
		return D1;
	return D2;
}
