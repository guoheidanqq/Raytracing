#ifndef SCENE_H
#define SCENE_H
#include "IHittable.h"
#include <vector>
using std::vector;
//#inclue <memory>

//using std::shared_ptr;
class Scene : public IHittable{

public: 
	Scene(){
	
	}
	void add(IHittable* const object){
		scene.push_back(object);	
	}

	void clear(){
		scene.clear();
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


public:
  vector<IHittable*> scene;

};





#endif