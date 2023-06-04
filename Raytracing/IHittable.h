#ifndef IHittable_H
#define IHittable_H

class Material;
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


};



#endif