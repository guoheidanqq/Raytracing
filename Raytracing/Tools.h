#ifndef TOOLS_H
#define TOOLS_H
#include <cstdlib>
#include "Vec3.h"


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




#endif