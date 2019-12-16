#include "Sphere.h"
#include <cmath>

Sphere::~Sphere()
{
}

bool Sphere::CheckHit(const RayLine & ray, Position3 & hitPos, Vector3 & normal) const
{
	Vector3 center = pos - ray.start;
	//
	//���S���王���ւ̓��ς��Ƃ�܂������x�N�g����
	float shadowLength = Dot(ray.vector, center);
	//Vector3 shadowRay = ray * syaeityou;
	//Vector3 shadowRay2 = eye + shadowRay;
	//// C-R �x�N�g�������
	//Vector3 suisen = sp.pos - shadowRay2;
	Vector3 shadowRay = ray.vector * shadowLength;
	Vector3 verticalLine = center - shadowRay;

	if (verticalLine.Magnitude() > radius)
	{
		return false;
	}

	// �O�����̒藝���g���Č�_�̍��W�𒲂ׂ�
	hitPos = ray.start + ray.vector * ((shadowLength - sqrt(radius * radius - verticalLine.Magnitude()*verticalLine.Magnitude())));

	// �@�������߂�
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
