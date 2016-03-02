//
//  scene.h
//  Raster
//
//  Created by Matthew Dillard on 2/28/16.
//

#ifndef scene_h
#define scene_h

#ifdef __APPLE__
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <list>
#include <map>

#include "camera.h"
#include "plane.h"
#include "sphere.h"
#include "cylinder.h"
#include "pointlight.h"
#include "directionlight.h"

class scene {
public:
	scene(const FLOAT3& ambientLight = {}, const float& diffuseOffset = 0.0);
	~scene();
	
	const camera* getCamera() const;
	FLOAT3 getAmbientLight() const;
	float getDiffuseOffset() const;
	const std::list<shape*>* getShapes() const;
	const std::list<light*>* getLights() const;
	
	void setCamera(camera*);
	void setAmbientLight(const FLOAT3&);
	void setDiffuseOffset(const float&);
	
	void addShape(shape*);
	void addLight(light*);
	
	GLfloat* capture();
	
	operator bool() const;
	
private:
	camera *m_camera;
	std::list<shape*> *m_shapes;
	std::list<light*> *m_lights;
	FLOAT3 *m_ambientLight;
	float *m_diffuseOffset;
};

#endif /* scene_h */
