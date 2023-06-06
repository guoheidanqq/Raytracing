#ifndef TOOLS_H
#define TOOLS_H
#include <cstdlib>
#include "Vec3.h"

double clamp(double x) {
	if (x >= 1.0f) {
		x = 1.f;

	}
	if (x <= 0.f) {
		x = 0.f;
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




#endif