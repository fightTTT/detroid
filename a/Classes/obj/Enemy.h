#pragma once
#include <tuple>
#include "cocos2d.h"

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

// �A�j���[�V�����f�[�^�@		 <plist,�摜��,�t���[���� >
using EnemyAnimData = std::tuple<std::string, std::string, int>;


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

	void RunAnim(ENEM_ACT animType);

	void SetDeth(const bool dethFlag);

private:
	ENEM_ACT _actNow;		// ���݂̃A�j���[�V����
	ENEM_ACT _actOld;		// 1�t���[���O�̃A�j���[�V����

	cocos2d::Size* _colSize;
	bool _dethFlag;

};

