//
//  color.h
//  Raster
//
//  Created by Matthew Dillard on 2/28/16.
//

#ifndef color_h
#define color_h

#include "rgba.h"

class colordata {
public:
	colordata(const RGBA& ambient = {}, const RGBA& diffuse = {}, const RGBA& specular = {}, const float& shininess = 0.0, const RGBA& glow = {});
	colordata(const colordata&);
	~colordata();
	
	RGBA getAmbient() const;
	RGBA getDiffuse() const;
	RGBA getSpecular() const;
	float getShininess() const;
	RGBA getGlow() const;
	
private:
	RGBA *m_ambient, *m_diffuse, *m_specular, *m_glow;
	float *m_shininess;
};

#endif /* color_h */
