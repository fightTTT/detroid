#pragma once
#include "GeometryObject.h"
class Plane :
	public GeometryObject
{
public:
	Plane();
	Vector3 normal;	// �@���x�N�g��
	float	offset; // ���_����̃I�t�Z�b�g
	Plane(Vector3& n,float o,const Material& m):normal(n),offset(o),GeometryObject(m){}
	~Plane();

	///�����蔻�� 
	///@param ray ��������n�܂钼�� 
	///@param hitpos[out] �Փ˓_ 
	///@param norm[out] �Փ˓_�̖@���x�N�g�� 
	///@retval true �������� 
	///@retval false �O�ꂽ 
	bool CheckHit(const RayLine& ray, Position3& hitPos, Vector3& normal)const override;

	//�}�e���A����Ԃ��܂� 
	const Material& GetMaterial()const override;

	float DistanceFromStart(const Position3& pos)override;
};

