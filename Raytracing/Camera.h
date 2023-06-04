#ifndef CAMERA_H
#define CAMERA_H

class Camera{

public:

	Camera(){
		double Ratiotmp = 16.0f/9.0f;
		double H = 2.f;
		double W = H*Ratiotmp;
		double F = 1.f;
		Point3 lbPointTmp(-W/2.0f,-H/2.0f,-F);
		Vec3 UVec(W,0,0);
		Vec3 VVec(0,H,0);
		this->U = normal(UVec);
		this->V = normal(VVec);
		this->lbPoint = lbPointTmp;
		this->Ratio = Ratiotmp;
		this->Width = W;
		this->Height = H;
	}


	Camera(double thetaInDegree){
		const double pi = 3.1415926f;
		double theta = thetaInDegree/180.f*pi;

		double Ratiotmp = 16.0f/9.0f;
		double H = 2.f * tan(theta/2.0f);
		double W = H*Ratiotmp;
		double F = 1.f;
		Point3 lbPointTmp(-W/2.0f,-H/2.0f,-F);
		Vec3 UVec(W,0,0);
		Vec3 VVec(0,H,0);
		this->U = normal(UVec);
		this->V = normal(VVec);
		this->lbPoint = lbPointTmp;
		this->Ratio = Ratiotmp;
		this->Width = W;
		this->Height = H;
	
	}
	


	Camera(double thetaInDegree,Point3 eye, Point3 lookat,Vec3 up){
		const double pi = 3.1415926f;
		double theta = thetaInDegree/180.f*pi;
		double Ratiotmp = 16.0f/9.0f;
		double H = 2.f * tan(theta/2.0f);
		double W = H*Ratiotmp;
		double F = 1.f;

		Vec3 vecW = normal(eye-lookat);
		Vec3 vecU =  normal(cross(up,vecW));
		Vec3 vecV  = normal(cross(vecW,vecU));
		Point3 lbPointTmp = eye - vecU*W/2.f - vecV*H/2.f -vecW*1.0f;
	
		this->origin = eye;
		this->U = vecU;
		this->V = vecV;
		this->W = vecW;
		this->lbPoint = lbPointTmp;
		this->Ratio = Ratiotmp;
		this->Width = W;
		this->Height = H;
	
	
	}





	Ray getRay(double u, double v){
		Ray ray(this->origin,this->lbPoint + u*this->U*this->Width + v*this->V*this->Height - this->origin);
		return ray;
	
	}

public:
	Point3 origin;
	double Width;
	double Height;
	Vec3 U;
	Vec3 V;
	Vec3 W;
	Point3 lbPoint;
	double Ratio;

};








#endif