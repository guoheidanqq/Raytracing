#ifndef RECTANGLEX_H
#define RECTANGLEX_H
#include "Ray.h"
#include "IHittable.h"
#include "Material.h"
#include <cmath>

class RectangleX:public IHittable{
public:
	RectangleX(double X0,double y0,double z0, double X1, double y1,double z1,Material* material,bool isFrontFace = true){
		this->X0 = X0;
		this->X1 = X0;
		this->y0 = y0;
		this->y1 = y1;
		this->z0 = z0;
		this->z1 = z1;

		
		this->material = material;
		double depth = 1.f;
		Point3 minPoint(this->X0 - depth, this->y0, this->z0);
		Point3 maxPoint(this->X1 + depth, this->y1, this->z1);
		this->boundingBox = AABB(minPoint, maxPoint);

		this->isFrontFace = isFrontFace;
	}

	void reverseFaceNormal() {
		this->isFrontFace = !this->isFrontFace;
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
					if (this->isFrontFace == true) {
						hitInfo.N = Vec3(1.f, 0.f, 0.f);
					}
					if (this->isFrontFace == false) {
						hitInfo.N = Vec3(-1.f, 0.f, 0.f);
					}
					
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

	virtual bool hitBoundingBox(const Ray& ray, double tMin, double tMax) const override {
		bool isHit = this->boundingBox.hit(ray, tMin, tMax);
		return isHit;
	}
	virtual AABB getBoundingBox()const override{

		return this->boundingBox;
	}





public:

	double X0;
	double X1;
	double y0;
	double y1;
	double z0;
	double z1;
	bool isFrontFace;


	Material* material;
	AABB boundingBox;
};



#endif