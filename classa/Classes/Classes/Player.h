#pragma once

#include "cocos2d.h"
#include <vector>
#include "Character.h"

enum class P_ANIMATION {
	IDLE,
	STAND,
	CLING,
	HURT,
	DUCK,
	JUMP,
	RUN,
	RUN_SHOOT,
	SHOOT_UP,
	MAX
};

USING_NS_CC;

class Player : public Character{
public:
	static Character* createPlayer();		// �S�Ẵv���C���[�̏�񂪕Ԃ�
	Player();
	~Player();
private:
	CREATE_FUNC(Player);						// �p�����ꂽ�N���X�����������ăv���C���[���R���X�g���N�^����
	bool AnimationInit(void);					// �v���C���[�̃A�j���[�V�����f�[�^��o�^����
	void update(float delta);					// �X�V����
	void ChangeAnimation(const char*action);	// �ʂ̃A�j���[�V�����ɐ؂�ւ�����
};