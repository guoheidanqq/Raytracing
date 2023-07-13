#include <algorithm>
#include <iostream>
#include "Vec3.h"
#include "Ray.h"
#include "Sphere.h"
#include "Scene.h"
#include "Camera.h"
#include "Tools.h"
#include "Labertian.h"
#include "Metal.h"
#include "CheckerTexture.h"
#include "ImageTexture.h"
#include "SolidColor.h"
#include "DiffuseLight.h"
#include "RectangleZ.h"
#include "RectangleX.h"
#include "RectangleY.h"
#include "Glass.h"
#include "AABB.h"
#include "BVH.h"
#include "Cube.h"
#include "Transform.h"
#include "InstanceFactory.h"
#include "IsotropicVolume.h"
#include "VolumeRegion.h"
#include "PerlinNoiseTexture.h"
#include "WorleyNoise.h"

using namespace std;
int main() {

	
	WorleyNoise worley;
	double result0 = worley.noise1D(9.6,0);
	double result1 = worley.noise1D(9.6,1);
	double result2 = worley.noise1D(9.6,2);
	double result3 = worley.noise2D(9.6, 10.3,0);
	double result4 = worley.noise2D(9.6,10.3, 1);
	double result5 = worley.noise2D(9.6,10.3,2);
	double result6 = worley.noise3D(9.6, 9.6,10.3,0);
	double result7 = worley.noise3D(9.6, 9.6,10.3,1);
	double result8 = worley.noise3D(9.6,9.6,10.3, 2);
	cout << result0 << endl;
	cout << result1 << endl;
	cout << result2 << endl;
	cout << result3 << endl;
	cout << result4 << endl;
	cout << result5 << endl;
	cout << result6 << endl;
	cout << result7 << endl;
	cout << result8 << endl;





	//double a = 1;
	//double b = 2;

	//double result = lerp(a, b, 0.1);
	//double sresult = smoothstep(a,b,1);
	//PerlinNoise perlin;
	//double perlinResult = perlin.noise_perlin_interp(Point3(3.1,4.2,5.3));







	//PerlinNoise perlin;
	//perlin.noise1D(1);

	//perlin.display(perlin.data);
	//cout << "hello world" << endl;
	//perlin.display(perlin.dataX);
	//perlin.display(perlin.dataY);
	//perlin.display(perlin.dataZ);

	//double x = -10;
	//double y = 10;
	//double z = 1000;
	//Point3 point(x,y,z);
	//double d1 = perlin.noise1D(x);
	//double d2 = perlin.noise2D(x,y);
	//double d3 = perlin.noise3D(x,y,z);
	//double d4 = perlin.noise(point);
	//cout << d1 << endl;


	system("pause");
	return 0;
}