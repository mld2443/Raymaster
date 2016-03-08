//
//  spotlight.h
//  Raster
//
//  Created by Matthew Dillard on 3/2/16.
//

#ifndef spotlight_h
#define spotlight_h

#include <math.h>

#include "light.h"

class spotlight : public light {
public:
	spotlight(const RGBA& color, const FLOAT3& position, const FLOAT3& direction, const float& angle, const float& softAngle = 0.0f);
	~spotlight();
	
	lighttype getType() const;
	
	FLOAT3 normalToLight(const FLOAT3&) const;
	bool illuminated(const FLOAT3&) const;
	float distance(const FLOAT3&) const;
	
private:
	FLOAT3 *m_position, *m_direction;
	float *m_angle, *m_softAngle;
};

#endif /* spotlight_h */
