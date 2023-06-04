#ifndef RAY_H
#define RAY_H

#include "Vec3.h"

class Ray{
public:
	Ray(){
	}

	Ray(const Point3& origin, const Vec3& dir){
		this->origin = origin;
		this->dir = normal(dir);		
	}

	Point3 getOrigin()  const{
		return this->origin;
	}

	Vec3 getDirection() const{
		Vec3 result = this->dir;
		result = normal(result);
		return result;
	}


	Point3 at(double t){

	  return origin + t*dir;
	}


public:
	Point3 origin;
	Vec3 dir;

};



#endif