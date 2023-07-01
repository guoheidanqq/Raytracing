#include <iostream>
#include "PerlinNoise.h"
using namespace std;
int main() {

	PerlinNoise perlin;
	perlin.noise1D(1);

	perlin.display(perlin.data);
	cout << "hello world" << endl;
	perlin.display(perlin.dataX);
	perlin.display(perlin.dataY);
	perlin.display(perlin.dataZ);

	double x = -10;
	double d = perlin.noise1D(x);
	cout << d << endl;


	system("pause");
	return 0;
}