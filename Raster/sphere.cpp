//
//	sphere.cpp
//	Raster
//
//	Created by Matthew Dillard on 2/7/16.
//

#include "sphere.h"

sphere::sphere() {
	m_pos = 0;
	m_color = 0;
	m_radius = 0;
}

sphere::~sphere() {
	
}


bool sphere::initialize(const FLOAT3& p, const FLOAT3& c, const FLOAT3&, const float& r){
	m_pos = new FLOAT3(p);
	m_color = new FLOAT3(c);
	m_radius = new float(r);
	
	return true;
}

void sphere::shutdown() {
	delete m_pos;
	m_pos = 0;
	
	delete m_color;
	m_color = 0;
	
	delete m_radius;
	m_radius = 0;
}


shape::shapetype sphere::getType() const {
	return shape::shapetype::sphere;
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
