//
//	plane.cpp
//	Raster
//
//	Created by Matthew Dillard on 2/7/16.
//

#include "plane.h"

plane::plane(const FLOAT3& gc, const FLOAT3& ac, const FLOAT3& dc, const FLOAT3& sc, const float& s, const FLOAT3& p, const FLOAT3& n) {
	m_glow = new FLOAT3(gc);
	m_ambient = new FLOAT3(ac);
	m_diffuse = new FLOAT3(dc);
	m_specular = new FLOAT3(sc);
	m_shininess = new float(s);
	m_pos = new FLOAT3(p);
	m_dir = new FLOAT3(n.normalize());
	m_radius = new float(n.dot(p));
}

plane::~plane() {
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


shape::shapetype plane::getType() const {
	return shape::shapetype::plane;
}


FLOAT3 plane::getNormal(const FLOAT3&) const {
	return *m_dir;
}


float plane::intersectRay(const FLOAT3& eye, const FLOAT3& ray) const {
	return (*m_radius - m_dir->dot(eye)) / (m_dir->dot(ray));
}
