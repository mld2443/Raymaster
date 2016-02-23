//
//	sphere.cpp
//	Raster
//
//	Created by Matthew Dillard on 2/7/16.
//

#include "sphere.h"

sphere::sphere(const FLOAT3& gc, const FLOAT3& ac, const FLOAT3& dc, const FLOAT3& sc, const float& s, const FLOAT3& p, const float& r) {
	m_glow = new FLOAT3(gc);
	m_ambient = new FLOAT3(ac);
	m_diffuse = new FLOAT3(dc);
	m_specular = new FLOAT3(sc);
	m_shininess = new float(s);
	m_pos = new FLOAT3(p);
	m_radius = new float(r);
}

sphere::~sphere() {
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
	
	delete m_radius;
	m_radius = 0;
}


shape::shapetype sphere::getType() const {
	return shape::shapetype::sphere;
}


FLOAT3 sphere::getNormal(const FLOAT3 &p) const {
	return (p - *m_pos).normalize();
}


float sphere::intersectRay(const FLOAT3& eye, const FLOAT3& ray) const {
	float b, c, rootval, root, d1, d2;
	
	FLOAT3 centervec = eye - *m_pos;
	
	b = ray.dot(centervec);
	c = centervec.dot(centervec) - (*m_radius * *m_radius);
	rootval = b * b - c;
	
	if (rootval < 0)
		return -1.0;
	
	root = sqrtf(rootval);
	
	d1 = -b + root, d2 = -b - root;
	
	if (d1 < d2)
		return d1;
	return d2;
}
