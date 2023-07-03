#ifndef PERLIN_NOISE_H
#define PERLIN_NOISE_H

#include "Vec3.h"
class PerlinNoise {

public:

	PerlinNoise(double scalex =1.f,double scaley =1.f,double scalez = 1.f) {

		this->scalex = scalex;
		this->scaley = scaley;
		this->scalez = scalez;
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

		double x = point.x();
		double y = point.y();
		double z = point.z();


		double result = this->noise3D(x,y,z,this->scalex,this->scaley,this->scalez);
		return result;
	}

	double noise_linear_interp(const Point3& point) {

		double x = point.x();
		double y = point.y();
		double z = point.z();

		double floorx = floor(x);
		double floory = floor(y);
		double floorz = floor(z);

		double tx = x - floorx;
		double ty = y - floory;
		double tz = z - floorz;


		double f000 = this->noise3D(floorx,floory,floorz,this->scalex,this->scaley,this->scalez);
		double f001 = this->noise3D(floorx, floory, floorz+1, this->scalex, this->scaley, this->scalez);
		double f010 = this->noise3D(floorx, floory+1, floorz, this->scalex, this->scaley, this->scalez);
		double f011 = this->noise3D(floorx, floory+1, floorz+1, this->scalex, this->scaley, this->scalez);
		double f100 = this->noise3D(floorx+1, floory, floorz, this->scalex, this->scaley, this->scalez);
		double f101 = this->noise3D(floorx+1, floory, floorz+1, this->scalex, this->scaley, this->scalez);
		double f110 = this->noise3D(floorx+1, floory+1, floorz, this->scalex, this->scaley, this->scalez);
		double f111 = this->noise3D(floorx+1, floory+1, floorz+1, this->scalex, this->scaley, this->scalez);
		
		double result = lerp3D(f000,f001,f010,f011,f100,f101,f110,f111,tx,ty,tz);
		return result;
	}


	double noise1D(double x,double scale = 1.f) {
		x = scale * x;
		int intX = (int)x;
		int indexX = intX % 256;
		if (indexX < 0) {
			indexX = indexX + 256;
		}
		double result = data[dataX[indexX]];
		return result;
	}

	double noise2D(double x, double y,double scalex = 1.f,double scaley = 1.f){
	
		x = x * scalex;
		y = y * scaley;
		int xi = (int)x % 256;
		if (xi < 0) {
			xi = xi + 256;
		}

		int yi = (int)y % 256;
		if (yi < 0) {
			yi = yi + 256;
		}

		int datai = dataY[dataX[xi]];
		//int datai = (xi * yi)%256;
		// int datai = (xi^yi);
		double result = data[datai];


		return result;
	}

	double noise3D(double x, double y,double z,double scalex =1.f,double scaley = 1.f,double scalez = 1.f) {

		x = x * scalex;
		y = y * scaley;
		z = z * scalez;
		int xi = (int)x % 256;
		if (xi < 0) {
			xi = xi + 256;
		}

		int yi = (int)y % 256;
		if (yi < 0) {
			yi = yi + 256;
		}

		int zi = (int)z % 256;
		if (zi < 0) {
			zi = zi + 256;
		}

		int indexY = (dataX[xi] + yi) % 256;
		int indexZ = (dataY[indexY] + zi) % 256;
		int datai = dataZ[indexZ];
		//int datai = (xi * yi * zi)%256;
		// int datai = (xi^yi);
		//int datai = (xi ^ yi ^ zi);
		double result = data[datai];

		return result;
		
	}


	// xi yi zi in [0,255]
	//return value [0,255]
	int hash(int xi,int yi, int zi) {
		int datai = (xi ^ yi ^ zi);

		return datai;
	
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

	double scalex;
	double scaley;
	double scalez;


};

#endif
