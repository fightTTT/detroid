#pragma once
#include "GeometryObject.h"
class Sphere :
	public GeometryObject
{
public:
	float radius;	// ���a
	Position3 pos;	// ���S���W
	Sphere():radius(0),pos(0,0,0),GeometryObject(Material()){}
	Sphere(float r,Position3& p,Material m):radius(r),pos(p),GeometryObject(m){}
	~Sphere();

	//�����蔻�� 
	bool CheckHit(const RayLine& ray, Position3& hitpos, Vector3& normal)const;

	//�}�e���A����Ԃ��܂� 
	const Material& GetMaterial()const;

	//�w����W����̍ŒZ����(���������璆�S�Ƃ̋���-���a�B���ʂ������琂���̒���) 
	float DistanceFromStart(const Position3& pos);
};

