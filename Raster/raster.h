//
//	raster.h
//	Raster
//
//	Created by Matthew Dillard on 2/7/16.
//

#ifndef raster_h
#define raster_h

#ifdef __APPLE__
	#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
	#include <GLUT/glut.h>
#else
	#include <GL/glut.h>
#endif
#include <algorithm>
#include <random>
#include <math.h>
#include <list>

#include "camera.h"
#include "plane.h"
#include "sphere.h"
#include "cylinder.h"
#include "pointlight.h"
#include "directionlight.h"

class raster {
public:
	raster(const unsigned int& width, const unsigned int& height, camera* c, const FLOAT3& globalAmbient, const float& diffuseOffset);
	~raster();

	camera& getCamera() const;
	unsigned int getXRes() const;
	unsigned int getYRes() const;
	
	void addShape(shape*);
	void addLight(light*);
	
	GLfloat* render(const unsigned int&) const;

private:
	void castRay(GLfloat*, const FLOAT3&, const FLOAT3&, const FLOAT3&, const unsigned int&) const;
	FLOAT3 getColor(const shape*, const FLOAT3&, const FLOAT3&) const;
	
	std::default_random_engine *m_rng;
	std::uniform_real_distribution<float> *m_unif;
	std::list<shape*> *m_shapes;
	std::list<light*> *m_lights;
	camera *m_camera;
	FLOAT3 m_globalAmbient;
	unsigned int m_xRes, m_yRes;
	float m_offset;
};

#endif /* raster_h */
