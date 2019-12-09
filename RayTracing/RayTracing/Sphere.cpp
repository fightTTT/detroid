#include "Sphere.h"

Sphere::Sphere()
{
}

Sphere::~Sphere()
{
}

bool Sphere::CheckHit(const RayLine & ray, Position3 & hitpos, Vector3 & normal) const
{
	Vector3 center = pos - ray.start;
	//
	//中心から視線への内積をとります＝＞ベクトル長
	float shadowLength = Dot(ray, center);
	//Vector3 shadowRay = ray * syaeityou;
	//Vector3 shadowRay2 = eye + shadowRay;
	//// C-R ベクトルを作る
	//Vector3 suisen = sp.pos - shadowRay2;
	Vector3 shadowRay = ray * shadowLength;
	Vector3 verticalLine = center - shadowRay;

	return false;
}

const Material & Sphere::GetMaterial() const
{

}

float Sphere::DistanceFromStart(const Position3 & pos)
{
	return 0.0f;
}
