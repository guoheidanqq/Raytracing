#ifndef VEC3_H
#define VEC3_H

#include <cmath>

class Vec3{

public:
	Vec3(){
	this->v[0]=0;
	this->v[1]=0;
	this->v[2]=0;
	}

	Vec3(double x, double y,double z ){

	this->v[0]=x;
	this->v[1]=y;
	this->v[2]=z;
	}

	double operator[](int i) const {
	  return this->v[i];
	}

	double& operator[](int i)  {
	  return this->v[i];
	}



	Vec3 operator-(){
		Vec3 result(this->v[0],this->v[1],this->v[2]);
		return result;
	}

	Vec3& operator+=(const Vec3& b){
		this->v[0]+= b.v[0];
		this->v[1]+= b.v[1];
		this->v[2]+= b.v[2];
		return *this;	
	}

	Vec3& operator*=(const double t){
		this->v[0]*=t;
		this->v[1]*=t;
		this->v[2]*= t;
		return *this;	
	}

	Vec3& operator/=(const double t){
		this->v[0]/=t;
		this->v[1]/=t;
		this->v[2]/= t;
		return *this;	
	}



	double length()const{
	return sqrt(this->v[0]*this->v[0] + this->v[1]*this->v[1] + this->v[2]*this->v[2]);
	}

	double x() const{
		return this->v[0];
	}
	double y() const {
	return this->v[1];
	}
	
	double z() const{
	return this->v[2];
	}



public:

	double v[3];

};


Vec3 operator+(const Vec3& a , const Vec3& b){
	Vec3 result(a.v[0]+b.v[0],a.v[1]+b.v[1],a.v[2]+b.v[2]);
	return result;

}


Vec3 operator-(const Vec3& a , const Vec3& b){
	Vec3 result(a.v[0]-b.v[0],a.v[1]-b.v[1],a.v[2]-b.v[2]);
	return result;

}

Vec3 operator*(double t, const Vec3& a){
	Vec3 result(a.v[0]*t,a.v[1]*t,a.v[2]*t);
	return result;	

}



Vec3 operator*( const Vec3& a, double t){
	Vec3 result(a.v[0]*t,a.v[1]*t,a.v[2]*t);
	return result;	

}


Vec3 operator*( const Vec3& a, const Vec3& b){
	Vec3 result(a.v[0]*b.v[0],a.v[1]*b.v[1],a.v[2]*b.v[2]);
	return result;	

}

Vec3 operator/( const Vec3& a, double t){
	Vec3 result(a.v[0]/t,a.v[1]/t,a.v[2]/t);
	return result;	

}


double dot(const Vec3& a , const Vec3& b){
	return (a.v[0]*b.v[0] + a.v[1]*b.v[1]+ a.v[2]*b.v[2]);
}

Vec3 cross(const Vec3& a , const Vec3& b){
	Vec3 result(a.v[1] * b.v[2] - a.v[2] * b.v[1],
                 a.v[2] * b.v[0] - a.v[0] * b.v[2],
                 a.v[0] * b.v[1] - a.v[1] * b.v[0]);

	return result;
}

Vec3 normal(const Vec3& a){
	double len = a.length();
	return Vec3(a.v[0]/len,a.v[1]/len,a.v[2]/len);
}

std::ostream& operator<<(std::ostream& out,const Vec3& a){
	return out<< a.v[0] << " "<<a.v[1]<<" "<<a.v[2]<<std::endl;
}


typedef Vec3 Point3;
typedef Vec3 Color; 
//using Color = Vec3;

#endif