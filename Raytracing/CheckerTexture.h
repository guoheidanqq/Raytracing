#ifndef CHECKERTEXTURE_H
#define CHECKERTEXTURE_H
#include <cmath>
#include "Texture.h"
#include "Vec3.h"
class CheckerTexture:public Texture{

public:

	CheckerTexture(){
	this->oddColor = Color(0.f,0.f,0.f);
	this->evenColor = Color(1.f,1.f,1.f);
	
	}
	virtual Color getTexture(double s, double t, const Point3& point)override{
	 double flag = sin(point.x()*10)*sin(point.y()*10)*sin(point.z()*10);
	 if(flag<=0){
	   return oddColor;
	 }
	 if(flag>=0){
	 return evenColor;
	 }
	 	
	}

public:
	Color oddColor;
	Color evenColor;


};






#endif
