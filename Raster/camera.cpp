//
//  camera.cpp
//  Raster
//
//  Created by Matthew Dillard on 2/22/16.
//

#include "camera.h"

camera::camera(const unsigned int& xRes, const unsigned int& yRes,
			   const FLOAT3& position, const FLOAT3& normal,
			   const float& FOV,
			   const float& nearClip, const float& farClip,
			   const std::list<shape*> *shapelist,
			   const std::list<light*> *lightlist,
			   const unsigned int& antialiasing,
			   const FLOAT3& up):
	m_xRes(new unsigned int(xRes)), m_yRes(new unsigned int(yRes)),
	m_pos(new FLOAT3(position)), m_normal(new FLOAT3(normal.normalize())),
	m_xFOV(new float(FOV)),
	m_nearClip(new float(nearClip)), m_farClip(new float(farClip)),
	shapes(shapelist),
	lights(lightlist),
	m_antialiasing(new unsigned int(antialiasing)),
	m_upDir(new FLOAT3(up.normalize())),
	
	m_P00(0), m_P10(0), m_P01(0), m_P11(0),
	m_deltaX(0), m_deltaY(0),
	
	m_rng(new std::default_random_engine()),
	m_unif(new std::uniform_real_distribution<float>(0, 1)) {}

camera::~camera() {
	delete m_xRes;
	delete m_yRes;
	m_xRes = m_yRes = 0;
	
	delete m_pos;
	delete m_normal;
	delete m_upDir;
	m_pos = m_normal = m_upDir = 0;
	
	if (m_P00) delete m_P00;
	if (m_P10) delete m_P10;
	if (m_P01) delete m_P01;
	if (m_P11) delete m_P11;
	m_P00 = m_P10 = m_P01 = m_P11 = 0;
	
	if (m_deltaX) delete m_deltaX;
	if (m_deltaY) delete m_deltaY;
	m_deltaX = m_deltaY = 0;
	
	delete m_xFOV;
	delete m_nearClip;
	delete m_farClip;
	m_xFOV = m_nearClip = m_farClip = 0;
	
	delete m_rng;
	delete m_unif;
	m_rng = 0;
	m_unif = 0;
}


FLOAT3 camera::getPos() const {
	return *m_pos;
}

FLOAT3 camera::getNormal() const{
	return *m_normal;
}

unsigned int camera::getXRes() const {
	return *m_xRes;
}

unsigned int camera::getYRes() const {
	return *m_yRes;
}


void camera::setPos(const FLOAT3& position) {
	*m_pos = position;
}

void camera::setNormal(const FLOAT3& normal) {
	*m_normal = normal;
}

GLfloat* camera::capture(const FLOAT3& ambientLight, const float& diffuseOffset){
	unsigned long pixindex = 0;
	GLfloat *pixels = new GLfloat[*m_xRes * *m_yRes * 3];
	FLOAT3 vRay, hRay;
	
	updateViewport();
	
	vRay = *m_P00;
	
	for (int j = 0; j < *m_yRes; ++j) {
		hRay = vRay;
		for (int i = 0; i < *m_xRes; ++i) {
			// background color
			pixels[pixindex] = 0.0f;
			pixels[pixindex+1] = 0.0f;
			pixels[pixindex+2] = 0.0f;
			
			castRay(pixels + pixindex, hRay, ambientLight, diffuseOffset);
			
			// increments
			hRay += *m_deltaX;
			pixindex += 3;
		}
		vRay += *m_deltaY;
	}
	
	return pixels;
}


void camera::updateViewport() {
	float uWidth, vHeight;
	
	uWidth = tanf((*m_xFOV / 2.0f) * (M_PI / 180.0f));
	vHeight = ((float)*m_yRes / (float)*m_xRes) * uWidth;
	
	if (m_deltaX || m_deltaY) {
		delete m_deltaX;
		delete m_deltaY;
	}
	
	m_deltaX = new FLOAT3(m_normal->cross(*m_upDir).normalize());
	m_deltaY = new FLOAT3(m_deltaX->cross(*m_normal).normalize());
	
	if (m_P00 || m_P10 || m_P01 || m_P11) {
		delete m_P00;
		delete m_P10;
		delete m_P01;
		delete m_P11;
	}
	
	m_P00 = new FLOAT3(*m_pos + *m_normal - (*m_deltaX * uWidth) - (*m_deltaY * vHeight));
	m_P10 = new FLOAT3(*m_pos + *m_normal + (*m_deltaX * uWidth) - (*m_deltaY * vHeight));
	m_P01 = new FLOAT3(*m_pos + *m_normal - (*m_deltaX * uWidth) + (*m_deltaY * vHeight));
	m_P11 = new FLOAT3(*m_pos + *m_normal + (*m_deltaX * uWidth) + (*m_deltaY * vHeight));
	
	*m_deltaX = (*m_P10 - *m_P00) / (float)*m_xRes;
	*m_deltaY = (*m_P01 - *m_P00) / (float)*m_yRes;
}

void camera::castRay(GLfloat *pixel, const FLOAT3& origin, const FLOAT3& ambientLight, const float& diffuseOffset) const {
	for (int samples = 0; samples < *m_antialiasing; ++samples) {
		float r1, r2, zValue;
		FLOAT3 sample, ray, color;
		shape *closest = 0;
		
		r1 = (*m_unif)(*m_rng), r2 = (*m_unif)(*m_rng);
		
		sample = origin + (*m_deltaY * r1) + (*m_deltaX * r2);
		ray = (sample - *m_pos).normalize();
		
		zValue = *m_farClip;
		color = {0.0f, 0.0f, 0.0f};
		
		for (shape *s : *shapes) {
			float intersect = s->intersectRay(*m_pos, ray);
			if (intersect > *m_nearClip && intersect < zValue) {
				zValue = intersect;
				closest = s;
			}
		}
		
		color = getColor(closest, *m_pos + (ray * zValue), -ray, ambientLight, diffuseOffset);
		
		pixel[0] += color.x;
		pixel[1] += color.y;
		pixel[2] += color.z;
	}
	
	pixel[0] /= float(*m_antialiasing);
	pixel[1] /= float(*m_antialiasing);
	pixel[2] /= float(*m_antialiasing);
}

FLOAT3 camera::getColor(const shape *s, const FLOAT3& point, const FLOAT3& toEye, const FLOAT3& ambientLight, const float& diffuseOffset) const {
	FLOAT3 glow{}, ambient{}, diffuse{}, specular{}, directionToLight{};
	
	glow = s->getGlow();
	
	ambient = ambientLight * s->getAmbient();
	
	for (light *l : *lights) {
		directionToLight = l->normalToLight(point);
		
		if (l->illuminated(point) && !obstructed(s, point, directionToLight, l)) {
			float product = s->getNormal(point).dot(directionToLight);
			float calculatedOffset = (product + diffuseOffset)/(1 + diffuseOffset);
			
			diffuse += s->getDiffuse() * l->getColor() * std::max(calculatedOffset, 0.0f);
			
			if (product > 0.0f) {
				FLOAT3 halfway = (toEye + l->normalToLight(point)).normalize();
				float value = (s->getNormal(point)).dot(halfway);
				specular += s->getSpecular() * l->getColor() * pow(std::max(value, 0.0f), s->getShininess());
			}
		}
	}
	
	return glow + ambient + diffuse + specular;
}

bool camera::obstructed(const shape* object, const FLOAT3& point, const FLOAT3& directionToLight, const light* source) const {
	float distanceToLight(source->distance(point));
	
	for (shape *s : *shapes) {
		if (s != object) {
			float intersect = s->intersectRay(point, directionToLight);
			if (intersect > 0.0 && intersect < distanceToLight)
				return true;
		}
	}
	
	return false;
}
