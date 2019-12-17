#pragma once
#include "GeometryObject.h"
class Sphere :
	public GeometryObject
{
public:
	Sphere():radius(0),pos(0,0,0),GeometryObject(Material()){}
	Sphere(const float r,const Position3& p,Material& m):radius(r),pos(p),GeometryObject(m){}
	~Sphere();

	//�����蔻�� 
	bool CheckHit(const RayLine& ray, Position3& hitpos, Vector3& normal)const override;

	//�}�e���A����Ԃ��܂� 
	const Material& GetMaterial()const override;

	//�w����W����̍ŒZ����(���������璆�S�Ƃ̋���-���a�B���ʂ������琂���̒���) 
	float DistanceFromStart(const Position3& pos)override;

	Position3 position()const override;

	Color specDefCol(const Material& material, const Color& albed, const Vector3& lite, const Position3& hitPos, const Vector3& normal, const Position3& eye)override;
private:
	float radius;	// ���a
	Position3 pos;	// ���S���W
};
