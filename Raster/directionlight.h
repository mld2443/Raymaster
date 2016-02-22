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
	directionlight(const FLOAT3& color, const FLOAT3& direction);
	~directionlight();
	
	lighttype getType() const;
};

#endif /* directionlight_h */
