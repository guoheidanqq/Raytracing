#ifndef MARBLE_TEXTURE_H
#define MARBLE_TEXTURE_H

#include "PerlinNoise.h"
#include "Texture.h"
class MarbleTexture :public Texture {
public:

	MarbleTexture(const double width=1.f, const Color& blackColor = Color(0.f,0.f,0.f), const Color& whiteColor =Color(1.f,1.f,1.f)) {

		double scalex = 1.f; 
		double scaley = 1.f;
		double scalez = 1.f;
		perlin.scalex = scalex;
		perlin.scaley = scaley;
		perlin.scalez = scalez;
		this->whiteColor = blackColor;
		this->blackColor = whiteColor;
		this->width = width;
	


	}

	virtual Color getTexture(double s, double t, const Point3& point) override {



		//Color color = this->stripe(point);
		double kPhase = 30.f;
		Color color = this->stripe_interp(point,kPhase);
		return color;
	}


	Color stripe(const Point3& point) const {
		const double pi = 3.1415926;
		double x = point.x();
		double d = sin(2*pi*x/this->width);
		
		if (d >= 0) {
			return this->whiteColor;
		}

		if (d < 0) {
			return this->blackColor;
		}
	
	}

	Color stripe_interp(const Point3& point, const double kPhase = 30.f)  {
		const double pi = 3.1415926;
		double x = point.x();
		perlin.scalex = 1;
		perlin.scaley = 1;
		perlin.scalez = 1;
		double phaseTurb =kPhase  * perlin.turbulance(point,3);
		double d = sin(2 * pi * x/this->width  + phaseTurb);
		double t = (1.f + d) / 2.f;

		Color result = lerpVec3(this->whiteColor, this->blackColor,t);
		return result;



	}




private:
	PerlinNoise perlin;
	Color whiteColor;
	Color blackColor;
	double width;






};




#endif
