//
//  camera.cpp
//  Raster
//
//  Created by Matthew Dillard on 2/22/16.
//

#include "camera.h"

camera::camera(const FLOAT3& p, const FLOAT3& d, const float& f, const float& l, const float& h, const FLOAT3& u) {
	m_pos = new FLOAT3(p);
	m_lookDir = new FLOAT3(d);
	m_xFOV = new float(f);
	m_lowFrustrum = new float(l);
	m_highFrustrum = new float(h);
	m_upDir = new FLOAT3(u);
	
	m_P00 = m_P10 = m_P01 = m_P11 = 0;
	m_deltaX = m_deltaY = 0;
}

camera::~camera() {
	delete m_pos;
	m_pos = 0;
	
	delete m_lookDir;
	m_lookDir = 0;
	
	delete m_xFOV;
	m_xFOV = 0;
	
	delete m_lowFrustrum;
	m_lowFrustrum = 0;
	
	delete m_highFrustrum;
	m_highFrustrum = 0;
	
	delete m_upDir;
	m_upDir = 0;
	
	if (m_P00) delete m_P00;
	if (m_P10) delete m_P10;
	if (m_P01) delete m_P01;
	if (m_P11) delete m_P11;
	m_P00 = m_P10 = m_P01 = m_P11 = 0;
	
	if (m_deltaX) delete m_deltaX;
	if (m_deltaY) delete m_deltaY;
	m_deltaX = m_deltaY = 0;
}


FLOAT3 camera::getPos() const {
	return *m_pos;
}

FLOAT3 camera::getLookDir() const{
	return *m_lookDir;
}

FLOAT3 camera::getUpDir() const {
	return *m_upDir;
}

FLOAT3 camera::getP00() const{
	return *m_P00;
}

FLOAT3 camera::getP10() const{
	return *m_P10;
}

FLOAT3 camera::getP01() const{
	return *m_P01;
}

FLOAT3 camera::getP11() const{
	return *m_P11;
}

FLOAT3 camera::getDeltaX() const{
	return *m_deltaX;
}

FLOAT3 camera::getDeltaY() const{
	return *m_deltaY;
}

float camera::getFOV() const{
	return *m_xFOV;
}

float camera::getLowFrust() const{
	return *m_lowFrustrum;
}

float camera::getHighFrust() const{
	return *m_highFrustrum;
}


void camera::updateViewport(const unsigned int w, const unsigned int h) {
	float uWidth, vHeight;
	
	uWidth = tanf((*m_xFOV / 2) * (M_PI / 180));
	vHeight = ((float)h / (float)w) * uWidth;
	
	if (m_deltaX || m_deltaY) {
		delete m_deltaX;
		delete m_deltaY;
	}
	
	m_deltaX = new FLOAT3(m_lookDir->cross(*m_upDir).normalize());
	m_deltaY = new FLOAT3(m_deltaX->cross(*m_lookDir).normalize());
	
	if (m_P00 || m_P10 || m_P01 || m_P11) {
		delete m_P00;
		delete m_P10;
		delete m_P01;
		delete m_P11;
	}
	
	m_P00 = new FLOAT3(*m_pos + *m_lookDir - (*m_deltaX * uWidth) - (*m_deltaY * vHeight));
	m_P10 = new FLOAT3(*m_pos + *m_lookDir + (*m_deltaX * uWidth) - (*m_deltaY * vHeight));
	m_P01 = new FLOAT3(*m_pos + *m_lookDir - (*m_deltaX * uWidth) + (*m_deltaY * vHeight));
	m_P11 = new FLOAT3(*m_pos + *m_lookDir + (*m_deltaX * uWidth) + (*m_deltaY * vHeight));
	
	*m_deltaX = (*m_P10 - *m_P00) / w;
	*m_deltaY = (*m_P01 - *m_P00) / h;
}
