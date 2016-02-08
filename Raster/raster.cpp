//
//	raster.cpp
//	Raster
//
//	Created by Matthew Dillard on 2/7/16.
//

#include "raster.h"

raster::raster() {
	m_shapes = 0;
}

raster::~raster() {
	
}


bool raster::initialize(const FLOAT3& p, const FLOAT3& d, const float& f, const float& low, const float& high) {
	m_shapes = new std::list<shape*>();
	m_eyePos = p;
	m_eyeDir = d.normalize();
	m_fovX = f;
	m_lowFrustrum = low;
	m_highFrustrum = high;
	
	if (low > high)
		return false;
	
	return true;
}

void raster::shutdown() {
	for (shape *s : *m_shapes) {
		s->shutdown();
		delete s;
		s = 0;
	}
	
	m_shapes->clear();
	delete m_shapes;
	m_shapes = 0;
}


void raster::setEyePos(const FLOAT3& p) {
	m_eyePos = p;
}

void raster::setLookDir(const FLOAT3& d) {
	m_eyeDir = d;
}

void raster::setFOV(const float& f) {
	m_fovX = f;
}


FLOAT3 raster::getEyePos() const {
	return m_eyePos;
}

FLOAT3 raster::getLookDir() const {
	return m_eyeDir;
}

float raster::getFOV() const {
	return m_fovX;
}


void raster::addShape(shape *s) {
	m_shapes->push_back(s);
}


/*void setpixel(GLubyte *pixels, const int size, const int x, const int y, const int c, const GLubyte val) {
	pixels[((size*y)+x)*3+c] = val;
}*/


GLubyte* raster::render(const int& w, const int& h, const unsigned int& AA) const {
	GLubyte *pixels = new GLubyte[w * h * 3];
	FLOAT3 vRay, hRay, rightDir, upDir, rightInc, upInc, P00, P10, P01, P11;
	float fovY, uWidth, vHeight;

	fovY = (h / w) * m_fovX;
	
	rightDir = m_eyeDir.cross({0,0,1}).normalize();
	upDir = rightDir.cross(m_eyeDir).normalize();
	
	uWidth = tanf((m_fovX / 2) * (M_PI / 180));
	vHeight = tanf((fovY / 2) * (M_PI / 180));
	
	P00 = m_eyePos + m_eyeDir - (rightDir * uWidth) - (upDir * vHeight);
	P10 = m_eyePos + m_eyeDir + (rightDir * uWidth) - (upDir * vHeight);
	P01 = m_eyePos + m_eyeDir - (rightDir * uWidth) + (upDir * vHeight);
	P11 = m_eyePos + m_eyeDir + (rightDir * uWidth) + (upDir * vHeight);
	
	rightInc = (P01 - P00) / (h + 1);
	upInc = (P10 - P00) / (w + 1);
	
	vRay = P00;
	
	for (int j = 0; j < h; ++j) {
		hRay = vRay;
		for (int i = 0; i < w; ++i) {
			//setpixel(pixels, w, i, j, 0, 127);
			
			
			
			hRay += rightInc;
		}
		vRay += upInc;
	}
	
	
	return pixels;
}
