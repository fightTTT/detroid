#pragma once
#include "cocos2d.h"
#include "ActCtrl.h"

enum class ENEM_ACT
{
	NONE,
	FREEZE,		// �������(�X��)
	MELT,		// �������(�n����)
	RIGHT_MOVE, // �E�ړ�
	LEFT_MOVE,	// ���ړ�
	FALL,		// �������钼�O
	FALLING,	// ������
	JUMP,		// �W�����v���钼�O
	JUMPING,	// �W�����v��
	ATTACK,		// �G���Ƃ̌ŗL�U��
	MAX
};

class Enemy:
	public cocos2d::Sprite
{
public:
	// �v���C���[�N���X�𐶐�����
	static cocos2d::Sprite *createSprite();
	Enemy();
	~Enemy();

	void Init();
	void update(float delta);

private:
	ActCtrl* _actCtrl;		// �A�N�V�������Ǘ�

};

