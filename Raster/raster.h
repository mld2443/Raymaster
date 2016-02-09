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
#include <random>
#include <math.h>
#include <list>

#include "plane.h"
#include "sphere.h"
#include "cylinder.h"

class raster {
public:
	raster();
	~raster();

	bool initialize(const FLOAT3&, const FLOAT3&, const float&, const float&, const float&);
	void shutdown();

	void setEyePos(const FLOAT3&);
	void setLookDir(const FLOAT3&);
	void setFOV(const float&);

	FLOAT3 getEyePos() const;
	FLOAT3 getLookDir() const;
	float getFOV() const;
	
	void addShape(shape*);
	
	GLfloat* render(const int&, const int&, const unsigned int&) const;

private:
	void castRay(GLfloat*, const FLOAT3&, const FLOAT3&, const FLOAT3&, const unsigned int&) const;
	
	std::default_random_engine *m_rng;
	std::uniform_real_distribution<float> *m_unif;
	std::list<shape*> *m_shapes;
	FLOAT3 m_eyePos, m_eyeDir;
	float m_fovX, m_lowFrustrum, m_highFrustrum;
};

#endif /* raster_h */
