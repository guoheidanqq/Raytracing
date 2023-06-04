#ifndef SOLIDCOLOR_H
#define SOLIDCOLOR_H

#include "Texture.h"
#include "Vec3.h"
class SolidColor :public Texture{

public:
	SolidColor(){}
	SolidColor(const Color& color){
	this->color = color;
	}

	SolidColor(double red, double green, double blue){
	Color color(red,green,blue);
	this->color = color;
	
	}


	virtual Color getTexture(double s, double t, const Point3& point) override{
	return this->color;
	
	}


public:
	Color color;

};

#endif