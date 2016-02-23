//
//	raster.cpp
//	Raster
//
//	Created by Matthew Dillard on 2/7/16.
//

#include "raster.h"

raster::raster(const unsigned int& x, const unsigned int& y, camera* c, const FLOAT3& ga, const float& os) {
	m_shapes = new std::list<shape*>();
	m_lights = new std::list<light*>();
	m_xRes = x;
	m_yRes = y;
	m_camera = c;
	m_globalAmbient = ga;
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


camera& raster::getCamera() const {
	return *m_camera;
}

unsigned int raster::getXRes() const {
	return m_xRes;
}

unsigned int raster::getYRes() const {
	return m_yRes;
}


void raster::addShape(shape *s) {
	m_shapes->push_back(s);
}

void raster::addLight(light *l) {
	m_lights->push_back(l);
}


GLfloat* raster::render(const unsigned int& AA) const {
	unsigned long pixindex = 0;
	GLfloat *pixels = new GLfloat[m_xRes * m_yRes * 3];
	FLOAT3 vRay, hRay;
	
	m_camera->updateViewport(m_xRes, m_yRes);
	
	vRay = m_camera->getP00();
	
	for (int j = 0; j < m_yRes; ++j) {
		hRay = vRay;
		for (int i = 0; i < m_xRes; ++i) {
			// background color
			pixels[pixindex] = 0.0;
			pixels[pixindex+1] = 0.0;
			pixels[pixindex+2] = 0.0;
			
			castRay(pixels + pixindex, hRay, m_camera->getDeltaX(), m_camera->getDeltaY(), AA);
			
			// increments
			hRay += m_camera->getDeltaX();
			pixindex += 3;
		}
		vRay += m_camera->getDeltaY();
	}
	
	return pixels;
}


void raster::castRay(GLfloat *pixel, const FLOAT3& orig, const FLOAT3& uInc, const FLOAT3& vInc, const unsigned int& AA) const {
	for (int samples = 0; samples < AA; ++samples) {
		float r1, r2, zValue;
		FLOAT3 sample, ray, color;
		
		r1 = (*m_unif)(*m_rng), r2 = (*m_unif)(*m_rng);
		
		sample = orig + (vInc * r1) + (uInc * r2);
		ray = (sample - m_camera->getPos()).normalize();
		
		zValue = m_camera->getHighFrust();
		color = {0.0, 0.0, 0.0};
		
		for (shape *s : *m_shapes) {
			float intersect = s->intersectRay(m_camera->getPos(), ray);
			if (intersect > m_camera->getLowFrust() && intersect < zValue) {
				zValue = intersect;
				color = getColor(s, m_camera->getPos() + (ray * intersect), -ray);
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
