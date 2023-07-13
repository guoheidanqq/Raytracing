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
		dataVec = new Vec3[size];
		dataX = new int[size];
		dataY = new int[size];
		dataZ = new int[size];
		for (int i = 0; i < size; i++) {
			data[i] = (double)i/255.f;
			//dataVec[i] = normal(randvecab(-1.f,1.f));
			dataVec[i] = randvecab(-1.f,1.f);
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
		delete[] dataVec;
		delete[] dataX;
		delete[] dataY;
		delete[] dataZ;
	}

	double noise(const Point3& point) const{

		double x = point.x();
		double y = point.y();
		double z = point.z();


		double result = this->noise3D(x,y,z,this->scalex,this->scaley,this->scalez);
		return result;
	}

	double noise_smoothstep_interp(const Point3& point) const{

		double x = point.x();
		double y = point.y();
		double z = point.z();

		double floorx = floor(x);
		double floory = floor(y);
		double floorz = floor(z);

		double tx = x - floorx;
		double ty = y - floory;
		double tz = z - floorz;


		double f000 = this->noise3D(floorx, floory, floorz, this->scalex, this->scaley, this->scalez);
		double f001 = this->noise3D(floorx, floory, floorz + 1, this->scalex, this->scaley, this->scalez);
		double f010 = this->noise3D(floorx, floory + 1, floorz, this->scalex, this->scaley, this->scalez);
		double f011 = this->noise3D(floorx, floory + 1, floorz + 1, this->scalex, this->scaley, this->scalez);
		double f100 = this->noise3D(floorx + 1, floory, floorz, this->scalex, this->scaley, this->scalez);
		double f101 = this->noise3D(floorx + 1, floory, floorz + 1, this->scalex, this->scaley, this->scalez);
		double f110 = this->noise3D(floorx + 1, floory + 1, floorz, this->scalex, this->scaley, this->scalez);
		double f111 = this->noise3D(floorx + 1, floory + 1, floorz + 1, this->scalex, this->scaley, this->scalez);

		double result = smoothstep3D(f000, f001, f010, f011, f100, f101, f110, f111, tx, ty, tz);
		return result;
	}


	double noise_linear_interp(const Point3& point) const {

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

	double noise_perlin_interp(const Point3& point) const{

		double x = point.x();
		double y = point.y();
		double z = point.z();

		double floorx = floor(x);
		double floory = floor(y);
		double floorz = floor(z);

		double tx = x - floorx;
		double ty = y - floory;
		double tz = z - floorz;


		Vec3 v000 = this->noise3D_Vec3(floorx, floory, floorz, this->scalex, this->scaley, this->scalez);
		Vec3 v001 = this->noise3D_Vec3(floorx, floory, floorz + 1, this->scalex, this->scaley, this->scalez);
		Vec3 v010 = this->noise3D_Vec3(floorx, floory + 1, floorz, this->scalex, this->scaley, this->scalez);
		Vec3 v011 = this->noise3D_Vec3(floorx, floory + 1, floorz + 1, this->scalex, this->scaley, this->scalez);
		Vec3 v100 = this->noise3D_Vec3(floorx + 1, floory, floorz, this->scalex, this->scaley, this->scalez);
		Vec3 v101 = this->noise3D_Vec3(floorx + 1, floory, floorz + 1, this->scalex, this->scaley, this->scalez);
		Vec3 v110 = this->noise3D_Vec3(floorx + 1, floory + 1, floorz, this->scalex, this->scaley, this->scalez);
		Vec3 v111 = this->noise3D_Vec3(floorx + 1, floory + 1, floorz + 1, this->scalex, this->scaley, this->scalez);

		Vec3 P = Vec3(tx,ty,tz);
		Vec3 p000 = P - Vec3(0.f,0.f,0.f);
		Vec3 p001 = P - Vec3(0.f,0.f,1.f);
		Vec3 p010 = P - Vec3(0.f,1.f,0.f);
		Vec3 p011 = P - Vec3(0.f,1.f,1.f);
		Vec3 p100 = P - Vec3(1.f,0.f,0.f);
		Vec3 p101 = P - Vec3(1.f, 0.f, 1.f);
		Vec3 p110 = P - Vec3(1.f, 1.f, 0.f);
		Vec3 p111 = P - Vec3(1.f, 1.f, 1.f);
		//p000 = normal(p000);
		//p001 = normal(p001);
		//p010 = normal(p010);
		//p011 = normal(p011);
		//p100 = normal(p100);
		//p101 = normal(p101);
		//p110 = normal(p110);
		//p111 = normal(p111);
		double f000 = dot(v000,p000);
		double f001 = dot(v001,p001);
		double f010 = dot(v010,p010);
		double f011 = dot(v011,p011);
		double f100 = dot(v100,p100);
		double f101 = dot(v101,p101);
		double f110 = dot(v110,p110);
		double f111 = dot(v111,p111);
		//f000 = remap_range_01(f000);
		//f001 = remap_range_01(f001);
		//f010 = remap_range_01(f010);
		//f011 = remap_range_01(f011);
		//f100 = remap_range_01(f100);
		//f101 = remap_range_01(f101);
		//f110 = remap_range_01(f110);
		//f111 = remap_range_01(f111);

		f000 = remap_range_03(f000);
		f001 = remap_range_03(f001);
		f010 = remap_range_03(f010);
		f011 = remap_range_03(f011);
		f100 = remap_range_03(f100);
		f101 = remap_range_03(f101);
		f110 = remap_range_03(f110);
		f111 = remap_range_03(f111);
		double result = smoothstep3D(f000, f001, f010, f011, f100, f101, f110, f111, tx, ty, tz);
		return result;
	}

	double remap_range_01(double x) {
		return (x + 1.f) / 2.f;
	}


	double remap_range_03(double x) const{
		//double result = (x + 3.f) / 3.f;
		//result = result - 0.1;
		//double gammaCorrect = result * result * result;
		//return gammaCorrect;
		//return x / sqrt(3.f);
		double result = x / 3.f;
		return result;
	}

	double noise1D(double x,double scale = 1.f) const{
		x = scale * x;
		int intX = (int)x;
		int indexX = intX % 256;
		if (indexX < 0) {
			indexX = indexX + 256;
		}
		double result = data[dataX[indexX]];
		return result;
	}

	double noise2D(double x, double y,double scalex = 1.f,double scaley = 1.f) const{
	
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

	double noise3D(double x, double y,double z,double scalex =1.f,double scaley = 1.f,double scalez = 1.f) const{

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
	Vec3 noise3D_Vec3(double x, double y, double z, double scalex = 1.f, double scaley = 1.f, double scalez = 1.f) const {

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
		Vec3 result = dataVec[datai];

		return result;

	}

	// xi yi zi in [0,255]
	//return value [0,255]
	int hash(int xi,int yi, int zi) {
		int datai = (xi ^ yi ^ zi);

		return datai;
	
	}



	double fbm(const Point3& point,int octaves = 3) const{

		//double weight1 = 1.f;
		//double weight2 = weight1 / 2.f;
		//double weight3 = weight2 / 2.f;
		//double scale1 = 1.f;
		//double scale2 = 2.f * scale1;
		//double scale3 = 2.f * scale2;
		//double perlin1 = weight1*noise_perlin_interp(scale1*point);
		//double perlin2 = weight2 * noise_perlin_interp(scale2*point);
		//double perlin3 = weight3 * noise_perlin_interp(scale3*point);

		//double result = perlin1 + perlin2 + perlin3;
		//result = result / (1.f + 1 / 2.f + 1 / 4.f);
		double weight = 1.f;
		double scale = 1.f;
		double sum = 0.f;
		double norm_sum = 0.f;
		for (int i = 1; i <= octaves; i++) {

			double perlin = weight * noise_perlin_interp(scale*point);
			sum = sum +  perlin;
			norm_sum = norm_sum + weight;
			weight = weight * 1 / 2.f;
			scale = scale * 2.f;

		}


		double result = (sum+norm_sum) / (2.f*norm_sum);
		//double result = clamp(sum);
		return  result;
	
	
	}



	double turbulance(const Point3& point, int octaves = 3) const{

		double weight = 1.f;
		double scale = 1.f;
		double sum = 0.f;
		double norm_sum = 0.f;

		for (int i = 1; i <= octaves; i++) {
			//double perlin_neg1_1 = noise_perlin_interp(scale * point) * 2.f - 1.f;
			double perlin_neg1_1 = noise_perlin_interp(scale*point);
			double perlin = weight * fabs(perlin_neg1_1);
			sum = sum + perlin;
			norm_sum = norm_sum + weight;
			weight = weight * 1 / 2.f;
			scale = scale * 2.f;

		}

		double result = sum / norm_sum;
		//double result = clamp(sum,0.f,1.f);

		return  result;


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
	Vec3* dataVec;
	int* dataX;
	int* dataY;
	int* dataZ;

	double scalex;
	double scaley;
	double scalez;


};

#endif