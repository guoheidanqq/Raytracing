#ifndef TRANSFORM_H
#define TRANSFORM_H
#include "IHittable.h"

class Matrix {
public:
	Matrix() {
		this->setIdentity();
		
	}

	Matrix(double a, double b, double c,double d,
			double e, double f, double g, double h,
			double i, double j, double k,double l,
			double m, double n, double o, double p) {
		this->mat[0][0] = a;
		this->mat[0][1] = b;
		this->mat[0][2] = c;
		this->mat[0][3] = d;
		this->mat[1][0] = e;
		this->mat[1][1] = f;
		this->mat[1][2] = g;
		this->mat[1][3] = h;
		this->mat[2][0] = i;
		this->mat[2][1] = j;
		this->mat[2][2] = k;
		this->mat[2][3] = l;
		this->mat[3][0] = m;
		this->mat[3][1] = n;
		this->mat[3][2] = o;
		this->mat[3][3] = p;
	
	}

	void setIdentity() {
		const int size = 4;
		for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++) {
				mat[i][j] = 0.f;
			}
		mat[0][0] = 1.f;
		mat[1][1] = 1.f;
		mat[2][2] = 1.f;
		mat[3][3] = 1.f;
	}

	void inverse() {

		if (this->det() <=  0.0000001f) {
			return;
		}
		double a = mat[0][0];
		double b = mat[0][1];
		double c = mat[0][2];
		double d = mat[0][3];
		double e = mat[1][0];
		double f = mat[1][1];
		double g = mat[1][2];
		double h = mat[1][3];
		double i = mat[2][0];
		double j = mat[2][1];
		double k = mat[2][2];
		double l = mat[2][3];
		double m = mat[3][0];
		double n = mat[3][1];
		double o = mat[3][2];
		double p = mat[3][3];
		mat[0][0] = (f * k * p - f * l * o - g * j * p + g * l * n + h * j * o - h * k * n) / (a * f * k * p - a * f * l * o - a * g * j * p + a * g * l * n + a * h * j * o - a * h * k * n - b * e * k * p + b * e * l * o + b * g * i * p - b * g * l * m - b * h * i * o + b * h * k * m + c * e * j * p - c * e * l * n - c * f * i * p + c * f * l * m + c * h * i * n - c * h * j * m - d * e * j * o + d * e * k * n + d * f * i * o - d * f * k * m - d * g * i * n + d * g * j * m);
		mat[0][1] = -(b * k * p - b * l * o - c * j * p + c * l * n + d * j * o - d * k * n) / (a * f * k * p - a * f * l * o - a * g * j * p + a * g * l * n + a * h * j * o - a * h * k * n - b * e * k * p + b * e * l * o + b * g * i * p - b * g * l * m - b * h * i * o + b * h * k * m + c * e * j * p - c * e * l * n - c * f * i * p + c * f * l * m + c * h * i * n - c * h * j * m - d * e * j * o + d * e * k * n + d * f * i * o - d * f * k * m - d * g * i * n + d * g * j * m);
		mat[0][2] = (b * g * p - b * h * o - c * f * p + c * h * n + d * f * o - d * g * n) / (a * f * k * p - a * f * l * o - a * g * j * p + a * g * l * n + a * h * j * o - a * h * k * n - b * e * k * p + b * e * l * o + b * g * i * p - b * g * l * m - b * h * i * o + b * h * k * m + c * e * j * p - c * e * l * n - c * f * i * p + c * f * l * m + c * h * i * n - c * h * j * m - d * e * j * o + d * e * k * n + d * f * i * o - d * f * k * m - d * g * i * n + d * g * j * m);
		mat[0][3] = -(b * g * l - b * h * k - c * f * l + c * h * j + d * f * k - d * g * j) / (a * f * k * p - a * f * l * o - a * g * j * p + a * g * l * n + a * h * j * o - a * h * k * n - b * e * k * p + b * e * l * o + b * g * i * p - b * g * l * m - b * h * i * o + b * h * k * m + c * e * j * p - c * e * l * n - c * f * i * p + c * f * l * m + c * h * i * n - c * h * j * m - d * e * j * o + d * e * k * n + d * f * i * o - d * f * k * m - d * g * i * n + d * g * j * m);
		mat[1][0] = -(e * k * p - e * l * o - g * i * p + g * l * m + h * i * o - h * k * m) / (a * f * k * p - a * f * l * o - a * g * j * p + a * g * l * n + a * h * j * o - a * h * k * n - b * e * k * p + b * e * l * o + b * g * i * p - b * g * l * m - b * h * i * o + b * h * k * m + c * e * j * p - c * e * l * n - c * f * i * p + c * f * l * m + c * h * i * n - c * h * j * m - d * e * j * o + d * e * k * n + d * f * i * o - d * f * k * m - d * g * i * n + d * g * j * m);
		mat[1][1] = (a * k * p - a * l * o - c * i * p + c * l * m + d * i * o - d * k * m) / (a * f * k * p - a * f * l * o - a * g * j * p + a * g * l * n + a * h * j * o - a * h * k * n - b * e * k * p + b * e * l * o + b * g * i * p - b * g * l * m - b * h * i * o + b * h * k * m + c * e * j * p - c * e * l * n - c * f * i * p + c * f * l * m + c * h * i * n - c * h * j * m - d * e * j * o + d * e * k * n + d * f * i * o - d * f * k * m - d * g * i * n + d * g * j * m);
		mat[1][2] = -(a * g * p - a * h * o - c * e * p + c * h * m + d * e * o - d * g * m) / (a * f * k * p - a * f * l * o - a * g * j * p + a * g * l * n + a * h * j * o - a * h * k * n - b * e * k * p + b * e * l * o + b * g * i * p - b * g * l * m - b * h * i * o + b * h * k * m + c * e * j * p - c * e * l * n - c * f * i * p + c * f * l * m + c * h * i * n - c * h * j * m - d * e * j * o + d * e * k * n + d * f * i * o - d * f * k * m - d * g * i * n + d * g * j * m);
		mat[1][3] = (a * g * l - a * h * k - c * e * l + c * h * i + d * e * k - d * g * i) / (a * f * k * p - a * f * l * o - a * g * j * p + a * g * l * n + a * h * j * o - a * h * k * n - b * e * k * p + b * e * l * o + b * g * i * p - b * g * l * m - b * h * i * o + b * h * k * m + c * e * j * p - c * e * l * n - c * f * i * p + c * f * l * m + c * h * i * n - c * h * j * m - d * e * j * o + d * e * k * n + d * f * i * o - d * f * k * m - d * g * i * n + d * g * j * m);
		mat[2][0] = (e * j * p - e * l * n - f * i * p + f * l * m + h * i * n - h * j * m) / (a * f * k * p - a * f * l * o - a * g * j * p + a * g * l * n + a * h * j * o - a * h * k * n - b * e * k * p + b * e * l * o + b * g * i * p - b * g * l * m - b * h * i * o + b * h * k * m + c * e * j * p - c * e * l * n - c * f * i * p + c * f * l * m + c * h * i * n - c * h * j * m - d * e * j * o + d * e * k * n + d * f * i * o - d * f * k * m - d * g * i * n + d * g * j * m);
		mat[2][1] = -(a * j * p - a * l * n - b * i * p + b * l * m + d * i * n - d * j * m) / (a * f * k * p - a * f * l * o - a * g * j * p + a * g * l * n + a * h * j * o - a * h * k * n - b * e * k * p + b * e * l * o + b * g * i * p - b * g * l * m - b * h * i * o + b * h * k * m + c * e * j * p - c * e * l * n - c * f * i * p + c * f * l * m + c * h * i * n - c * h * j * m - d * e * j * o + d * e * k * n + d * f * i * o - d * f * k * m - d * g * i * n + d * g * j * m);
		mat[2][2] = (a * f * p - a * h * n - b * e * p + b * h * m + d * e * n - d * f * m) / (a * f * k * p - a * f * l * o - a * g * j * p + a * g * l * n + a * h * j * o - a * h * k * n - b * e * k * p + b * e * l * o + b * g * i * p - b * g * l * m - b * h * i * o + b * h * k * m + c * e * j * p - c * e * l * n - c * f * i * p + c * f * l * m + c * h * i * n - c * h * j * m - d * e * j * o + d * e * k * n + d * f * i * o - d * f * k * m - d * g * i * n + d * g * j * m);
		mat[2][3] = -(a * f * l - a * h * j - b * e * l + b * h * i + d * e * j - d * f * i) / (a * f * k * p - a * f * l * o - a * g * j * p + a * g * l * n + a * h * j * o - a * h * k * n - b * e * k * p + b * e * l * o + b * g * i * p - b * g * l * m - b * h * i * o + b * h * k * m + c * e * j * p - c * e * l * n - c * f * i * p + c * f * l * m + c * h * i * n - c * h * j * m - d * e * j * o + d * e * k * n + d * f * i * o - d * f * k * m - d * g * i * n + d * g * j * m);
		mat[3][0] = -(e * j * o - e * k * n - f * i * o + f * k * m + g * i * n - g * j * m) / (a * f * k * p - a * f * l * o - a * g * j * p + a * g * l * n + a * h * j * o - a * h * k * n - b * e * k * p + b * e * l * o + b * g * i * p - b * g * l * m - b * h * i * o + b * h * k * m + c * e * j * p - c * e * l * n - c * f * i * p + c * f * l * m + c * h * i * n - c * h * j * m - d * e * j * o + d * e * k * n + d * f * i * o - d * f * k * m - d * g * i * n + d * g * j * m);
		mat[3][1] = (a * j * o - a * k * n - b * i * o + b * k * m + c * i * n - c * j * m) / (a * f * k * p - a * f * l * o - a * g * j * p + a * g * l * n + a * h * j * o - a * h * k * n - b * e * k * p + b * e * l * o + b * g * i * p - b * g * l * m - b * h * i * o + b * h * k * m + c * e * j * p - c * e * l * n - c * f * i * p + c * f * l * m + c * h * i * n - c * h * j * m - d * e * j * o + d * e * k * n + d * f * i * o - d * f * k * m - d * g * i * n + d * g * j * m);
		mat[3][2] = -(a * f * o - a * g * n - b * e * o + b * g * m + c * e * n - c * f * m) / (a * f * k * p - a * f * l * o - a * g * j * p + a * g * l * n + a * h * j * o - a * h * k * n - b * e * k * p + b * e * l * o + b * g * i * p - b * g * l * m - b * h * i * o + b * h * k * m + c * e * j * p - c * e * l * n - c * f * i * p + c * f * l * m + c * h * i * n - c * h * j * m - d * e * j * o + d * e * k * n + d * f * i * o - d * f * k * m - d * g * i * n + d * g * j * m);
		mat[3][3] = 0.1e1 / (a * f * k * p - a * f * l * o - a * g * j * p + a * g * l * n + a * h * j * o - a * h * k * n - b * e * k * p + b * e * l * o + b * g * i * p - b * g * l * m - b * h * i * o + b * h * k * m + c * e * j * p - c * e * l * n - c * f * i * p + c * f * l * m + c * h * i * n - c * h * j * m - d * e * j * o + d * e * k * n + d * f * i * o - d * f * k * m - d * g * i * n + d * g * j * m) * (a * f * k - a * g * j - b * e * k + b * g * i + c * e * j - c * f * i);


	}

	double det() const {
		double a = mat[0][0];
		double b = mat[0][1];
		double c = mat[0][2];
		double d = mat[0][3];
		double e = mat[1][0];
		double f = mat[1][1];
		double g = mat[1][2];
		double h = mat[1][3];
		double i = mat[2][0];
		double j = mat[2][1];
		double k = mat[2][2];
		double l = mat[2][3];
		double m = mat[3][0];
		double n = mat[3][1];
		double o = mat[3][2];
		double p = mat[3][3];
		double result = a * f * k * p - a * f * l * o - a * g * j * p + a * g * l * n 
			+ a * h * j * o - a * h * k * n
			- b * e * k * p + b * e * l * o + b * g * i * p - b * g * l * m 
			- b * h * i * o + b * h * k * m + c * e * j * p - c * e * l * n
			- c * f * i * p + c * f * l * m + c * h * i * n - c * h * j * m 
			- d * e * j * o + d * e * k * n + d * f * i * o - d * f * k * m
			- d * g * i * n + d * g * j * m;
		return result;
	}

	Matrix transpose() {
	
		Matrix tMat;
		for(int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++) {
				tMat.mat[i][j] = this->mat[j][i];
			
			}
		
		return tMat;
	
	}

public:
	double mat[4][4];
};

Matrix multiply(const Matrix& a, const Matrix& b)  {
	const int size = 4;
	Matrix result;	
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++) {
			result.mat[i][j] = 0.f;
			for (int k = 0; k < size; k++)
				result.mat[i][j] = result.mat[i][j] + a.mat[i][k] * b.mat[k][j];
		}
	return result;
}

Matrix inverse(const Matrix& a) {
	Matrix result = a;
	result.inverse();
	return result;
}

class Transform {
public:
	Transform() {
		transMat.setIdentity();	
		invTransMat.setIdentity();
	}


	void begin() {
		transMat.setIdentity();
		invTransMat.setIdentity();
	}

	void end() {
		invTransMat=inverse(transMat);
	}
	void tranlate(double dx, double dy ,double dz) {
		Matrix translateMat(1.f,0.f,0.f,dx,
							0.f,1.f,0.f,dy,
							0.f,0.f,1.f,dz,
							0.f,0.f,0.f,1.f);
		Matrix result = multiply(translateMat,transMat);
		transMat = result;
	}

	void scale(double sx, double sy, double sz) {
		Matrix scaleMat(sx, 0.f, 0.f, 0.f,
						0.f, sy, 0.f, 0.f,
						0.f, 0.f, sz, 0.f,
						0.f, 0.f, 0.f, 1.f);
		Matrix result = multiply(scaleMat, transMat);
		transMat = result;

	}

	void rotateX(double degree) {
		// delta Theta in degree 
		double theta = radian2degree(degree);
		Matrix rotateXMat( 1.f,       0.f,          0.f,  0.f,
							0.f, cos(theta), -sin(theta), 0.f,
							0.f, sin(theta), cos(theta),  0.f,
							0.f,        0.f,        0.f,  1.f);
		Matrix result = multiply(rotateXMat, transMat);
		transMat = result;
	
	}

	void rotateY(double degree) {
		double theta = radian2degree(degree);
		Matrix rotateYMat(cos(theta), 0.f, sin(theta), 0.f,
								0.f,  1.f,       0.f,  0.f,
						  -sin(theta), 0.f, cos(theta), 0.f,
							0.f, 0.f, 0.f, 1.f);
		Matrix result = multiply(rotateYMat, transMat);
		transMat = result;

	}
	void rotateZ(double degree) {
		double theta = radian2degree(degree);
		Matrix rotateZMat(cos(theta), -sin(theta), 0.f, 0.f,
						   sin(theta), cos(theta), 0.f, 0.f,
								  0.f,        0.f,  1.f, 0.f,
							      0.f,         0.f, 0.f, 1.f);
		Matrix result = multiply(rotateZMat, transMat);
		transMat = result;
	
	}

	Point3 applyToPoint(const Point3& point) const {
		
		double a = transMat.mat[0][0];
		double b = transMat.mat[0][1];
		double c = transMat.mat[0][2];
		double d = transMat.mat[0][3];
		double e = transMat.mat[1][0];
		double f = transMat.mat[1][1];
		double g = transMat.mat[1][2];
		double h = transMat.mat[1][3];
		double i = transMat.mat[2][0];
		double j = transMat.mat[2][1];
		double k = transMat.mat[2][2];
		double l = transMat.mat[2][3];
		double m = transMat.mat[3][0];
		double n = transMat.mat[3][1];
		double o = transMat.mat[3][2];
		double p = transMat.mat[3][3];
		double x = point.x();
		double y = point.y();
		double z = point.z();
		double newX = a * x + b * y + c * z + d;
		double newY = e * x + f * y + g * z + h;
		double newZ = i * x + j * y + k * z + l;
		double newW = m * x + n * y + o * z + p;

		return Point3(newX,newY,newZ);
	}

	Vec3 applyToVector(const Vec3& vec) const {

		double a = transMat.mat[0][0];
		double b = transMat.mat[0][1];
		double c = transMat.mat[0][2];
		double d = transMat.mat[0][3];
		double e = transMat.mat[1][0];
		double f = transMat.mat[1][1];
		double g = transMat.mat[1][2];
		double h = transMat.mat[1][3];
		double i = transMat.mat[2][0];
		double j = transMat.mat[2][1];
		double k = transMat.mat[2][2];
		double l = transMat.mat[2][3];
		double m = transMat.mat[3][0];
		double n = transMat.mat[3][1];
		double o = transMat.mat[3][2];
		double p = transMat.mat[3][3];
		double x = vec.x();
		double y = vec.y();
		double z = vec.z();
		double newX = a * x + b * y + c * z;
		double newY = e * x + f * y + g * z;
		double newZ = i * x + j * y + k * z;
		double newW = m * x + n * y + o * z;

		return Vec3(newX, newY, newZ);

	}


	Point3 inverseApplyToPoint(const Point3& point) {
		double a = invTransMat.mat[0][0];
		double b = invTransMat.mat[0][1];
		double c = invTransMat.mat[0][2];
		double d = invTransMat.mat[0][3];
		double e = invTransMat.mat[1][0];
		double f = invTransMat.mat[1][1];
		double g = invTransMat.mat[1][2];
		double h = invTransMat.mat[1][3];
		double i = invTransMat.mat[2][0];
		double j = invTransMat.mat[2][1];
		double k = invTransMat.mat[2][2];
		double l = invTransMat.mat[2][3];
		double m = invTransMat.mat[3][0];
		double n = invTransMat.mat[3][1];
		double o = invTransMat.mat[3][2];
		double p = invTransMat.mat[3][3];
		double x = point.x();
		double y = point.y();
		double z = point.z();
		double newX = a * x + b * y + c * z + d;
		double newY = e * x + f * y + g * z + h;
		double newZ = i * x + j * y + k * z + l;
		double newW = m * x + n * y + o * z + p;

		return Point3(newX, newY, newZ);
	}

	Vec3 inverseApplyToVector(const Vec3& vec) {
		double a = invTransMat.mat[0][0];
		double b = invTransMat.mat[0][1];
		double c = invTransMat.mat[0][2];
		double d = invTransMat.mat[0][3];
		double e = invTransMat.mat[1][0];
		double f = invTransMat.mat[1][1];
		double g = invTransMat.mat[1][2];
		double h = invTransMat.mat[1][3];
		double i = invTransMat.mat[2][0];
		double j = invTransMat.mat[2][1];
		double k = invTransMat.mat[2][2];
		double l = invTransMat.mat[2][3];
		double m = invTransMat.mat[3][0];
		double n = invTransMat.mat[3][1];
		double o = invTransMat.mat[3][2];
		double p = invTransMat.mat[3][3];
		double x = vec.x();
		double y = vec.y();
		double z = vec.z();
		double newX = a * x + b * y + c * z;
		double newY = e * x + f * y + g * z;
		double newZ = i * x + j * y + k * z;
		double newW = m * x + n * y + o * z;

		return Vec3(newX, newY, newZ);
	}

	Vec3 applyToNormal(const Vec3& normal) {
		Matrix invMT = invTransMat.transpose();
		double a = invMT.mat[0][0];
		double b = invMT.mat[0][1];
		double c = invMT.mat[0][2];
		double d = invMT.mat[0][3];
		double e = invMT.mat[1][0];
		double f = invMT.mat[1][1];
		double g = invMT.mat[1][2];
		double h = invMT.mat[1][3];
		double i = invMT.mat[2][0];
		double j = invMT.mat[2][1];
		double k = invMT.mat[2][2];
		double l = invMT.mat[2][3];
		double m = invMT.mat[3][0];
		double n = invMT.mat[3][1];
		double o = invMT.mat[3][2];
		double p = invMT.mat[3][3];
		double x = normal.x();
		double y = normal.y();
		double z = normal.z();
		double newX = a * x + b * y + c * z;
		double newY = e * x + f * y + g * z;
		double newZ = i * x + j * y + k * z;
		double newW = m * x + n * y + o * z;

		return Vec3(newX, newY, newZ);
	}
public:

	Matrix transMat;
	Matrix invTransMat;




};






#endif
