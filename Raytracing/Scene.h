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
	void add(IHittable* object){
		scene.push_back(object);	
	}

	void clear(){
	scene.clear();
	}

	virtual bool hit(Ray& ray,HitInfo& hitInfo, double tMin =0.f, double tMax = 1000000.f) override{
		
		IHittable* hitObject = nullptr;
		vector<HitInfo> hitArray;

		bool isHit = false;
		for(int i = 0; i < scene.size(); i++){
			hitObject = scene[i];
			isHit = hitObject->hit(ray,hitInfo,tMin,tMax);
			if(isHit){
				hitArray.push_back(hitInfo);

			}
				
		}
		if(hitArray.size()==0){			    
				return false;
			}
		if(hitArray.size()==1){
			hitInfo = hitArray[0];
			return true;
		}
		else {
			//find smalles time 
			double time = 1000000.f;
			int index = 0;
			for(int j = 0; j< hitArray.size();j++){
				if(hitArray[j].hitTime < time){
				index = j;
				time = hitArray[j].hitTime;
				}

			}

			hitInfo = hitArray[index];

			return true;
		
		}

	}






public:
  vector<IHittable*> scene;

};





#endif