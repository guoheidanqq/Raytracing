#ifndef ISOTROPIC_VOLUME_H
#define ISOTROPIC_VOLUME_H
#include "Material.h"
#include "Texture.h"
#include "Tools.h"
class IsotropicVolume : public Material {
public:

	IsotropicVolume(Texture* const albedoColor) {
		this->albedoColor = albedoColor;
	
	}
	virtual bool isLightMaterial() override {
		return false;
	}

	virtual Color emitted(double ss, double tt, Point3& point)  override{
		return Color(0.f, 0.f, 0.f);
	}

	virtual bool scatter(const Ray& inRay, const HitInfo& hitInfo, Color& attenuation, Ray& scatterRay) override {
	
		Vec3 randomDirection = randvec_in_unitsphere();
		Point3 point = hitInfo.hitPoint;
		double s = hitInfo.ss;
		double t = hitInfo.tt;
		Ray newRay(point, randomDirection);
		attenuation = albedoColor->getTexture(s,t,point);
		scatterRay = newRay;
		return true;
	}




public:

	Texture* albedoColor;

};




#endif 
