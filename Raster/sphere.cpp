//
//	sphere.cpp
//	Raster
//
//	Created by Matthew Dillard on 2/7/16.
//

#include "sphere.h"

sphere::sphere(const colordata& colors,
			   const FLOAT3& pos,
			   const float& radius) : quadric(colors, pos, {1,1,1,0,0,0,0,0,0,-radius}) {}

sphere::~sphere() {
	delete m_colors;
	delete m_pos;
	delete m_eq;
	
	m_colors = 0;
	m_eq = 0;
	m_pos = 0;
}


shape::shapetype sphere::getType() const {
	return shapetype::sphere;
}
