#ifndef CUBE_H
#define CUBE_H
#include "IHittable.h"
#include "Scene.h"
#include "RectangleX.h"
#include "RectangleY.h"
#include "RectangleZ.h"
class Cube : public IHittable {
public: 
	Cube(const Point3& minPoint, const Point3& maxPoint,Material* const material) {
		this->material = material;		
		double x0 = minPoint.x();
		double y0 = minPoint.y();
		double z0 = minPoint.z();
		double x1 = maxPoint.x();
		double y1 = maxPoint.y();
		double z1 = maxPoint.z();
		RectangleX*  leftFace = new RectangleX(x0,y0,z0,x0,y1,z1,this->material,false);
		RectangleX* rightFace = new RectangleX(x1,y0,z0,x1,y1,z1, this->material,true);
		RectangleY* buttomFace = new RectangleY(x0,y0,z0,x1,y0,z1,this->material,false);
		RectangleY* topFace = new RectangleY(x0,y1,z0,x1,y1,z1, this->material, true);
		RectangleZ*  backFace  = new RectangleZ(x0,y0,z0, x1,y1,z0, this->material,false);
		RectangleZ*  frontFace = new RectangleZ(x0, y0, z1, x1, y1, z1, this->material, true);
		this->cube.add(leftFace);
		this->cube.add(rightFace);
		this->cube.add(buttomFace);
		this->cube.add(topFace);
		this->cube.add(backFace);
		this->cube.add(frontFace);
		
		this->boundingBox = this->cube.boundingBox;
		
	
	}

	virtual bool hit(const Ray& ray, HitInfo& hitInfo, double tMin, double tMax) override {
		bool isHit = this->cube.hit(ray,hitInfo,tMin,tMax);
		return isHit;

	}
	virtual bool hitBoundingBox(const Ray& ray, double tMin, double tMax) const override {
		bool isHit = this->boundingBox.hit(ray, tMin, tMax);

		return isHit;
	}
	virtual AABB getBoundingBox()const override {
		return this->boundingBox;
	}


public: 
	Point3 minPoint;
	Point3 maxPoint;
	Scene  cube;
	Material* material;
	AABB boundingBox;
	


};



#endif
