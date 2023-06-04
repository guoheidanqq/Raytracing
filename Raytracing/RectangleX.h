#ifndef RECTANGLEX_H
#define RECTANGLEX_H
#include "Ray.h"
#include "IHittable.h"
#include "Material.h"
#include <cmath>

class RectangleX:public IHittable{
public:
	RectangleX(double y0,double z0, double y1,double z1, double X0,Material* material){
		this->z0 = z0;
		this->z1 = z1;
		this->y0 = y0;
		this->y1 = y1;
		this->X0  = X0;
		this->material = material;
	}

	virtual bool hit(const Ray& ray, HitInfo& hitInfo,double tMin, double tMax)override {

		Point3 A  = ray.getOrigin();
		Vec3   b = ray.getDirection();
		double t = -1000.f;
		//parallel plane
		if(fabs(b.x())<0.00001f){
		  return false;
		}
		if(fabs(b.x())>=0.00001f){
		
			t = (this->X0 - A.x())/b.x();

			
			
			Point3 hitPoint = ray.at(t);
			double z = hitPoint.z();
			double y = hitPoint.y();

			if(z>=z0&&z<=z1 && y>=y0 && y<=y1 && t >= tMin && t<= tMax){
			    
					hitInfo.hitTime = t;
					hitInfo.hitPoint = hitPoint;
					hitInfo.N = Vec3(1.f,0.f,0.f);
					hitInfo.hitMaterial = this->material;
					hitInfo.ss = (z-z0)/(z1-z0);
					hitInfo.tt = (y-y0)/(y1-y0);
				return true;
			
			}
			else {
				return false;
			}
		
		}

		


	
	
	

		return false;
	}







public:
	double z0;
	double z1;
	double y0;
	double y1;
	double X0;
	Material* material;
};



#endif