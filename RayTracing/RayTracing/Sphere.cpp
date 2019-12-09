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
	//���S���王���ւ̓��ς��Ƃ�܂������x�N�g����
	float shadowLength = Dot(ray, center);
	//Vector3 shadowRay = ray * syaeityou;
	//Vector3 shadowRay2 = eye + shadowRay;
	//// C-R �x�N�g�������
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
