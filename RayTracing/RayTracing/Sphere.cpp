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

Position3 Sphere::position() const
{
	return pos;
}

Color Sphere::specDefCol(const Material& material,const Color& albed, const Vector3 & light, const Position3 & hitPos, const Vector3 & normal, const Position3 & eye)
{
	auto nvec = normal;

	float dif = Dot(light, normal);
	if (dif <= 0)
	{
		
		nvec = -nvec;
	}

	auto reflect = light - nvec * dif * 2;

	reflect.Normalize();
	auto notEyeVec = eye - hitPos;
	notEyeVec.Normalize();

	float spacular = material.reflectance * 1 * abs(std::pow(Dot(reflect, notEyeVec), material.specularity));
	dif = material.reflectance * dif;
	dif = Clamp(dif);

	auto col = Color((dif * albed.x), (dif * albed.y), (dif * albed.z));

	col = { col.x + spacular + 0.1f,col.y + spacular + 0.1f, col.z + spacular + 0.1f, };

	col.x = Clamp(col.x);
	col.y = Clamp(col.y);
	col.z = Clamp(col.z);
	//auto b = Clamp(col.y);

	return col;
}
