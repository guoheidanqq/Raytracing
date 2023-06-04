#ifndef LAMBERIIAN_H
#define LAMBERTIAN_H
#include "Material.h"
#include "Vec3.h"
#include "Tools.h"
#include "Texture.h"

class Lambertian:public Material{


public:
	Lambertian( const Color& albedoColor){
		this->albedoColor = albedoColor;
		this->texture = nullptr;
	}

	Lambertian( Texture* const  texture){

		this->albedoColor =Color(0.f,0.f,0.f);
		this->texture = texture;
	}

	virtual bool scatter(const Ray& inRay, const HitInfo& hitInfo, Color& attenuation, Ray& scatterRay) override{
	
		    Point3 hitPoint = hitInfo.hitPoint;
			double hitTime = hitInfo.hitTime;
			Vec3 N = hitInfo.N;
			N = normal(N);
			Vec3 center = hitPoint + N;
			Vec3 vecS = normal(randvec_in_unitsphere()); 
			Vec3 PS = center + vecS;
			PS = normal(PS);
			Ray newRay(hitPoint,PS);
			scatterRay = newRay;

			if(texture==nullptr){
				attenuation = this->albedoColor;
			}
			if(texture!=nullptr){
				double ss = hitInfo.ss;
				double tt = hitInfo.tt;
				attenuation = this->texture->getTexture(ss,tt,hitPoint);
			}

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
	Texture* texture;


};






#endif
