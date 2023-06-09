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


using namespace std;

Color raytracing(Ray& ray,Scene& scene, int level = 5);

void write_color(ostream& out, Color tracingColor){



out<<int(clamp(tracingColor.x())*255)<<" "<<int(clamp(tracingColor.y())*255)<<" "<<int(clamp(tracingColor.z())*255)<<endl;

}





Color raytracing(Ray& ray,Scene& scene, int level){

	if(level <= 0){
		return Color(0.f,0.f,0.f);
	
	}

	if(level >=1){

		HitInfo hitInfo;
		double tMin = 0.001f;
		double tMax = 1000000.f;
		bool isHit = scene.hit(ray,hitInfo,tMin,tMax);
		if(isHit){

			Point3 hitPoint = hitInfo.hitPoint;
			double hitTime = hitInfo.hitTime;
			Vec3 N = hitInfo.N;
			Material* material = hitInfo.hitMaterial;
			double ss = hitInfo.ss;
			double tt = hitInfo.tt;
			

			if(material->isLightMaterial()==true){
				Color result = material->emitted(ss,tt,hitPoint);
				return  result;
			}

			if(material->isLightMaterial() == false){
			
			Color attenuationColor(0.f,0.f,0.f);
			Ray scatterRay;
			bool isScatter = material->scatter(ray,hitInfo,attenuationColor,scatterRay);
			if (isScatter) {
				Ray newRay = scatterRay;

				int nextlevel = level - 1;
				Color nextHitColor = raytracing(newRay, scene, nextlevel);

				Color newColor = attenuationColor * nextHitColor;
				return newColor;
			}
			if (!isScatter) {
				return Color(0.f,0.f,0.f);
			}

			
			}



		}

		if(!isHit){
			Color WhiteColor(1.0,1.0,1.0);
			Color SkyBlueColor(0.5,0.7,1.0);
			double y = ray.dir.y();//-1 1
			double t = (y+1.f)/2.f;
			Color middleColor = (1-t)*WhiteColor + t*SkyBlueColor;
			return middleColor;
		
		}
	

	}





}

Scene RandomSpheres() {
	Scene randomScene;
	const double radius = 0.2;
	Material* material_ground = new Lambertian(Color(0.8, 0.8, 0.0));
	Material* material_lambertian = new Lambertian(Color(0.7, 0.3, 0.3));
	Material* material_metal = new Metal(Color(0.8, 0.8, 0.8));
	Material* material_glass = new Glass(1.f, 1.5f);
	Sphere* glassSphere = new Sphere(Point3(0.f, 1.f, 0.f), 1.f, material_glass);
	Sphere* metalSphere = new Sphere(Point3(4.f, 1.f, 0.f), 1.f, material_metal);
	Sphere* labertianSphere = new Sphere(Point3(-4.f, 1.f, 0.f), 1.f, material_lambertian);
	randomScene.add(glassSphere);
	randomScene.add(metalSphere);
	randomScene.add(labertianSphere);


	for (int a = -11; a <= 11; a++) {
		for (int b = -11; b <= 11; b++) {
			Point3 center(a + rand01(), radius, b+ rand01());
			Vec3 disVec = center - metalSphere->center;
			if (disVec.length() > 0.9) {
				int MATERIAL_TYPE = random012(0.8, 0.15, 0.05);
				if (MATERIAL_TYPE == 0) {
					//add lambertian 
					Color randomColor1(rand01(), rand01(), rand01());
					Color randomColor2(rand01(), rand01(), rand01());
					Color randomColor = randomColor1 * randomColor2;
					Lambertian* lamberMaterial = new Lambertian(randomColor);
					Sphere* sphere_ab = new Sphere(center, radius, lamberMaterial);
					randomScene.add(sphere_ab);
				}

				if (MATERIAL_TYPE == 1) {
					// add metal
					double a = 0.5;
					double b = 1.f;
					Color randomColor(randab(a, b), randab(a, b), randab(a, b));
					Metal* metalMaterial = new Metal(randomColor);
					Sphere* sphere_ab = new Sphere(center, radius, metalMaterial);
					randomScene.add(sphere_ab);
				}

				if (MATERIAL_TYPE == 2) {
					//add glass				
					Glass* glassMaterial = new Glass(1.f, 1.5f);
					Sphere* sphere_ab = new Sphere(center, radius, glassMaterial);
					randomScene.add(sphere_ab);
				}
			}



		}	
	}


	return randomScene;


}





int main(){
	//Camera cam(150.f);
//Camera cam(90.f,Point3(278.f,278.f,-800.f),Point3(278.f,278.f,0.f),Vec3(0.f,1.f,0.f));
Camera cam;


// random scene render camera
//Camera cam(30.f,Point3(13.f,2.f,3.f),Point3(0.f,0.f,0.f),Vec3(0.f,1.f,0.f));
int Height = 540;
int Width = Height*cam.Ratio;//960 * 540 width * height  render image size  

// world of raytracing book
Scene world;
Material* material_ground = new Lambertian(Color(0.8, 0.8, 0.0));
Material* material_center = new Lambertian(Color(0.7, 0.3, 0.3));
Material* material_left = new Metal(Color(0.8, 0.8, 0.8));
Material* material_left_glass = new Glass(1.f,1.5f);
Material* material_right = new Metal(Color(0.8, 0.6, 0.2));
world.add(new Sphere(Point3( 0.0, -100.5, -1.0), 100.0, material_ground));
world.add(new Sphere(Point3( 0.0, 0.0, -1.0), 0.5, material_center));
world.add(new Sphere(Point3(-1.0, 0.0, -1.0), 0.5, material_left));
world.add(new Sphere(Point3( 1.0, 0.0, -1.0), 0.5, material_right));

Glass* glass = new Glass(1.f,1.5f);

Ray rayin(Point3(0.f,0.f,0.f),Vec3(1,-0.01,0));
Vec3 N(0,1,0);
Vec3 Rt = glass->refractDirectionFromAirToGlass(rayin,N);
bool isFromoutSide = glass->isFromOutside(rayin,N);

bool isInternalReflect = glass->isInternelReflect(rayin,N);
double costhetai = 0.01f;
double r = glass->reflectanceRatio(rayin, N);

Vec3 uintVecincircle = randvec_in_uinit_circle();
Ray testRay(Point3(0.f, 0.f, 0.f), Vec3(0, 0, -1));
AABB aabb(Point3(-1.f,-1.f,-1.f),Point3(1.f,1.f,1.f));

bool isHit = aabb.hit(testRay,0.01f,1000.f);
bool reuslt = aabb.isOverlap(-1.f,1.f,0.5f,3.f);
double a = 1;
double b = 2; 
aabb.swap(a,b);


	
//Scene scene = world;
Scene scene = RandomSpheres();

//for (int i = 0; i <= 100; i++) {
//	cout << random012(0.33, 0.33, 0.34) << endl;;
//}



//// Scene description
//ImageTexture earthmap("earthmap.jpg");
////Texture* imageTexture = new ImageTexture("earthmap.jpg");
//Texture* earthTexture = new ImageTexture("earthmap.jpg"); 
//
//Color result = earthTexture->getTexture(0,1,Point3());
//
//Lambertian lambert1(Color(0.8f,0.8f,0.0f));//ground color
//Lambertian lambert2(Color(0.7f,0.3f,0.3f));
//Lambertian lambertX(Color(1.0f,0.f,0.f));
//Lambertian lambertY(Color(0.f,0.f,1.f));
//Lambertian lambert3(earthTexture);
//Metal metal1(Color(0.8f,0.8f,0.8f));
//Metal metal2(Color(0.8f,0.6f,0.2f));
//DiffuseLight diffuseLight(new SolidColor(Color(1.f,1.f,1.f)));
//DiffuseLight diffuseLight1(earthTexture);
//
//Scene scene;
//Sphere sp1(Point3(10,5,-10),5.f,&metal1);
//Sphere sp2(Point3(-10,5,-10),5.f,&metal2);
//Sphere sp3(Point3(0,3,-8),2.f,&diffuseLight1);
//Sphere sp4(Point3(0.f,-100.5f,-100.f),100.f,&diffuseLight1);//ground 
//RectangleZ rec1(-200.f,-200.f,200.f,200.f,-200.f,&lambert3);
//RectangleX rec2(-200.f,-200.f,200.f,200.f,-200.f,&lambertX);
//RectangleY rec3(-200.f,-200.f,200.f,200.f,-100.f,&lambertY);
//
//scene.add(&sp1);
//scene.add(&sp2);
//scene.add(&sp3);
//scene.add(&sp4);
//scene.add(&rec1);
//scene.add(&rec2);
//scene.add(&rec3);
//
////scene = world;
//
////Cornell box
//
//
//Scene cornellbox;
//Lambertian red(Color(0.65f,0.05f,0.05f));
//Lambertian white(Color(0.73f,0.73f,0.73f));
//Lambertian green(Color(0.12f,0.45f,0.15f));
//Lambertian light(Color(10.f,10.f,10.f));
//RectangleX leftwall(0.f,0.f,555.f,555.f,0.f,&red);
//RectangleX rightwall(0.f,0.f,555.f,555.f,555.f,&green);
//RectangleY buttomwall(0.f,0.f,555.f,555.f,0.f,&white);
//RectangleY topwall(0.f,0.f,555.f,555.f,555.f,&white);
//RectangleY lightwall(213.f,227.f,332.f,343.f,550.f,&white);
//RectangleY backwall(0.f,0.f,555.f,555.f,550.f,&white);
//
//cornellbox.add(&leftwall);
//cornellbox.add(&rightwall);
//cornellbox.add(&buttomwall);
//cornellbox.add(&topwall);
//cornellbox.add(&backwall);
//cornellbox.add(&lightwall);
//
//scene = cornellbox;

/*
auto red = make_shared<lambertian>(color(.65, .05, .05));
auto white = make_shared<lambertian>(color(.73, .73, .73));
auto green = make_shared<lambertian>(color(.12, .45, .15));
auto light = make_shared<diffuse_light>(color(15, 15, 15));
objects.add(make_shared<yz_rect>(0, 555, 0, 555, 555, green));
objects.add(make_shared<yz_rect>(0, 555, 0, 555, 0, red));
objects.add(make_shared<xz_rect>(213, 343, 227, 332, 554, light));
objects.add(make_shared<xz_rect>(0, 555, 0, 555, 0, white));
objects.add(make_shared<xz_rect>(0, 555, 0, 555, 555, white));
objects.add(make_shared<xy_rect>(0, 555, 0, 555, 555, white));
*/





//renderer
int SUB_SAMPLING_NUM = 1;
int levels = 5;
cout<<"P3"<<endl;
cout<<Width;
cout<<" ";
cout<<Height; 
cout<<endl;
cout<<255<<endl;
for(int i = Height-1;i>=0;i-- ){
	std::cerr << "\rScanlines remaining: " << i << ' ' << std::flush;
	for(int j = 0;j<Width;j++){

		//i = 270;
		//j = 480;
		//j = 720;
		Color averageColor(0.f,0.f,0.f);
		

		for(int s = 0; s < SUB_SAMPLING_NUM; s++){
		
			double u = double(j+rand01())/(Width-1);
		    double v = double(i+rand01())/(Height-1);
		    Ray ray = cam.getRay(u,v);
			
		    Color tracingColor = raytracing(ray,scene,levels);
			averageColor = averageColor + tracingColor;
		
		}


		averageColor = averageColor/double(SUB_SAMPLING_NUM);
		write_color(cout,averageColor);

		
	}

}





return 0;
}

