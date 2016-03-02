//
//  directionlight.h
//  Raster
//
//  Created by Matthew Dillard on 2/22/16.
//

#ifndef directionlight_h
#define directionlight_h

#include "light.h"

class directionlight : public light {
public:
	directionlight(const FLOAT3& color, const FLOAT3& normal);
	~directionlight();
	
	lighttype getType() const;
	
	FLOAT3 normalToLight(const FLOAT3&) const;
	bool illuminated(const FLOAT3&) const;
	
private:
	FLOAT3 *m_normal;
};

#endif /* directionlight_h */
