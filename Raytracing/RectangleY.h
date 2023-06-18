#ifndef RECTANGLEY_H
#define RECTANGLEY_H
#include "Ray.h"
#include "IHittable.h"
#include "Material.h"
#include <cmath>

class RectangleY:public IHittable{
public:
	RectangleY(double x0, double Y0, double z0, double x1, double Y1, double z1, Material* material, bool isFrontFace = true) {

		this->x0 = x0;
		this->x1 = x1;
		this->Y0  = Y0;
		this->Y1 = Y0;

		this->z0 = z0;
		this->z1 = z1;
		this->material = material;
		double depth = 1.f;
		Point3 minPoint(this->x0 , this->Y0 - depth, this->z0);
		Point3 maxPoint(this->x0 , this->Y0 + depth, this->z1);
		this->boundingBox = AABB(minPoint, maxPoint);

		this->isFrontFace = isFrontFace;
	}

	virtual bool hit(const Ray& ray, HitInfo& hitInfo,double tMin, double tMax)override {

		Point3 A  = ray.getOrigin();
		Vec3   b = ray.getDirection();
		double t = -1000.f;
		//parallel plane
		if(fabs(b.y())<0.00001f){
		  return false;
		}
		if(fabs(b.y())>=0.00001f){
		
			t = (this->Y0 - A.y())/b.y();

			
			
			Point3 hitPoint = ray.at(t);
			double z = hitPoint.z();
			double x = hitPoint.x();

			if(z>=z0&&z<=z1 && x>=x0 && x<=x1 && t >= tMin && t<= tMax){
			    
					hitInfo.hitTime = t;
					hitInfo.hitPoint = hitPoint;

					if (this->isFrontFace == true) {
						hitInfo.N = Vec3(0.f, 1.f, 0.f);
					}
					if (this->isFrontFace == false) {
						hitInfo.N = Vec3(0.f, -1.f, 0.f);
					}

					hitInfo.hitMaterial = this->material;
					hitInfo.ss = (z-z0)/(z1-z0);
					hitInfo.tt = (x-x0)/(x1-x0);
				return true;
			
			}
			else {
				return false;
			}
		
		}

		return false;
	}


	virtual bool hitBoundingBox(const Ray& ray, double tMin, double tMax) const override {
		bool isHit = this->boundingBox.hit(ray, tMin, tMax);
		return isHit;
	}
	virtual AABB getBoundingBox()const override {

		return this->boundingBox;
	}





public:

	double x0;
	double x1;
	double Y0;
	double Y1;
	double z0;
	double z1;
	Material* material;
	AABB boundingBox;

	bool isFrontFace;
};



#endif