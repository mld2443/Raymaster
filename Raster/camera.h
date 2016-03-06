//
//  camera.h
//  Raster
//
//  Created by Matthew Dillard on 2/22/16.
//

#ifndef camera_h
#define camera_h

#ifdef __APPLE__
	#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
	#include <GLUT/glut.h>
#else
	#include <GL/glut.h>
#endif
#include <random>
#include <vector>
#include <list>

#include "threadpool.h"
#include "shape.h"
#include "light.h"

#define THREADPOOLSIZE 4

class camera {
public:
	camera(const unsigned int& xRes, const unsigned int& yRes,
		   const FLOAT3& pos, const FLOAT3& lookDir,
		   const float& xFOV,
		   const float& nearClip, const float& farClip,
		   const std::list<shape*> *shapelist,
		   const std::list<light*> *lightlist,
		   const unsigned int& antialiasing = 16,
		   const FLOAT3& up = {0,1,0});
	~camera();
	
	FLOAT3 getPos() const;
	FLOAT3 getNormal() const;
	unsigned int getXRes() const;
	unsigned int getYRes() const;
	
	void setPos(const FLOAT3&);
	void setNormal(const FLOAT3&);
	
	GLfloat* capture(const FLOAT3&, const float&);
	
private:
	void updateViewport();
	
	FLOAT3 castRays(const FLOAT3&, const FLOAT3&, const float&) const;
	FLOAT3 getColor(const shape*, const FLOAT3&, const FLOAT3&, const FLOAT3&, const float&) const;
	bool obstructed(const shape*, const FLOAT3&, const FLOAT3&, const light*) const;
	
	unsigned int *m_xRes, *m_yRes, *m_antialiasing;
	FLOAT3 *m_pos, *m_normal, *m_upDir, *m_P00, *m_P10, *m_P01, *m_P11, *m_deltaX, *m_deltaY;
	float *m_xFOV, *m_nearClip, *m_farClip;
	
	const std::list<shape*> *shapes;
	const std::list<light*> *lights;
	
	std::default_random_engine *m_rng;
	std::uniform_real_distribution<float> *m_unif;
};

#endif /* camera_h */
