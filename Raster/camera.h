//
//  camera.h
//  Raster
//
//  Created by Matthew Dillard on 2/22/16.
//

#ifndef camera_h
#define camera_h

#include "float3.h"

class camera {
public:
	camera(const FLOAT3& pos, const FLOAT3& lookDir, const float& xFOV, const float& nearClip, const float& farClip, const FLOAT3& up = {0,1,0});
	~camera();
	
	FLOAT3 getPos() const;
	FLOAT3 getLookDir() const;
	FLOAT3 getUpDir() const;
	FLOAT3 getP00() const;
	FLOAT3 getP10() const;
	FLOAT3 getP01() const;
	FLOAT3 getP11() const;
	FLOAT3 getDeltaX() const;
	FLOAT3 getDeltaY() const;
	float getFOV() const;
	float getLowFrust() const;
	float getHighFrust() const;
	
	void updateViewport(const unsigned int width, const unsigned int height);
	
private:
	FLOAT3 *m_pos, *m_lookDir, *m_upDir, *m_P00, *m_P10, *m_P01, *m_P11, *m_deltaX, *m_deltaY;
	float *m_xFOV, *m_lowFrustrum, *m_highFrustrum;
};

#endif /* camera_h */
