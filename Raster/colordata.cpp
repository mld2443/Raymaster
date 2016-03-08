//
//  color.cpp
//  Raster
//
//  Created by Matthew Dillard on 2/28/16.
//

#include "colordata.h"

colordata::colordata(const RGBA& amb, const RGBA& dif, const RGBA& spe, const float& shi, const RGBA& glo) {
	m_ambient = new RGBA(amb);
	m_diffuse = new RGBA(dif);
	m_specular = new RGBA(spe);
	m_shininess = new float(shi);
	m_glow = new RGBA(glo);
}

colordata::colordata(const colordata& c):
	m_ambient(new RGBA(*c.m_ambient)),
	m_diffuse(new RGBA(*c.m_diffuse)),
	m_specular(new RGBA(*c.m_specular)),
	m_shininess(new float(*c.m_shininess)),
	m_glow(new RGBA(*c.m_glow)) {}

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


RGBA colordata::getAmbient() const {
	return *m_ambient;
}

RGBA colordata::getDiffuse() const {
	return *m_diffuse;
}

RGBA colordata::getSpecular() const{
	return *m_specular;
}

float colordata::getShininess() const{
	return *m_shininess;
}

RGBA colordata::getGlow() const{
	return *m_glow;
}
