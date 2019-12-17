#include "GeometryObject.h"

GeometryObject::GeometryObject()
{
}

GeometryObject::~GeometryObject()
{
}

Position3 GeometryObject::position() const
{
	return Position3();
}

Color GeometryObject::specDefCol(const Material& material, const Color& albed, const Vector3 & lite, const Position3 & spPos, const Vector3 & normal, const Position3 & eye)
{
	return Color();
}
