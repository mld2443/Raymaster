//
//	raster.cpp
//	Raster
//
//	Created by Matthew Dillard on 2/7/16.
//

#include "raster.h"

raster::raster() {
	m_rng = 0;
	m_unif = 0;
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
	
	m_rng = new std::default_random_engine();
	m_unif = new std::uniform_real_distribution<float>(0, 1);
	
	return true;
}

void raster::shutdown() {
	delete m_rng;
	m_rng = 0;
	
	delete m_unif;
	m_unif = 0;
	
	for (shape *s : *m_shapes) {
		switch (s->getType()) {
			case shape::plane:
				delete (plane*)s;
				break;
				
			case shape::sphere:
				delete (sphere*)s;
				break;
				
			case shape::cylinder:
				delete (cylinder*)s;
				break;
				
			default:
				break;
		}
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


GLfloat* raster::render(const int& w, const int& h, const unsigned int& AA) const {
	unsigned long pixindex;
	GLfloat *pixels = new GLfloat[w * h * 3];
	FLOAT3 vRay, hRay, rightDir, upDir, rightInc, upInc, P00, P10, P01, P11;
	float fovY, uWidth, vHeight;
	
	pixindex = 0;

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
			// background color
			pixels[pixindex] = 0.0;
			pixels[pixindex+1] = 0.0;
			pixels[pixindex+2] = 0.0;
			
			castRay(pixels + pixindex, hRay, rightInc, upInc, AA);
			
			// increments
			hRay += rightInc;
			pixindex += 3;
		}
		vRay += upInc;
	}
	
	return pixels;
}


void raster::castRay(GLfloat *pixel, const FLOAT3& orig, const FLOAT3& uInc, const FLOAT3& vInc, const unsigned int& AA) const {
	for (int samples = 0; samples < AA; ++samples) {
		float r1, r2, zValue;
		FLOAT3 sample, ray, color;
		
		r1 = (*m_unif)(*m_rng), r2 = (*m_unif)(*m_rng);
		
		sample = orig + (vInc * r1) + (uInc * r2);
		ray = (sample - m_eyePos).normalize();
		
		zValue = m_highFrustrum;
		color = {0.0, 0.0, 0.0};
		
		for (shape *s : *m_shapes) {
			float intersect = s->intersectRay(m_eyePos, ray);
			if (intersect > m_lowFrustrum && intersect < zValue) {
				zValue = intersect;
				color = s->getColor();
			}
		}
		
		pixel[0] += color.x;
		pixel[1] += color.y;
		pixel[2] += color.z;
	}
	
	pixel[0] /= float(AA);
	pixel[1] /= float(AA);
	pixel[2] /= float(AA);
}
