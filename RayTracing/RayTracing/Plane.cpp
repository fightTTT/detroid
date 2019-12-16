#include "Plane.h"

Plane::Plane()
{
}

Plane::~Plane()
{
}

bool Plane::CheckHit(const RayLine & ray, Position3 & hitPos, Vector3 & norm) const
{
	Vector3 hoge = ray.vector;
	float horizon = Dot(-hoge, normal);

	if (horizon <= 0)
	{
		return false;
	}

	auto hitPosLen = (Dot(ray.start, normal) - offset) / horizon;
	hitPos = ray.vector * hitPosLen + ray.start;

	if (Dot(-hoge,normal) > 0.0f)
	{
		return true;
	}

	return false;
}

const Material & Plane::GetMaterial() const
{
	return material;
}

float Plane::DistanceFromStart(const Position3 & pos)
{
	return (pos.y - offset);
}
