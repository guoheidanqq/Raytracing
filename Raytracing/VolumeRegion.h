#ifndef VOLUME_REGION_H
#define VOLUME_REGION_H
#include "IHittable.h"
#include <limits>
#include "Tools.h"
class  VolumeRegion : public IHittable {
	public:

		VolumeRegion(IHittable* const volumeRegion,Material* const material,double density=1.f) {

			this->density = density;
			this->volumeRegion = volumeRegion;
			this->material = material;
			this->boundingBox = volumeRegion->getBoundingBox();
		
		}
		virtual bool hit(const Ray& ray, HitInfo& hitInfo, double tMin, double tMax) override {
			const double infinity = std::numeric_limits<double>::infinity();
			bool isHit = volumeRegion->hit(ray,hitInfo,tMin,tMax);
			HitInfo hitInfo0; 
			HitInfo hitInfo1;
			double t = -infinity;
			double t0 = -infinity; 
			double t1 = -infinity;
			
			

			if (isHit == false) {
				return false;
			}

			if (isHit == true) {

				bool isHit0 = volumeRegion->hit(ray, hitInfo0, 0.f, +infinity);
				
				bool isHit1 = volumeRegion->hit(ray, hitInfo1, t0 + 0.01, +infinity);
				
				t0 = hitInfo0.hitTime;//bug
				t1 = hitInfo1.hitTime;

				//ray origion outside the boundary
				if (isHit0 == true && isHit1 == true) {

					Point3 p0 = hitInfo0.hitPoint;
					Point3 p1 = hitInfo1.hitPoint;
					Vec3 disVec = p1 - p0;
					double distance = disVec.length();
					//sample from exponential distribution  
					double u = rand01();
					if (u <= 0.00001) {
						u =  0.00001;
					}
					
					double step = -log(u) / (this->density);

					if (step >= distance) {
						return false;
					}

					if (step  < distance) {

						t = t0 + distance / ray.dir.length();

						if (t<tMin || t>tMax) {

							return false;
						}

						if (t >= tMin && t >= tMax) {
							Point3 point = ray.at(t);
							hitInfo.hitTime = t;
							hitInfo.hitPoint = point;
							hitInfo.hitMaterial = this->material;
							hitInfo.N = Vec3(0.f, 0.f, 1.f);
							hitInfo.ss = 0.f;
							hitInfo.tt = 0.f;
							return true;
						}




					}



				
				}

				//ray origion inside the boundary
				if (isHit0 == true && isHit1 == false) {
					Point3 p0 = hitInfo0.hitPoint;
					double t0 = hitInfo0.hitTime;
					double t = t0;					
					Vec3 disVec = (p0 - ray.origin);
					double distance = disVec.length();
					double u = rand01();
					if (u <= 0.00001) {
						u = 0.00001;
					}

					double step = -log(u) / (this->density);
					if (step >= distance) {
						return false;
					}

					if (step < distance) {
						double t = step / ray.dir.length();

						if (t< tMin || t> tMax) {
							return false;
						}
						if (t>=tMin && t<=tMax) {
							Point3 point = ray.at(t);
							hitInfo.hitTime = t;
							hitInfo.hitPoint = point;
							hitInfo.hitMaterial = this->material;
							hitInfo.N = Vec3(0.f, 0.f, 1.f);
							hitInfo.ss = 0.f;
							hitInfo.tt = 0.f;
							return true;
						
						}


					
					}
				
				}
				
			}

			return false;
		}
		virtual bool hitBoundingBox(const Ray& ray, double tMin, double tMax) const override {
			
			bool isHit = this->volumeRegion->hitBoundingBox(ray, tMin, tMax);
			return isHit;
		}
		virtual AABB getBoundingBox()const override {
			
			return this->boundingBox;
		
		}


	public:
		IHittable* volumeRegion;
		Material* material;			
		AABB boundingBox;
		double density;


};




#endif
