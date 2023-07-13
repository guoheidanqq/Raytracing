
#ifndef WORLEY_NOISE_H
#define WORLEY_NOISE_H
#include <algorithm>
#include "Vec3.h"
#include "Tools.h"


class WorleyNoise{

public:
	WorleyNoise() {
		
		for (int i = 0; i < SAMPLE1D_NUM;i++) {
			double x = randab(0, 255);
			double y = 0; 
			double z = 0;
			seed1D[i] = Vec3(x,y,z);
		}

		for (int i = 0; i < SAMPLE2D_NUM; i++) {
			double x = randab(0, 255);
			double y = randab(0,255);
			double z = 0;
			seed2D[i] = Vec3(x, y, z);
		}

		for (int i = 0; i < SAMPLE3D_NUM; i++) {
			double x = randab(0, 255);
			double y = randab(0,255);
			double z = randab(0,255);
			seed3D[i] = Vec3(x, y, z);
		}






	}
	double noise1D(double x,int level = 0) {
		Point3 p(x,0.f,0.f);
	
		double distanceMin = 10000.f;
		double distArr[SAMPLE1D_NUM];
		for (int i = 0; i < SAMPLE1D_NUM; i++) {
			Vec3 disVec = p - seed1D[i];
			double distance = disVec.length();
			distArr[i] = distance;
		}
		std::sort(distArr,distArr+256);
		double result = distArr[level];
		double b = 255.f;
		double Ed1 = b * b / 6.f; //104.1
		double Vd1 = 67.f / 180.f * b * b * b * b;
		double stdVd1 =pow(Vd1,1.f/4.f);
		double norm_factor =  stdVd1; //199.18
		//double norm_factor = 255.f/256.f *2*(level+1);
		//double norm_factor = sqrt(255.f *255.f / 6.f) * 1.f;
		result = result / norm_factor;
		result = clamp(result,0.f,1.f);
		return result;

	}

	double noise2D(double x, double y,int level = 0) {
		Point3 p(x, y, 0.f);

		double distanceMin = 10000.f;
		double distArr[SAMPLE2D_NUM];
		for (int i = 0; i < SAMPLE2D_NUM; i++) {
			Vec3 disVec = p - seed2D[i];
			double distance = disVec.length();
			distArr[i] = distance;
		}
		std::sort(distArr, distArr + SAMPLE2D_NUM);
		double result = distArr[level];
		//double a = sqrt(255.f * 255.f / SAMPLE2D_NUM);
	
		//double norm_factor = sqrt(2)*(a*2)*(level+1);
		//double norm_factor = sqrt(255.f *255.f / 3.f) *1.f;
		double b = 255.f;
		double Ed2 = b * b / 3.f;  //147.23
		double Vd2 = 67.f / 90.f * b * b * b * b;
		double stdVd2 = pow(Vd2, 1.f / 4.f);
		double norm_factor = stdVd2;  //236.86
		result = result / norm_factor;
		result = clamp(result, 0.f, 1.f);
		return result;

	}

	double noise3D(double x, double y,double z,int level = 0) {
		Point3 p(x, y, z);

		double distanceMin = 10000.f;
		double distArr[SAMPLE3D_NUM];
		for (int i = 0; i < SAMPLE3D_NUM; i++) {
			Vec3 disVec = p - seed3D[i];
			double distance = disVec.length();
			distArr[i] = distance;
		}
		std::sort(distArr, distArr + SAMPLE3D_NUM);
		double result = distArr[level];
		double a = pow((255.f * 255.f * 255.f / SAMPLE3D_NUM), 1.f / 3.f);
		//double norm_factor = 3*a*pow(3.f,1.f/3.f) * (level + 1.f);

		//double norm_factor = sqrt(255.f * 255.f / 2.f) * 1.f;		
		double b = 255.f;
		double Ed3 = b * b / 2.f; //180.31
		double Vd3 = 67.f / 60.f * b * b * b * b;
		double stdVd3 = pow(Vd3, 1.f / 4.f);
		double norm_factor = stdVd3;  //262.12
		result = result / norm_factor;
		result = clamp(result, 0.f, 1.f);
		return result;
	}

	
public:
	static const int SAMPLE1D_NUM = 256;
	static const int SAMPLE2D_NUM = 1000;
	static const int SAMPLE3D_NUM = 3000;
	Vec3 seed1D[SAMPLE1D_NUM];
	Vec3 seed2D[SAMPLE2D_NUM];
	Vec3 seed3D[SAMPLE3D_NUM];
};



#endif