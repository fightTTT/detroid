#pragma once
#include <tuple>
#include <array>
#include "cocos2d.h"
#include "input/Input.h"

// �v���C���[�A�j���[�V�����̎��
enum class PL_ACTION
{
	IDLE,		// �������
	RIGHT_MOVE, // �E�ړ�
	LEFT_MOVE,	// ���ړ�
	JUMP,		// �W�����v���钼�O
	JUMPING,	// �W�����v��
	FALL,		// ����
	RUN_SHOT,	// ����Ȃ���e����
	MAX
};

class ActCtrl;

// �A�j���[�V�����f�[�^�@		 <plist,�摜��,�t���[���� >
using PlayerAnimData = std::tuple<std::string, std::string, int>;

class Player :
	public cocos2d::Sprite
{
public:
	// �v���C���[�N���X�𐶐�����
	static cocos2d::Sprite *createSprite();
	Player();
	~Player();
	void Init();
	void update(float delta);
	          
	// key�̃g���K�[�����擾����֐�
	INPUT_TRG GetInputTrg(cocos2d::EventKeyboard::KeyCode keyCode);

	// ���ݎ��s���̃A�N�V�����^�C�v�擾
	const PL_ACTION GetActType();
	void SetActType(PL_ACTION actType);
	const float GetJumpSpeed();
	void SetJumpSpeed(float jumpSpeed);

private:

	Input* _input;

	ActCtrl* _actCtrl;		// �A�N�V�������Ǘ�

	float _JumpSpeed;		// �W�����v�̃X�s�[�h

	// �A�j���[�V�����̎��s
	void RunAnim(PL_ACTION animType);
	std::array<std::string, static_cast<int>(PL_ACTION::MAX)> _animName; // �A�j���[�V������

	PL_ACTION _actNow;					// ���݂̃A�j���[�V����
	PL_ACTION _actOld;					// 1�t���[���O�̃A�j���[�V����
	
};
