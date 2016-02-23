//
//	shape.cpp
//	Raster
//
//	Created by Matthew Dillard on 2/7/16.
//

#include "shape.h"

FLOAT3 shape::getGlow() const {
	return *m_glow;
}

FLOAT3 shape::getAmbient() const {
	return *m_ambient;
}

FLOAT3 shape::getDiffuse() const {
	return *m_diffuse;
}

FLOAT3 shape::getSpecular() const {
	return *m_specular;
}

float shape::getShininess() const {
	return *m_shininess;
}

FLOAT3 shape::getPos() const {
	return *m_pos;
}

FLOAT3 shape::getDir() const {
	return *m_dir;
}

float shape::getRadius() const {
	return *m_radius;
}
