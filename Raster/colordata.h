//
//  color.h
//  Raster
//
//  Created by Matthew Dillard on 2/28/16.
//

#ifndef color_h
#define color_h

#include "float3.h"

class colordata {
public:
	colordata(const FLOAT3& ambient = {}, const FLOAT3& diffuse = {}, const FLOAT3& specular = {}, const float& shininess = 0.0, const FLOAT3& glow = {});
	~colordata();
	
	FLOAT3 getAmbient() const;
	FLOAT3 getDiffuse() const;
	FLOAT3 getSpecular() const;
	float getShininess() const;
	FLOAT3 getGlow() const;
	
private:
	FLOAT3 *m_ambient, *m_diffuse, *m_specular, *m_glow;
	float *m_shininess;
};

#endif /* color_h */
