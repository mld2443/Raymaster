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

#include "shape.h"
#include "scene.h"

class camera {
public:
	camera(const unsigned int& xRes, const unsigned int& yRes,
		   const FLOAT3& pos, const FLOAT3& lookDir,
		   const float& xFOV,
		   const float& nearClip, const float& farClip,
		   const unsigned int& antialiasing = 16,
		   const FLOAT3& up = {0,1,0});
	~camera();
	
	FLOAT3 getPos() const;
	FLOAT3 getNormal() const;
	
	void setPos(const FLOAT3&);
	void setNormal(const FLOAT3&);
	
	GLfloat* capture(const scene*);
	
private:
	void updateViewport();
	void castRay(GLfloat*, const FLOAT3&, const scene*) const;
	FLOAT3 getColor(const shape*, const FLOAT3&, const FLOAT3&, const scene*) const;
	
	unsigned int *m_xRes, *m_yRes, *m_antialiasing;
	FLOAT3 *m_pos, *m_normal, *m_upDir, *m_P00, *m_P10, *m_P01, *m_P11, *m_deltaX, *m_deltaY;
	float *m_xFOV, *m_nearClip, *m_farClip;
	
	std::default_random_engine *m_rng;
	std::uniform_real_distribution<float> *m_unif;
};

#endif /* camera_h */
