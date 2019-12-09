#include "Plane.h"

Plane::Plane()
{
}

Plane::~Plane()
{
}

bool Plane::CheckHit(const RayLine & ray, Position3 & hitPos, Vector3 & normal) const
{
	return false;
}

const Material & Plane::GetMaterial() const
{
	// TODO: return ステートメントをここに挿入します
}

float Plane::DistanceFromStart(const Position3 & pos)
{
	return 0.0f;
}
