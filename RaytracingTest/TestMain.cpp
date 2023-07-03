#include <iostream>
#include "PerlinNoise.h"
#include "Tools.h"

using namespace std;
int main() {

	double a = 1;
	double b = 2;

	double result = lerp(a, b, 0.1);
	double sresult = smoothstep(a,b,1);







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