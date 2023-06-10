#ifndef IHittable_H
#define IHittable_H
#include "AABB.h"

class Material;
class AABB;
class HitInfo{
public:
	double hitTime;
	Point3 hitPoint;
	Vec3  N;

	Material* hitMaterial;



	double ss;
	double tt;

};



class IHittable{
public:
	virtual bool hit(const Ray& ray, HitInfo& hitInfo,double tMin, double tMax) = 0;
	virtual bool hitBoundingBox(const Ray& ray, double tMin, double tMax) const = 0;
	virtual AABB getBoundingBox()const = 0;
};



#endif