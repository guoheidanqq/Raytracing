#ifndef SPHERE_H
#define SPHERE_H

#include "Vec3.h"
#include "Ray.h"
#include "IHittable.h"
#include "AABB.h"

double hitSphere(const Point3& center,double radius,const Ray& ray);

class Sphere :public IHittable{

public:
	Sphere(const Point3& center,double radius, Material* const  material){
		this->center = center;
		this->radius = radius;
		this->material = material;
		this->boundingBox = AABB(center-Vec3(radius,radius,radius),center + Vec3(radius,radius,radius));


	}
	virtual bool hit(const Ray& ray,HitInfo& hitInfo, double tMin =0.f, double tMax = 1000000.f) override{
		
		double hitTime = hitSphere(this->center,this->radius,ray);
		if(hitTime>=0.f&& hitTime>=tMin && hitTime <= tMax){
			Point3 pHit = ray.at(hitTime);
		    Vec3   pHitNormal = pHit-center;
		    Vec3 N = normal(pHitNormal);

			hitInfo.hitTime = hitTime;
			hitInfo.hitPoint =pHit;
			hitInfo.N = N;
			hitInfo.hitMaterial = this->material;
			this->getST(pHit,hitInfo.ss,hitInfo.tt);
			return true;
		}

		else return false;
	

	}

	virtual bool hitBoundingBox(const Ray& ray, double tMin, double tMax) const override {
	
		bool isHit = this->boundingBox.hit(ray, tMin,tMax);

		return isHit;

	}
	virtual AABB getBoundingBox()const override {
	
		return this->boundingBox;
	}

	void getST(const Point3& point, double& ss,double& tt){

		double pi = 3.1415926f;
		Vec3 vec = point-center;
		vec/= radius;
		double theta = acos(-vec.y());
        double phi = atan2(-vec.z(), vec.x()) + pi;
        ss = phi / (2*pi);
        tt = theta / pi;	
	}



public:
	Point3 center;
	double radius;
	Material* material;

	AABB boundingBox;

};




double hitSphere(const Point3& center,double radius,const Ray& ray){

	Vec3 A = ray.getOrigin();
	Vec3 B = ray.getDirection();
	Vec3 C =center;
	double r = radius;

	B = normal(B);
	double a = dot(B,B);
	double b =2*dot(B,A-C);
	double c  = dot(A-C,A-C)-r*r;
	double discriminant  = (b*b-4.f*a*c);
	if(discriminant<0.f){
		return -1.f;
	}

	if(discriminant >= 0.f){	
		double t= (-b -sqrt(discriminant))/(2.f*a);
		return t;	
	}
}







#endif