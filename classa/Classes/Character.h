#pragma once
#include "cocos2d.h"
#include <vector>
#include <functional>
#include "Input.h"
#include <list>

USING_NS_CC;
struct Setting;
using modular = std::function<bool(Sprite& sprite, Setting& setting)>;

// �����W���[���̐ݒ�
struct Setting
{
	std::list<modular> functionList;									// �����������Ă���z��
	std::list<modular> checkList;										// �`�F�b�N�����������Ă���z��
	INPUT_TYPE input = INPUT_TYPE::EMPTY;								// ���͂̃^�C�v
	EventKeyboard::KeyCode key = EventKeyboard::KeyCode::KEY_NONE;		// �L�[�̎w��
	Vec2 velocity = Vec2(0.0f, 0.0f);									// ���x
	Vec2 collisionPoint[2] = { Vec2(0.0f,0.0f),Vec2(0.0f,0.0f) };		// �����蔻��
	std::string animation = "";											// �A�j���[�V�����̎w��
	bool flip;

	// �����̒ǉ�
	void AddFunction(modular function)
	{
		functionList.emplace_back(function);
	}

	// �`�F�b�N�̒ǉ�
	void AddCheck(modular check)
	{
		checkList.emplace_back(check);
	}
};

class Character : public Sprite
{
public:
	Character();
	~Character();
	float* JumpVelocity();
	float JumpVelocity(float velocity);
	bool IsJump(void);
	bool IsJump(bool flag);
	bool IsFall(void);
	bool IsFall(bool flag);
	void IsJumpReady(bool flag);
	bool IsJumpReady(void);
	std::string Animation();
	std::string Animation(std::string name);
private:
	void update(float delta);
protected:
	void AddToUpdate(Setting& data);			// ���W���[���̒ǉ�
	std::vector<Setting> _update;				// �S���W���[���������Ă���z��
	std::string _currentAnimation;				// �L�����̌��݃A�j���[�V����
	float _jumpVelocity;						// �L�����̃W�����v�̑��x
	bool _isJump;
	bool _isFall;
	bool _isJumpReady;
};