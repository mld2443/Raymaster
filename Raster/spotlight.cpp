//
//  spotlight.c
//  Raster
//
//  Created by Matthew Dillard on 3/2/16.
//

#include "spotlight.h"

spotlight::spotlight(const FLOAT3& color, const FLOAT3& position, const FLOAT3& direction, const float& angle) {
	m_color = new FLOAT3(color);
	m_position = new FLOAT3(position);
	m_direction = new FLOAT3(direction.normalize());
	m_angle = new float(angle);
}

spotlight::~spotlight() {
	delete m_color;
	delete m_position;
	
	m_color = 0;
	m_position = 0;
}


light::lighttype spotlight::getType() const {
	return point;
}


FLOAT3 spotlight::normalToLight(const FLOAT3& p) const {
	return (*m_position - p).normalize();
}

bool spotlight::illuminated(const FLOAT3& point) const{
	FLOAT3 pointRay((point - *m_position).normalize());
	
	float angleBetween = acosf(m_direction->dot(pointRay))  * (180.0f / M_PI);
	
	return angleBetween <= *m_angle;
}
