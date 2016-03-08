//
//  camera.cpp
//  Raster
//
//  Created by Matthew Dillard on 2/22/16.
//

#include "camera.h"

// constructor and destructor
camera::camera(const unsigned int& xRes, const unsigned int& yRes,
			   const FLOAT3& position, const FLOAT3& normal,
			   const float& FOV,
			   const float& nearClip, const float& farClip,
			   const std::list<shape*> *shapelist,
			   const std::list<light*> *lightlist,
			   const unsigned int& antialiasing,
			   const FLOAT3& up):
	m_xRes(new unsigned int(xRes)), m_yRes(new unsigned int(yRes)),
	m_pos(new FLOAT3(position)), m_normal(new FLOAT3(normal.normalize())),
	m_xFOV(new float(FOV)),
	m_nearClip(new float(nearClip)), m_farClip(new float(farClip)),
	shapes(shapelist),
	lights(lightlist),
	m_antialiasing(new unsigned int(antialiasing)),
	m_upDir(new FLOAT3(up.normalize())),
	
	m_P00(0), m_P10(0), m_P01(0), m_P11(0),
	m_deltaX(0), m_deltaY(0),
	
	m_rng(new std::default_random_engine()),
	m_unif(new std::uniform_real_distribution<float>(0, 1)) {}

camera::~camera() {
	delete m_xRes;
	delete m_yRes;
	m_xRes = m_yRes = 0;
	
	delete m_pos;
	delete m_normal;
	delete m_upDir;
	m_pos = m_normal = m_upDir = 0;
	
	if (m_P00) delete m_P00;
	if (m_P10) delete m_P10;
	if (m_P01) delete m_P01;
	if (m_P11) delete m_P11;
	m_P00 = m_P10 = m_P01 = m_P11 = 0;
	
	if (m_deltaX) delete m_deltaX;
	if (m_deltaY) delete m_deltaY;
	m_deltaX = m_deltaY = 0;
	
	delete m_xFOV;
	delete m_nearClip;
	delete m_farClip;
	m_xFOV = m_nearClip = m_farClip = 0;
	
	delete m_rng;
	delete m_unif;
	m_rng = 0;
	m_unif = 0;
}


// getters
FLOAT3 camera::getPos() const {
	return *m_pos;
}

FLOAT3 camera::getNormal() const{
	return *m_normal;
}

unsigned int camera::getXRes() const {
	return *m_xRes;
}

unsigned int camera::getYRes() const {
	return *m_yRes;
}


// setters
void camera::setPos(const FLOAT3& position) {
	*m_pos = position;
}

void camera::setNormal(const FLOAT3& normal) {
	*m_normal = normal;
}


// starts the ray tracing, everything begins here
std::vector<RGBA> camera::capture(const RGBA& ambientLight, const float& diffuseOffset){
	threadpool pool(THREADPOOLSIZE);
	std::vector<RGBA> pixels;
	auto futurepixels = std::vector<std::future<RGBA>>();
	FLOAT3 vRay{}, hRay{};
	
	// update the viewpoint in case the camera is moving
	updateViewport();
	
	vRay = *m_P00;
	
	// calculate the value of each pixel
	for (int j = 0; j < *m_yRes; ++j) {
		hRay = vRay;
		for (int i = 0; i < *m_xRes; ++i) {
			futurepixels.emplace_back(pool.enqueue([&, hRay]{ return castRays(hRay, ambientLight, diffuseOffset); }));
			
			// increments
			hRay += *m_deltaX;
		}
		vRay += *m_deltaY;
	}
	
	for (int i = 0; i < futurepixels.size(); ++i) {
		RGBA pixel = futurepixels[i].get();
		pixels.push_back(pixel);
	}
	
	return pixels;
}


// updates the viewpoint and screenspace based on eye position and look direction
void camera::updateViewport() {
	float uWidth, vHeight;
	
	// calculate the screen dimensions relative to the eye vector given the FOV
	uWidth = tanf((*m_xFOV / 2.0f) * (M_PI / 180.0f));
	vHeight = ((float)*m_yRes / (float)*m_xRes) * uWidth;
	
	if (m_deltaX || m_deltaY) {
		delete m_deltaX;
		delete m_deltaY;
	}
	
	// calculate the coordinate frame for screenspace
	m_deltaX = new FLOAT3(m_normal->cross(*m_upDir).normalize());
	m_deltaY = new FLOAT3(m_deltaX->cross(*m_normal).normalize());
	
	if (m_P00 || m_P10 || m_P01 || m_P11) {
		delete m_P00;
		delete m_P10;
		delete m_P01;
		delete m_P11;
	}
	
	// compute the four corners of the screen in the global coordinate space
	m_P00 = new FLOAT3(*m_pos + *m_normal - (*m_deltaX * uWidth) - (*m_deltaY * vHeight));
	m_P10 = new FLOAT3(*m_pos + *m_normal + (*m_deltaX * uWidth) - (*m_deltaY * vHeight));
	m_P01 = new FLOAT3(*m_pos + *m_normal - (*m_deltaX * uWidth) + (*m_deltaY * vHeight));
	m_P11 = new FLOAT3(*m_pos + *m_normal + (*m_deltaX * uWidth) + (*m_deltaY * vHeight));
	
	// compute the average width of a pixel represented in screenspace
	*m_deltaX = (*m_P10 - *m_P00) / (float)*m_xRes;
	*m_deltaY = (*m_P01 - *m_P00) / (float)*m_yRes;
}

// traces rays to find the closest shapes, and performs the antialiasing
RGBA camera::castRays(const FLOAT3& origin, const RGBA& ambientLight, const float& diffuseOffset) const {
	float horiOffset, vertOffset, zValue;
	FLOAT3 subsample, ray;
	RGBA pixel{};
	shape *closest = 0;
	
	// collect samples of the scene for this current pixel
	for (int samples = 0; samples < *m_antialiasing; ++samples) {
		// randomly generate offsets for the current subsample
		horiOffset = (*m_unif)(*m_rng), vertOffset = (*m_unif)(*m_rng);
		
		// get the subsample position and construct a ray from it
		subsample = origin + (*m_deltaX * horiOffset) + (*m_deltaY * vertOffset);
		ray = (subsample - *m_pos).normalize();
		
		// initialize for color sampling
		zValue = *m_farClip;
		
		// detect the closest shape
		for (shape *s : *shapes) {
			float intersect = s->intersectRay(*m_pos, ray);
			if (intersect > *m_nearClip && intersect < zValue) {
				zValue = intersect;
				closest = s;
			}
		}
		
		// retrieve the shape's color
		pixel += getColor(closest, *m_pos + (ray * zValue), -ray, ambientLight, diffuseOffset);
	}
	
	// return the normalized supersampled value
	return pixel / (float)(*m_antialiasing);
}

// samples a shape at a point to get a color given the current lighting conditions
RGBA camera::getColor(const shape *s, const FLOAT3& point, const FLOAT3& toEye, const RGBA& ambientLight, const float& diffuseOffset) const {
	RGBA glow{}, ambient{}, diffuse{}, specular{};
	FLOAT3 directionToLight{};
	
	// color independant of all other lighting conditions
	glow = s->getGlow();
	
	// color dependant on the ambient light of the scene
	ambient = ambientLight * s->getAmbient();
	
	// iterate through all lights in the scene
	for (light *l : *lights) {
		directionToLight = l->normalToLight(point);
		
		// shadow check
		if (l->illuminated(point) && !obstructed(s, point, directionToLight, l)) {
			float product = s->getNormal(point).dot(directionToLight);
			float calculatedOffset = (product + diffuseOffset)/(1 + diffuseOffset);
			
			// color from direct diffuse illumination
			diffuse += s->getDiffuse() * l->getColor() * std::max(calculatedOffset, 0.0f);
			
			if (product > 0.0f) {
				FLOAT3 halfway = (toEye + l->normalToLight(point)).normalize();
				float specularvalue = (s->getNormal(point)).dot(halfway);
				
				// color from specular highlights
				specular += s->getSpecular() * l->getColor() * pow(std::max(specularvalue, 0.0f), s->getShininess());
			}
		}
	}
	
	return glow + ambient + diffuse + specular;
}

// Used to calculate shadows
bool camera::obstructed(const shape* object, const FLOAT3& point, const FLOAT3& directionToLight, const light* source) const {
	// first get the distance from the surface to the light
	float distanceToLight(source->distance(point));
	
	// then see if any shapes are closer than that
	for (shape *s : *shapes) {
		// we can ignore the original object
		if (s != object) {
			float intersect(s->intersectRay(point, directionToLight));
			if (intersect > 0.0 && intersect < distanceToLight)
				return true;
		}
	}
	
	return false;
}
