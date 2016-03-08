//
//  scene.h
//  Raster
//
//  Created by Matthew Dillard on 2/28/16.
//

#ifndef scene_h
#define scene_h

#include <vector>
#include <list>
#include <map>

#include "directionlight.h"
#include "pointlight.h"
#include "spotlight.h"
#include "cylinder.h"
#include "camera.h"
#include "sphere.h"
#include "plane.h"
#include "rgba.h"

class scene {
public:
	scene(const RGBA& ambientLight = {}, const float& diffuseOffset = 0.0);
	~scene();
	
	const camera* getCamera() const;
	RGBA getAmbientLight() const;
	float getDiffuseOffset() const;
	const std::list<shape*>* getShapes() const;
	const std::list<light*>* getLights() const;
	
	void setCamera(camera*);
	void setAmbientLight(const RGBA&);
	void setDiffuseOffset(const float&);
	
	void addShape(shape*);
	void addLight(light*);
	
	std::vector<RGBA> capture();
	
	operator bool() const;
	
private:
	camera *m_camera;
	std::list<shape*> *m_shapes;
	std::list<light*> *m_lights;
	RGBA *m_ambientLight;
	float *m_diffuseOffset;
};

#endif /* scene_h */
