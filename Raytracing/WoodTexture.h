#ifndef WOOD_TEXTURE_H
#define WOOD_TEXTURE_H
#include "PerlinNoise.h"
#include "Texture.h"
#include "Tools.h"
class WoodTexture :public Texture {
public:

	WoodTexture(const double width = 0.2f, const Color& blackColor = Color(0.157f, 0.078f, 0.039f), const Color& whiteColor = Color(0.824f, 0.627f, 0.471f)) {

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
		Color color = this->stripe_interp(point, kPhase);
		return color;
	}


	Color stripe(const Point3& point) const {
		const double pi = 3.1415926;
		double x = point.x();
		double y = point.y();
		double z = point.z();
		double distance = sqrt(x * x + z * z);
		double d = sin(2 * pi * x / this->width);

		if (d >= 0) {
			return this->whiteColor;
		}

		if (d < 0) {
			return this->blackColor;
		}

	}

	Color stripe_interp(const Point3& point, const double kPhase = 1.f) {
		const double pi = 3.1415926;
		double x = point.x();
		double y = point.y();
		double z = point.z();
		double distance = sqrt(x * x + z * z);
		perlin.scalex = 1;
		perlin.scaley = 1;
		perlin.scalez = 1;
		//double phaseTurb = kPhase * perlin.turbulance(point, 3);
		double phaseFbm = kPhase * perlin.fbm(point);
		//double d = sin(2 * pi *  distance/ this->width + phaseTurb);
		double d = sin(2 * pi * distance / this->width + phaseFbm);
		double t = (1.f + d) / 2.f;

		Color result = lerpVec3(this->whiteColor, this->blackColor, t);
		return result;



	}




private:
	PerlinNoise perlin;
	Color whiteColor;
	Color blackColor;
	double width;






};


#endif
