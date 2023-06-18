#ifndef DIFFUSELIGHT_H
#define DIFFUSELIGHT_H
#include "Material.h"
#include "Texture.h"

class DiffuseLight :public Material{
public:
	DiffuseLight( Texture*   const texture){
		this->texture = texture;
	}
	


	virtual bool isLightMaterial() override{
	
		return true;
	}
	virtual Color emitted(double ss, double tt, Point3& point){

		Color color = this->texture->getTexture(ss,tt,point);
		return color;
	}

	virtual bool scatter(const Ray& inRay, const HitInfo& hitInfo, Color& attenuation, Ray& scatterRay){
	
	   return false;
	}


public:
	Texture* texture;


};



#endif