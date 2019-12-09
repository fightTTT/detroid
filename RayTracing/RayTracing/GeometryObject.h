#pragma once
#include"Geometry.h"

//�\�ʖ͗l��`
enum class Pattern {
	none,		//�͗l�Ȃ� 
	hstripe,	//�Ȗ͗l(��) 
	vstripe,	//�Ȗ͗l(�c) 
	checkered,	//�s���͗l(�`�F�b�J�[�t���b�O) 
	textured	//�e�N�X�`���}�b�s���O 
};

//�\�ʍގ�  
struct Material {
	Color diffuse;		//�g�U���ː���(cos�ŕ\��������Ԃ��F) 
	Color specular;		//���ʔ��ː���(�X�y�L�����Ō��肳���\�ʍގ����Ԃ��F) 
	Color ambient;		//����(�Q�^) 
	float specularity;	//�X�y�L�����̋���(�搔) 
	float reflectance;	//���˗� 
	Pattern pattern;	//�͗l��� 

	Material() :
		diffuse(1, 1, 1), specular(0, 0, 0), ambient(0, 0, 0), specularity(0), reflectance(0) {}

	Material(const Color& diff,
			 const Color& spec,
			 const Color& amb,
			 float inSpecularity,
			 float inReflectance,
			 Pattern p = Pattern::none) : diffuse(diff), specular(spec), ambient(amb),
			 specularity(inSpecularity), reflectance(inReflectance),pattern(p) {}
};



class GeometryObject
{
public:
	GeometryObject();
	Material material;
	GeometryObject(Material m) :material(m) {};
	~GeometryObject();

	///�����蔻�� 
	///@param ray ��������n�܂钼�� 
	///@param hitpos[out] �Փ˓_ 
	///@param normal[out] �Փ˓_�̖@���x�N�g�� 
	///@retval true �������� 
	///@retval false �O�ꂽ
	virtual bool CheckHit(const RayLine& ray, Position3& hitPos, Vector3& normal)const = 0;

	///�}�e���A����Ԃ��܂� 
	///@return �}�e���A���I�u�W�F�N�g
	virtual const Material& GetMaterial()const = 0;

	///�w����W����̍ŒZ����(���������璆�S�Ƃ̋���-���a�B���ʂ������琂���̒���) 
	///@param p �����𑪂肽���_(���W) 
	virtual	float DistanceFromStart(const Position3& pos) = 0;
};

