#ifndef METAL_H
#define METAL_H

#include"Vec3.h"
#include "Material.h"

class Metal: public Material{

public: 
	Metal(const Color& albedoColor){
	this->albedoColor = albedoColor;
	}

	virtual bool scatter(const Ray& inRay, const HitInfo& hitInfo, Color& attenuation, Ray& scatterRay) override{
		

		Point3 hitPoint = hitInfo.hitPoint;
		double hitTime = hitInfo.hitTime;
		Vec3 N = hitInfo.N;
		N = normal(N);
		Vec3 V = normal(inRay.dir);

		Vec3 B = dot(V,-N)*N;
		Vec3 R = V + 2*B;
		Ray reflectRay(hitPoint,R);
		scatterRay = reflectRay;

		attenuation = this->albedoColor;
		return true;

	}

public:

	Color albedoColor;

};




#endif