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
	// TODO: return �X�e�[�g�����g�������ɑ}�����܂�
}

float Plane::DistanceFromStart(const Position3 & pos)
{
	return 0.0f;
}
