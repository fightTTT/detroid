#pragma once
#include "cocos2d.h"
#include <vector>

USING_NS_CC;

// �Փ˂̃^�C�v
enum class C_TYPE
{
	MOVE,		// ���E�Փ�
	UPDOWN		// �㉺�Փ�
};

class CPoint
{
public:
	//�@�Փ˗p�̓_�̏�����
	CPoint();
	CPoint(int index, Vec2 pos);
	CPoint(int index, Vec2 pos, Size size, C_TYPE type);
	~CPoint();

	void SetOffset(Size size);				// XY���W�����炷
	void SetOffsetX(float size);			// X���W�����炷
	void SetOffsetX(float size, int index);	// �w�肳�ꂽX���W�����炷
	void SetOffsetY(float size);			// Y���W�����炷
	void SetOffsetY(float size, int index);	// �w�肳�ꂽY���W�����炷
	const Vec2 GetPoint(int index);			// �w�肳�ꂽ�_�̍��W���Ƃ�
	const int GetPointSize(void);			// �R���e�i�̗v�f�������
	const std::vector<Vec2> GetGroup(void);	// �x�N�g���z������
private:
	std::vector<Vec2> _point;
};