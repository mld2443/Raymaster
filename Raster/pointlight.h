//
//  pointlight.h
//  Raster
//
//  Created by Matthew Dillard on 2/22/16.
//

#ifndef pointlight_h
#define pointlight_h

#include "light.h"

class pointlight : public light {
public:
	pointlight(const RGBA& color, const FLOAT3& position);
	~pointlight();
	
	lighttype getType() const;
	
	FLOAT3 normalToLight(const FLOAT3&) const;
	bool illuminated(const FLOAT3&) const;
	float distance(const FLOAT3&) const;
	
private:
	FLOAT3 *m_position;
};

#endif /* pointlight_h */
