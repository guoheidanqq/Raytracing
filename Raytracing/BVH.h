#ifndef BVH_H
#define BVH_H
#include <algorithm>
#include "AABB.h"
#include "IHittable.h"
#include "Scene.h"

class BVHNode : public IHittable {

public:
	BVHNode() {
	}

	BVHNode( const Scene& nodeScene) {
		this->nodeScene = nodeScene;
		this->boundingBox = nodeScene.boundingBox;
		int NUM_OBJECTS = nodeScene.scene.size();

		Scene sortedScene = nodeScene;
		Scene leftScene;
		Scene rightScene;
		
		std::sort(sortedScene.scene.begin(), sortedScene.scene.end(), compareHittable_X);

		if (NUM_OBJECTS == 1) {
			this->left = nullptr;
			this->right = nullptr;
			this->boundingBox = this->nodeScene.boundingBox;
		
		}

		if (NUM_OBJECTS == 2) {
			leftScene.add(this->nodeScene.scene[0]);
			rightScene.add(this->nodeScene.scene[1]);
			this->left = new BVHNode(leftScene);
			this->right = new BVHNode(rightScene);
			this->boundingBox = nodeScene.boundingBox;


		}


		if (NUM_OBJECTS >2) {
			int midIndex = floor(NUM_OBJECTS  / 2);
			//[0 midIndex) [midInde num_objects)
			for (int i = 0; i < midIndex; i++) {
				leftScene.add(nodeScene.scene[i]);
			}

			for (int i = midIndex; i < NUM_OBJECTS; i++) {
				rightScene.add(nodeScene.scene[i]);
			}

			this->left = new BVHNode(leftScene);
			this->right = new BVHNode(rightScene);
			this->boundingBox = nodeScene.boundingBox;

		
		
		}

	}





	virtual bool hit(const Ray& ray, HitInfo& hitInfo, double tMin, double tMax)  override{
		bool isHitBoundgingBox = this->boundingBox.hit(ray,tMin,tMax);
		if (isHitBoundgingBox == true) {
			bool isHitLeft  = 	this->left->hit(ray,hitInfo,tMin,tMax);
			if (isHitLeft) {
				double tHitRight = hitInfo.hitTime;
				tMax = tHitRight;			
			}
			
			bool isHitRight =   this->right->hit(ray,hitInfo,tMin,tMax);

			bool hitResult = isHitLeft || isHitRight;
			return hitResult;			
		
		}

		if (isHitBoundgingBox = false) {
		
			return false;
		}


	
	}
	virtual bool hitBoundingBox(const Ray& ray, double tMin, double tMax) const override {
		bool isHit = this->boundingBox.hit(ray,tMin, tMax);
		return isHit;
	
	}
	virtual AABB getBoundingBox()const override{

		return this->boundingBox;
	}


public:
	BVHNode* left;
	BVHNode* right;
	Scene nodeScene;
	AABB  boundingBox;


};




class BVH:public IHittable {
public: 
	BVH() {
		this->root = nullptr;
	}
	BVH(BVHNode* root) {
		this->root = root;	
	}

	BVH(const Scene& scene) {
		if (scene.scene.size() == 0) {
			this->root = nullptr;
		}
		if (scene.scene.size() > 0)
		{
			this->root = new BVHNode(scene);
		}
		
		
	
	}

	void inOrderTravel(BVHNode* node) {
		if (node != nullptr) {
			inOrderTravel(node->left);
			std::cout << node->boundingBox.minPoint << std::endl;
			inOrderTravel(node->right);
		}
	
	}

	virtual bool hit(const Ray& ray, HitInfo& hitInfo, double tMin, double tMax) override {
		bool isHit = this->root->hit(ray,hitInfo,tMin,tMax);
		return isHit;
	}
	virtual bool hitBoundingBox(const Ray& ray, double tMin, double tMax) const {
		bool isHit = this->root->hitBoundingBox(ray, tMin,tMax);
		return isHit;
	}
	virtual AABB getBoundingBox()const override {

		return this->root->getBoundingBox();
	
	}




public:
	BVHNode* root;
};



#endif
