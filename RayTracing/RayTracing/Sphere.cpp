#include "Sphere.h"
#include <cmath>

Sphere::~Sphere()
{
}

bool Sphere::CheckHit(const RayLine & ray, Position3 & hitPos, Vector3 & normal) const
{
	Vector3 center = pos - ray.start;
	//
	//中心から視線への内積をとります＝＞ベクトル長
	float shadowLength = Dot(ray.vector, center);
	//Vector3 shadowRay = ray * syaeityou;
	//Vector3 shadowRay2 = eye + shadowRay;
	//// C-R ベクトルを作る
	//Vector3 suisen = sp.pos - shadowRay2;
	Vector3 shadowRay = ray.vector * shadowLength;
	Vector3 verticalLine = center - shadowRay;

	if (verticalLine.Magnitude() > radius)
	{
		return false;
	}

	// 三平方の定理を使って交点の座標を調べる
	hitPos = ray.start + ray.vector * ((shadowLength - sqrt(radius * radius - verticalLine.Magnitude()*verticalLine.Magnitude())));

	// 法線を求める
	normal = hitPos - pos;
	normal.Normalize();

	return true;
}

const Material & Sphere::GetMaterial() const
{
	return material;
}

float Sphere::DistanceFromStart(const Position3 & pos)
{
	auto lengs = (pos - this->pos).Magnitude();

	return (lengs - radius);
}
