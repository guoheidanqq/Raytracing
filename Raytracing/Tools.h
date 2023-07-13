#ifndef TOOLS_H
#define TOOLS_H
#include <cstdlib>
#include "Vec3.h"
#include "IHittable.h"

double radian2degree(double radian) {
	const double pi = 3.1415926f;
	return pi / 180.f * radian;
}

bool compareHittable_X(const IHittable* a, const IHittable* b) {
	double axMin = a->getBoundingBox().minPoint.x();
	double bxMin = b->getBoundingBox().minPoint.x();

	if (axMin < bxMin) {
		return true;
	}
	if (axMin >= bxMin) {

		return false;
	}
}
bool compareHittable_Y(const IHittable* a, const IHittable* b) {
	double ayMin = a->getBoundingBox().minPoint.y();
	double byMin = b->getBoundingBox().minPoint.y();

	if (ayMin < byMin) {
		return true;
	}
	if (ayMin >= byMin) {

		return false;
	}
}


bool compareHittable_Z(const IHittable* a, const IHittable* b) {
	double azMin = a->getBoundingBox().minPoint.z();
	double bzMin = b->getBoundingBox().minPoint.z();

	if (azMin < bzMin) {
		return true;
	}
	if (azMin >= bzMin) {

		return false;
	}
}


double clamp(double x) {
	if (x >= 1.0f) {
		x = 1.f;

	}
	if (x <= 0.f) {
		x = 0.f;
	}

	return x;

}


double clamp(double x,double a,double b) {
	if (x <= a) {
		x = a;

	}
	if (x >= b) {
		x = b;
	}

	return x;

}

double rand01(){
	double result = double(rand())/double(RAND_MAX + 1.0f);
	return result;

}

double randab(double a, double b){

	double result = rand01();
	result = a+(b-a)*result;
	return result;
}

Vec3 randvec01(){

	Vec3 result(rand01(),rand01(),rand01());

	return result;

}

Vec3 randvecab(double a, double b){

	Vec3 result(randab(a,b),randab(a,b),randab(a,b));

	return result;

}


Vec3 randvec_in_unitsphere(){
	Vec3 fortest(randab(-1.f,1.f),randab(-1.f,1.f),randab(-1.f,1.f));

	while(true){
		if(fortest.length()<=1.0f){
		break;
		}
		fortest = Vec3(randab(-1.f,1.f),randab(-1.f,1.f),randab(-1.f,1.f));
	
	}
	return fortest;
}

Vec3 randvec_in_uinit_circle() {
	Vec3 vec(randab(-1.f, 1.f), randab(-1.f, 1.f), 0);

	while (true) {
		if (vec.length() <= 1.0f) {
			break;
		}
		vec = Vec3(randab(-1.f, 1.f), randab(-1.f, 1.f), 0);

	}
	return vec;

}


int random012(double a, double b, double c) {
	// precondition a + b + c = 1
	double U = rand01();
	int result = 0; 
	if (U >= 0 && U <= a) {
		result = 0;
	}

	if (U >= a && U <= a + b) {
		result = 1;
	}

	if (U >= a + b && U <= 1.f) {
		result = 2;
	}

	return result;

}

double lerp(double a, double b, double t) {

	double result = a + (b - a) * t;
	return result;
}

Vec3 lerpVec3(const Vec3& a, const Vec3& b, double t) {
	Vec3 result = a + (b - a) * t;
	return result;
}


double smoothstep(double a, double b, double t) {

	double result = (b - a) * t * t*(3 - 2 * t) + a;
	return result;
}



double smoothstep2D(double f00, double f01,double f10,double f11, double tx,double ty) {

	double f0 = smoothstep(f00, f01, ty);
	double f1 = smoothstep(f10, f11, ty);
	double result = smoothstep(f0, f1, tx);
	return result;
}
double smoothstep3D(double f000, double f001, double f010, double f011,
	double f100, double f101, double f110, double f111,
	double tx, double ty, double tz) {

	double f00 = smoothstep(f000, f001, tz);
	double f01 = smoothstep(f010, f011, tz);
	double f10 = smoothstep(f100, f101, tz);
	double f11 = smoothstep(f110, f111, tz);
	double result = smoothstep2D(f00, f01, f10, f11, tx, ty);
	return result;
}

double lerp2D(double f00, double f01, double f10, double f11,double tx,double ty) {

	double f0 = lerp(f00, f01, ty);
	double f1 = lerp(f10, f11, ty);
	double result = lerp(f0, f1, tx);
	return result;
}



double lerp3D(double f000,double f001,double f010,double f011,
			  double f100,double f101,double f110,double f111,
				double tx,double ty,double tz) {

	double f00 = lerp(f000, f001, tz);
	double f01 = lerp(f010,f011,tz);
	double f10 = lerp(f100,f101,tz);
	double f11 = lerp(f110,f111,tz);
	double result = lerp2D(f00,f01,f10,f11,tx,ty);
	return result;
}

double tx(double x0, double x1, double x) {
	double result = (x - x0) / (x1 - x0);
	return result;
}




#endif