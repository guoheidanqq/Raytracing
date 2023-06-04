#ifndef MATERIAL_H
#define MATERIAL_H
#include "Ray.h"
#include "IHittable.h"

class HitInfo;
class Material{

public:

	virtual bool isLightMaterial(){
		return false;
	}

	virtual Color emitted(double ss, double tt, Point3& point){
		return Color(0.f,0.f,0.f);
	}

	virtual bool scatter(const Ray& inRay, const HitInfo& hitInfo, Color& attenuation, Ray& scatterRay)= 0;
};



#endif
