#ifndef INSTANCE_FACTORY_H
#define INSTANCE_FACTORY_H

#include "IHittable.h"
#include "Transform.h"
#include <vector>
#include <limits>
#include "Vec3.h"
class InstanceFactory : public IHittable {
public:
	InstanceFactory(IHittable* originObj,Transform transform) {
		this->originObj = originObj;
		this->transform = transform;
		this->boundingBox = this->getBoundingBox();
	
	}


	virtual bool hit(const Ray& ray, HitInfo& hitInfo, double tMin, double tMax) override {
		Ray transRay;
		Point3 transPoint;
		Vec3 transNormal;
		HitInfo transHitInfo;

		double transHitTime;
		double hitTime;
		Point3 point;
		Vec3 N;		
		transRay.origin = this->transform.inverseApplyToPoint(ray.origin);
		transRay.dir = this->transform.inverseApplyToVector(ray.dir);
		transRay.dir = normal(transRay.dir);
		double timeScale = transRay.dir.length();
		double transTMin = tMin * timeScale;
		double transTMax = tMax * timeScale;
		bool isHit = originObj->hit(transRay,transHitInfo,transTMin, transTMax);
		
		transPoint = transHitInfo.hitPoint;
		transNormal = transHitInfo.N;
		transHitTime = transHitInfo.hitTime;
		point = transform.applyToPoint(transPoint);
		N = transform.applyToNormal(transNormal);
		hitTime = transHitTime / timeScale;

		hitInfo = transHitInfo;
		hitInfo.hitPoint = point;
		hitInfo.N = N;
		hitInfo.hitTime = hitTime;

		return isHit;

	}
	virtual bool hitBoundingBox(const Ray& ray, double tMin, double tMax) const override {
		bool isHit = this->boundingBox.hit(ray, tMin, tMax);

		return isHit;
	}
	virtual AABB getBoundingBox()const override {
		AABB originBB = originObj->getBoundingBox();
		Point3 minPoint = originBB.minPoint;
		Point3 maxPoint = originBB.maxPoint;
		double x0 = minPoint.x();
		double y0 = minPoint.y();
		double z0 = minPoint.z();
		double x1 = maxPoint.x();
		double y1 = maxPoint.y();
		double z1 = maxPoint.z();
		Point3 p0(x0, y0, z0);
		Point3 p1(x0, y0, z1);
		Point3 p2(x0, y1, z0);
		Point3 p3(x0, y1, z1);
		Point3 p4(x1, y0, z0);
		Point3 p5(x1, y0, z1);
		Point3 p6(x1, y1, z0);
		Point3 p7(x1, y1, z1);
		std::vector<Point3> points;
		points.push_back(p0);
		points.push_back(p1);
		points.push_back(p2);
		points.push_back(p3);
		points.push_back(p4);
		points.push_back(p5);
		points.push_back(p6);
		points.push_back(p7);
		std::vector<Point3> transformedPoints;
		for (int i = 0; i < 8; i++) {
			Point3 tmpPoint = transform.applyToPoint(points[i]);
			transformedPoints.push_back(tmpPoint);
		}
		const double infinity = std::numeric_limits<double>::infinity();
		double xmin = infinity;
		double ymin = infinity;
		double zmin = infinity;
		double xmax = -infinity;		
		double ymax = -infinity;
		double zmax = -infinity;
		for (int i = 0; i < 8; i++) {
			Point3 point = transformedPoints[i];
			double x = point.x();
			double y = point.y();
			double z = point.z();
			if (x < xmin) {
				xmin = x;
			}
			if (x > xmax) {
				xmax = x;
			}
			if (y < ymin) {
				ymin = y;
			}
			if (y > ymax) {
				ymax = y;
			}
			if (z < zmin) {
				zmin = z;
			}
			if (z > zmax) {
				zmax = z;
			}
		
		}
				
		AABB transformedBB(Point3(xmin,ymin,zmin),Point3(xmax,ymax,zmax));
		return transformedBB;

	}




public:
	IHittable* originObj;
	Transform transform;
	AABB boundingBox;


};






#endif
