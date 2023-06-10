#ifndef SCENE_H
#define SCENE_H
#include "IHittable.h"
#include <vector>
#include "AABB.h"
using std::vector;
//#inclue <memory>

//using std::shared_ptr;
class Scene : public IHittable{

public: 
	Scene(){
		this->boundingBox = AABB(Point3(100000.f,10000.f,100000.f), Point3(-100000.f, -10000.f, -100000.f));
	
	}
	void add(IHittable* const object){
		scene.push_back(object);
		this->boundingBox = addBoundingBox(this->boundingBox, object->getBoundingBox());
		 
	}

	virtual AABB getBoundingBox()const override{
		return this->boundingBox;
	}
	void clear(){
		scene.clear();
		this->boundingBox = AABB(Point3(0.f, 0.f, 0.f), Point3(0.f, 0.f, 0.f));
	}

	virtual bool hit(const Ray& ray,HitInfo& hitInfo, double tMin =0.f, double tMax = 1000000.f) override{
		
		IHittable* hitObject = nullptr;		
		HitInfo currentHitInfo;
		double maxHitTime=1000000.f;
		bool isHit = false;
		bool returnValue = false;
		for(int i = 0; i < scene.size(); i++){
			hitObject = scene[i];
			isHit = hitObject->hit(ray,currentHitInfo,tMin,tMax);
			if (isHit) {
				maxHitTime = currentHitInfo.hitTime;
				tMax = maxHitTime;
				hitInfo = currentHitInfo;
				returnValue = true;
				
			}
				
		}	

		return returnValue;
	}

	virtual bool hitBoundingBox(const Ray& ray, double tMin, double tMax) const override {
	
		bool isHit = this->boundingBox.hit(ray,tMin,tMax);
		return isHit;
	}




public:
  vector<IHittable*> scene;
  AABB boundingBox;

};





#endif