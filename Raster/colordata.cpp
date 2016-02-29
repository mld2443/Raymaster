//
//  color.cpp
//  Raster
//
//  Created by Matthew Dillard on 2/28/16.
//

#include "colordata.h"

colordata::colordata(const FLOAT3& amb, const FLOAT3& dif, const FLOAT3& spe, const float& shi, const FLOAT3& glo) {
	m_ambient = new FLOAT3(amb);
	m_diffuse = new FLOAT3(dif);
	m_specular = new FLOAT3(spe);
	m_shininess = new float(shi);
	m_glow = new FLOAT3(glo);
}

colordata::~colordata() {
	delete m_ambient;
	delete m_diffuse;
	delete m_specular;
	delete m_shininess;
	delete m_glow;
	
	m_ambient = 0;
	m_diffuse = 0;
	m_specular = 0;
	m_shininess = 0;
	m_glow = 0;
}


FLOAT3 colordata::getAmbient() const {
	return *m_ambient;
}

FLOAT3 colordata::getDiffuse() const {
	return *m_diffuse;
}

FLOAT3 colordata::getSpecular() const{
	return *m_specular;
}

float colordata::getShininess() const{
	return *m_shininess;
}

FLOAT3 colordata::getGlow() const{
	return *m_glow;
}
