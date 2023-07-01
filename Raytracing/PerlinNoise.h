#ifndef PERLIN_NOISE_H
#define PERLIN_NOISE_H

#include "Vec3.h"
class PerlinNoise {

public:

	PerlinNoise() {
		const int size = 256;
		data = new double[size];
		dataX = new double[size];
		dataY = new double[size];
		dataZ = new double[size];
		for (int i = 0; i < size; i++) {
			data[i] = i;
			dataX[i] = i;
			dataY[i] = i;
			dataZ[i] = i;
		}
		srand(1);
		this->shuffle_fisher_yates(dataX);
		this->shuffle_fisher_yates(dataY);
		this->shuffle_fisher_yates(dataZ);

	}

	~PerlinNoise() {
		delete[] data;
		delete[] dataX;
		delete[] dataY;
		delete[] dataZ;
	}

	double noise(const Point3& point) {
		return 1.f;
	}

	double noise1D(double x) {
		return 1.f;
	}

	double noise2D(double x, double y){
	
		return 1.f;
	}

	double noise3D(double x, double y,double z) {
		return 1.f;
	}


private:

	//fisher yates shuffle method
	void shuffle_fisher_yates(double* randData) {
		const int size = 256;
		for (int i = 0; i < size; i++) {
			int choose = rand() % (size-1);
			double& a = randData[choose];
			double& b = randData[size - 1 - i];
			swap(a, b);
		}
	
	}
	void swap(double& a, double& b) const
	{
		double tmp = a;
		a = b;
		b = tmp;

	}
public:
	void display(const double* arr ) const{
		const int size = 256;
		for (int i = 0; i < size; i++) {
			std::cout << arr[i] << " ";

		}
		std::cout << std::endl;
	
	}

public:
	double* data;
	double* dataX;
	double* dataY;
	double* dataZ;


};

#endif
