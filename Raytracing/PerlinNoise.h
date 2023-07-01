#ifndef PERLIN_NOISE_H
#define PERLIN_NOISE_H

#include "Vec3.h"
class PerlinNoise {

public:

	PerlinNoise() {
		const int size = 256;
		data = new double[size];
		dataX = new int[size];
		dataY = new int[size];
		dataZ = new int[size];
		for (int i = 0; i < size; i++) {
			data[i] = (double)i/255.f;
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
		int intX = (int)x;
		int indexX = intX % 255;
		if (indexX < 0) {
			indexX = indexX + 255;
		}
		double result = data[dataX[indexX]];
		return result;
	}

	double noise2D(double x, double y){
	

		int xi = (int)x % 255;
		if (xi < 0) {
			xi = xi + 255;
		}

		int yi = (int)y % 255;
		if (yi < 0) {
			yi = yi + 255;
		}

		int datai = dataY[dataX[xi]];
		//int datai = (xi * yi)%255;
		// int datai = (xi^yi);
		double result = data[datai];


		return result;
	}

	double noise3D(double x, double y,double z) {
		return 1.f;
	}


private:

	//fisher yates shuffle method
	void shuffle_fisher_yates(int* randData) {
		const int size = 256;
		for (int i = 0; i < size; i++) {
			int choose = rand() % (size-1);
			int& a = randData[choose];
			int& b = randData[size - 1 - i];
			swap(a, b);
		}
	
	}
	void swap(int& a, int& b) const
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

	void display(const int* arr) const {
		const int size = 256;
		for (int i = 0; i < size; i++) {
			std::cout << arr[i] << " ";

		}
		std::cout << std::endl;

	}

public:
	double* data;
	int* dataX;
	int* dataY;
	int* dataZ;


};

#endif
