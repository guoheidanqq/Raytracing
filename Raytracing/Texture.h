#ifndef TEXTURE_H
#define TEXTURE_H
#include "Vec3.h"

class Texture{
public:
	virtual Color getTexture(double s, double t, const Point3& point)=0;
};





#endif