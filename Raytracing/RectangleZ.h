#ifndef RECTANGLEZ_H
#define RECTANGLEZ_H
#include "Ray.h"
#include "IHittable.h"
#include "Material.h"
#include <cmath>

class RectangleZ:public IHittable{
public:
	RectangleZ(double x0, double y0, double Z0, double x1, double y1, double Z1, Material* material, bool isFrontFace = true) {
		this->x0 = x0;
		this->x1 = x1;
		this->y0 = y0;
		this->y1 = y1;
		this->Z0  = Z0;
		this->Z1 = Z1;


		this->material = material;

		double depth = 1.f;
		Point3 minPoint(this->x0 , this->y0, this->Z0 - depth);
		Point3 maxPoint(this->x1 , this->y1, this->Z1 + depth);
		this->boundingBox = AABB(minPoint, maxPoint);

		this->isFrontFace = isFrontFace;
	}

	virtual bool hit(const Ray& ray, HitInfo& hitInfo,double tMin, double tMax)override {

		Point3 A  = ray.getOrigin();
		Vec3   b = ray.getDirection();
		double t = -1000.f;
		//parallel plane
		if(fabs(b.z())<0.00001f){
		  return false;
		}
		if(fabs(b.z())>=0.00001f){
		
			t = (this->Z0 - A.z())/b.z();

			
			
			Point3 hitPoint = ray.at(t);
			double x = hitPoint.x();
			double y = hitPoint.y();

			if(x>=x0&&x<=x1 && y>=y0 && y<=y1 && t >= tMin && t<= tMax){
			    
					hitInfo.hitTime = t;
					hitInfo.hitPoint = hitPoint;
					if (this->isFrontFace == true) {
						hitInfo.N = Vec3(0.f, 0.f, 1.f);
					}
					if (this->isFrontFace == false) {
						hitInfo.N = Vec3(0.f, 0.f, -1.f);
					}
					
					hitInfo.hitMaterial = this->material;
					hitInfo.ss = (x-x0)/(x1-x0);
					hitInfo.tt = (y-y0)/(y1-y0);
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
	double y0;
	double y1;
	double Z0;
	double Z1;
	Material* material;
	AABB boundingBox;
	bool isFrontFace;
};



#endif