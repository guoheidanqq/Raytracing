#ifndef METAL_H
#define METAL_H

#include"Vec3.h"
#include "Material.h"

class Metal: public Material{

public: 
	Metal(const Color& albedoColor){
		this->albedoColor = albedoColor;
		this->roughness = 0.6f;
		
	}

	Metal(const Color& albedoColor,double roughness) {
		this->albedoColor = albedoColor;
		this->roughness = roughness;

	}


	virtual bool scatter(const Ray& inRay, const HitInfo& hitInfo, Color& attenuation, Ray& scatterRay) override{
		

		Point3 hitPoint = hitInfo.hitPoint;
		double hitTime = hitInfo.hitTime;
		Vec3 N = hitInfo.N;
		N = normal(N);
		Vec3 V = normal(inRay.dir);
		//Vec3 NegN = -N;
		Vec3 B = dot(V,-N)*N;
		Vec3 R = V + 2*B;
		//Vec3 R = V - 2 * dot(V, N) * N;
		R = normal(R);
		Vec3 varyVec  = this->roughness * randvec_in_unitsphere();
		Vec3 roughR = R + varyVec;
		roughR = normal(roughR);

		Ray reflectRay(hitPoint,roughR);
		scatterRay = reflectRay;

		attenuation = this->albedoColor;
		double costheta = dot(scatterRay.dir, N);
		if (costheta > 0.f) {
			return true;
		}

		if (costheta <= 0.f) {
			return false;
		}
	}

public:

	Color albedoColor;
	double roughness;

};




#endif