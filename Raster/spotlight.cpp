//
//  spotlight.c
//  Raster
//
//  Created by Matthew Dillard on 3/2/16.
//

#include "spotlight.h"

spotlight::spotlight(const RGBA& color, const FLOAT3& position, const FLOAT3& direction, const float& angle, const float& softAngle) {
	m_color = new RGBA(color);
	m_position = new FLOAT3(position);
	m_direction = new FLOAT3(direction.normalize());
	m_angle = new float(angle);
	m_softAngle = new float(softAngle);
}

spotlight::~spotlight() {
	delete m_color;
	m_color = 0;
	
	delete m_position;
	delete m_direction;
	m_position = m_direction = 0;
	
	delete m_angle;
	delete m_softAngle;
	m_angle = m_softAngle = 0;
}


light::lighttype spotlight::getType() const {
	return spot;
}


FLOAT3 spotlight::normalToLight(const FLOAT3& p) const {
	return (*m_position - p).normalize();
}

bool spotlight::illuminated(const FLOAT3& point) const{
	FLOAT3 pointRay((point - *m_position).normalize());
	
	float angleBetween = acosf(m_direction->dot(pointRay))  * (180.0f / M_PI);
	
	return angleBetween <= *m_angle;
}

float spotlight::distance(const FLOAT3& point) const {
	return (*m_position - point).len();
}
