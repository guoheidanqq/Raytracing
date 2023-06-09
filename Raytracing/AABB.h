#ifndef AABB_H
#define AABB_H
#include "Vec3.h"
#include "Ray.h"
class AABB {
public:
	AABB() {
		this->maxPoint = Point3(1.f, 1.f, 1.f);
		this->minPoint = Point3(-1.f, -1.f, -1.f);

	}
	AABB(const Point3& minPoint, const Point3& maxPoint) {

		this->minPoint = minPoint;
		this->maxPoint = maxPoint;


	}
public:
	bool hit(const Ray& inRay, double tmin, double tmax) const {
		double tx0 = -10000.f;
		double tx1 = -10000.f;
		double ty0 = -10000.f;
		double ty1 = -10000.f;
		double tz0 = -10000.f;
		double tz1 = -10000.f;
		double x0 = this->minPoint.x();
		double y0 = this->minPoint.y();
		double z0 = this->minPoint.z();
		double x1 = this->maxPoint.x();
		double y1 = this->maxPoint.y();
		double z1 = this->maxPoint.z();
		Point3 A = inRay.getOrigin();
		Vec3   b = inRay.getDirection();
		double Ax = A.x();
		double Ay = A.y();
		double Az = A.z();
		double bx = b.x();
		double by = b.y();
		double bz = b.z();



		//parallel plane
		if (fabs(bx) < 0.00001f || fabs(by) < 0.00001f || fabs(bz) < 0.00001f) {
			return false;
		}

		if (fabs(bx) >= 0.00001f) {
			tx0 = (x0 - Ax) / bx;
			tx1 = (x1 - Ax) / bx;
			if (tx0 > tx1) {
				swap(tx0, tx1);
			}
			

		}

		if (fabs(by) >= 0.00001f) {
			ty0 = (y0 - Ay) / by;
			ty1 = (y1 - Ay) / by;
			if (ty0 > ty1) {
				swap(ty0,ty1);
			}

		}

		if (fabs(bz) >= 0.00001f) {
			tz0 = (z0 - Az) / bz;
			tz1 = (z1 - Az) / bz;
			if (tz0 > tz1) {
				swap(tz0,tz1);
			}

		}

		bool xyOverlap = isOverlap(tx0, tx1, ty0, ty1);
		bool yzOverlap = isOverlap(ty0, ty1, tz0, tz1);
		bool xzOverlap = isOverlap(tx0, tx1, tz0, tz1);
		bool xRangeOverlap = isOverlap(tx0, tx1, tmin, tmax);
		bool yRangeOverlap = isOverlap(ty0, ty1, tmin, tmax);
		bool zRangeOverlap = isOverlap(tz0, tz1, tmin, tmax);
		if (xyOverlap && yzOverlap && xzOverlap &&
			xRangeOverlap && yRangeOverlap && zRangeOverlap) {
			return true;
		}
		return false;


	}

	bool isOverlap(double t0, double t1, double s0, double s1) const {
		double tmin = fmax(t0, s0);
		double tmax = fmin(t1, s1);
		if (tmin <= tmax) {
			return true;
		}
		if (tmin >= tmax) {
			return false;
		}

	}

	void swap(double& a, double& b) const
	{
		double tmp = a;
		a = b;
		b = tmp;

	}
	


public:
	Point3 minPoint;
	Point3 maxPoint;

};







#endif
