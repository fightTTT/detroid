#pragma once
#include <tuple>
#include <map>
#include <list>
#include <memory>
#include "Character.h"
#include "input/Input.h"


// �v���C���[�A�N�V�����̎��
enum class PL_ACTION
{
	IDLE,		// �������
	RUN,		// ����
	JUMP_FALL,		// �W�����v
	RUN_SHOT,	// ����Ȃ���e����
	MAX
};

class ActCtrl;
class EffectMng;

// �A�j���[�V�����f�[�^�@		 <plist,�摜��,�t���[���� >
using PlayerAnimData = std::tuple<std::string, std::string, int>;

using EffectData = std::unique_ptr<EffectMng>;

class Player :
	public Sprite
{
public:
	// �v���C���[�N���X�𐶐�����
	static Sprite *createSprite();
	Player();
	~Player();
	void Init();
	void update(float delta);

	// key�̃g���K�[�����擾����֐�
	INPUT_TRG GetInputTrg(cocos2d::EventKeyboard::KeyCode keyCode);
	const PL_ACTION GetActType();
	void SetActType(PL_ACTION actType);
	cocos2d::Layer& GetEffect();
private:
	std::map<std::string, EffectData> _effect;

	Input* _input;

	Layer* layer;

	std::string _animName[static_cast<int>(PL_ACTION::MAX)];
	PlayerAnimData _playerAnimData[static_cast<int>(PL_ACTION::MAX)];

	std::list<PL_ACTION> actFlag;

	ActCtrl* actCtrl;

	PL_ACTION _animNow;					// ���݂̃A�j���[�V����
	PL_ACTION _animOld;					// 1�t���[���O�̃A�j���[�V����
	// �A�j���[�V�����̎��s
	void RunAnim(PL_ACTION animType);
};
