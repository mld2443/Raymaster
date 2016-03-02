//
//  scene.cpp
//  Raster
//
//  Created by Matthew Dillard on 2/28/16.
//

#include "scene.h"

scene::scene(const FLOAT3& ambientLight, const float& diffuseOffset):
	m_camera(0),
	m_shapes(new std::list<shape*>()),
	m_lights(new std::list<light*>()),
	m_ambientLight(new FLOAT3(ambientLight)),
	m_diffuseOffset(new float(diffuseOffset)) {}

scene::~scene() {
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
				
			case shape::quadric:
				delete (quadric*)s;
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
	
	if(m_camera)
		delete m_camera;
	m_camera = 0;
	
	delete m_ambientLight;
	m_ambientLight = 0;
	
	delete m_diffuseOffset;
	m_diffuseOffset = 0;
}


const camera* scene::getCamera() const {
	return m_camera;
}

FLOAT3 scene::getAmbientLight() const {
	return *m_ambientLight;
}

float scene::getDiffuseOffset() const {
	return *m_diffuseOffset;
}

const std::list<shape*>* scene::getShapes() const {
	return m_shapes;
}

const std::list<light*>* scene::getLights() const {
	return m_lights;
}


void scene::setCamera(camera* cam) {
	if (m_camera)
		delete m_camera;
	
	m_camera = cam;
}

void scene::setAmbientLight(const FLOAT3& ambient) {
	*m_ambientLight = ambient;
}

void scene::setDiffuseOffset(const float& offset) {
	*m_diffuseOffset = offset;
}


void scene::addShape(shape* s) {
	m_shapes->push_back(s);
}

void scene::addLight(light* l) {
	m_lights->push_back(l);
}


GLfloat* scene::capture() {
	return m_camera->capture(*m_ambientLight, *m_diffuseOffset);
}


scene::operator bool() const {
	return (m_camera && m_shapes->size());
}
