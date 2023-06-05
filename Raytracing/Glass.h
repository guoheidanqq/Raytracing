#ifndef GLASS_H
#define GLASS_H
#include "Material.h"
class Glass : public Material {

public:

	Glass(double ni, double nt) {
		this->ni = ni;
		this->nt = nt;	
	}




	virtual bool scatter(const Ray& inRay, const HitInfo& hitInfo, 
		Color& attenuation, Ray& scatterRay) {

		Point3 hitPoint = hitInfo.hitPoint;
		double hitTime = hitInfo.hitTime;
		Vec3 N = hitInfo.N;
		N = normal(N);
		Vec3 outDir;
		bool flag = false;
		if (isFromOutside(inRay,N)) {
			outDir = refractDirectionFromAirToGlass(inRay,N);
			flag = true;
		}

		if (isFromInside(inRay,N)) {
			if (isInternelReflect(inRay, N)) {
				outDir = reflect(inRay,N);
				flag = true;
			}

			outDir = refractDirectionFromGlassToAir(inRay,N);
			flag = true;
		
		}
		attenuation = Color(1.f,1.f,1.f);
		scatterRay = Ray(hitPoint,outDir);
		return flag;
	}


	Vec3 refractDirectionFromAirToGlass(const Ray& inRay,const Vec3& outN) {
		double ni = this->ni;
		double nt = this->nt;
		Vec3 Ri = inRay.dir;
		Vec3 N = outN;
		N = normal(outN);
		Ri = normal(Ri);
		
		double costhetai = dot(-Ri, N);
		double sinthetai = sqrt(1-costhetai*costhetai);
		double sinthetat = ni / nt * sinthetai;
		double costhetat = sqrt(1 - sinthetat * sinthetat);

		Vec3 R_parrallel_t = costhetat * (-N);
		Vec3 R_perpendicular_i = Ri + costhetai * N;
		R_perpendicular_i = normal(R_perpendicular_i);
		Vec3 R_perpendicular_t = sinthetat * R_perpendicular_i;
		Vec3 Rt = R_parrallel_t + R_perpendicular_t;

		return Rt;
	}


	Vec3 refractDirectionFromGlassToAir(const Ray& inRay, const Vec3& outN) {
		double ni = this->nt;
		double nt = this->ni;
		Vec3 Ri = inRay.dir;
		Vec3 N = outN;
		N = normal(outN);
		Ri = normal(Ri);

		double costhetai = dot(-Ri, N);
		double sinthetai = sqrt(1 - costhetai * costhetai);
		double sinthetat = ni / nt * sinthetai;
		double costhetat = sqrt(1 - sinthetat * sinthetat);

		Vec3 R_parrallel_t = costhetat * (-N);
		Vec3 R_perpendicular_i = Ri + costhetai * N;
		R_perpendicular_i = normal(R_perpendicular_i);
		Vec3 R_perpendicular_t = sinthetat * R_perpendicular_i;
		Vec3 Rt = R_parrallel_t + R_perpendicular_t;

		return Rt;
	}


	bool isFromOutside(const Ray& inRay, const Vec3& outNormal) {
		Vec3 dir = inRay.dir;
		dir = normal(dir);
		Vec3 N = normal(outNormal);
		if (dot(dir, N) <= 0) {
			return true;
		}

		return false;
	
	}


	bool isFromInside(const Ray& inRay, const Vec3& outNormal) {
		Vec3 dir = inRay.dir;
		dir = normal(dir);
		Vec3 N = normal(outNormal);
		if (dot(dir, N) >= 0) {
			return true;
		}

		return false;

	}


	Vec3 reflect(const Ray& inray, const Vec3& N) {
	
		Vec3 N = normal(N);
		Vec3 V = normal(inray.dir);		
		Vec3 B = dot(V, -N) * N;
		Vec3 R = V + 2 * B;
		//Vec3 R = V - 2 * dot(V, N) * N;
		R = normal(R);
		return R;
	}

	bool isInternelReflect(const Ray& inRay, const Vec3& outNormal) {
		double ni = this->nt; // is in glass 
		double nt = this->ni;
		Vec3 Ri = inRay.dir;
		Vec3 N = outNormal;
		N = normal(outNormal);
		Ri = normal(Ri);

		double costhetai = dot(-Ri, N);
		double sinthetai = sqrt(1 - costhetai * costhetai);
		double sinthetat = ni / nt * sinthetai;
		double costhetat = sqrt(1 - sinthetat * sinthetat);

		if (sinthetat > 1.f) {
			return true;
		}

		return false;
	
	}


public:

	double ni;// enviroment object refractive index
	double nt;// glass  refractive index  ni<<nt




};





#endif

