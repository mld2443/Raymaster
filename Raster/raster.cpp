//
//	raster.cpp
//	Raster
//
//	Created by Matthew Dillard on 2/7/16.
//

#include "raster.h"

raster::raster(const FLOAT3& p, const FLOAT3& d, const FLOAT3& ga, const float& f, const float& low, const float& high, const float& os) {
	m_shapes = new std::list<shape*>();
	m_lights = new std::list<light*>();
	m_eyePos = p;
	m_eyeDir = d.normalize();
	m_globalAmbient = ga;
	m_fovX = f;
	m_lowFrustrum = low;
	m_highFrustrum = high;
	m_offset = os;
	
	m_rng = new std::default_random_engine();
	m_unif = new std::uniform_real_distribution<float>(0, 1);
}

raster::~raster() {
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
	
	for (light *l : *m_lights) {
		switch (l->getType()) {
			case light::point:
				delete (pointlight*)l;
				break;
				
			case light::directional:
				delete (directionlight*)l;
				break;
				
			default:
				break;
		}
		l = 0;
	}
	
	m_lights->clear();
	delete m_lights;
	m_lights = 0;
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

void raster::addLight(light *l) {
	m_lights->push_back(l);
}


GLfloat* raster::render(const unsigned int& w, const unsigned int& h, const unsigned int& AA) const {
	unsigned long pixindex;
	GLfloat *pixels = new GLfloat[w * h * 3];
	FLOAT3 vRay, hRay, rightDir, upDir, P00, P10, P01;
	float uWidth, vHeight;
	
	pixindex = 0;
	
	FLOAT3 up{0,1,0};
	
	rightDir = m_eyeDir.cross(up).normalize();
	upDir = rightDir.cross(m_eyeDir).normalize();
	
	uWidth = tanf((m_fovX / 2) * (M_PI / 180));
	vHeight = ((float)h / (float)w) * uWidth;
	
	P00 = m_eyePos + m_eyeDir - (rightDir * uWidth) - (upDir * vHeight);
	P10 = m_eyePos + m_eyeDir + (rightDir * uWidth) - (upDir * vHeight);
	P01 = m_eyePos + m_eyeDir - (rightDir * uWidth) + (upDir * vHeight);
	
	rightDir = (P10 - P00) / w;
	upDir = (P01 - P00) / h;
	
	vRay = P00;
	
	for (int j = 0; j < h; ++j) {
		hRay = vRay;
		for (int i = 0; i < w; ++i) {
			// background color
			pixels[pixindex] = 0.0;
			pixels[pixindex+1] = 0.0;
			pixels[pixindex+2] = 0.0;
			
			castRay(pixels + pixindex, hRay, rightDir, upDir, AA);
			
			// increments
			hRay += rightDir;
			pixindex += 3;
		}
		vRay += upDir;
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
				color = getColor(s, m_eyePos + (ray * intersect), -ray);
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

FLOAT3 raster::getColor(const shape *s, const FLOAT3& point, const FLOAT3& toEye) const {
	FLOAT3 glow, ambient, diffuse = {}, specular = {};
	
	glow = s->getGlow();
	
	ambient = m_globalAmbient * s->getAmbient();
	
	for (light *l : *m_lights) {
		float product = s->getNormal(point).dot(l->normalToLight(point));
		float offsetProduct = (product + m_offset)/(1 + m_offset);
		
		diffuse += s->getDiffuse() * l->getColor() * std::max(offsetProduct, 0.0f);
		
		if (product > 0.0) {
			FLOAT3 halfway = (toEye + l->normalToLight(point)).normalize();
			float value = (s->getNormal(point)).dot(halfway);
			specular += s->getSpecular() * l->getColor() * pow(std::max(value, 0.0f), s->getShininess());
		}
	}
	
	return glow + ambient + diffuse + specular;
}
