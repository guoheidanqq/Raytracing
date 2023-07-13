#ifndef  PERLIN_NOISE_TEXTURE_H
#define  PERLIN_NOISE_TEXTURE_H
#include "PerlinNoise.h"
#include "Texture.h"
class PerlinNoiseTexture :public Texture {
public:

	PerlinNoiseTexture(double scalex = 1.f, double scaley = 1.f, double scalez = 1.f) {

		perlin.scalex = scalex;
		perlin.scaley = scaley;
		perlin.scalez = scalez;
	
	}

	virtual Color getTexture(double s, double t, const Point3& point) override {
	
		//double result = (perlin.noise_linear_interp(point) + 1.f)/2.f;
		//double result = (perlin.noise_smoothstep_interp(point) + 1.f)/2.f;
		//double result = (perlin.noise_perlin_interp(point)+1.f)/2.f;
		double result = perlin.fbm(point,1);
		//double result = perlin.turbulance(point,3);
		//result = sqrt(result);
		Color color(result,result,result);

		return color;
	}







private:
	PerlinNoise perlin;



};


#endif 

