#include "Character.h"
#include "KeyCheck.h"
#include "AnimationChanger.h"

Character::Character()
{
	_isFall = true;
	_isJump = false;
	_isJumpReady = true;
	_jumpVelocity = 0.0f;
	_currentAnimation = "";
	this->scheduleUpdate();
}

Character::~Character()
{

}

float* Character::JumpVelocity()
{
	return &_jumpVelocity;
}

float Character::JumpVelocity(float velocity)
{
	return _jumpVelocity = velocity;
}

bool Character::IsJump(void)
{
	return _isJump;
}

bool Character::IsJump(bool flag)
{
	return _isJump = flag;
}

bool Character::IsFall(void)
{
	return _isFall;
}

bool Character::IsFall(bool flag)
{
	return _isFall = flag;
}

void Character::IsJumpReady(bool flag)
{
	_isJumpReady = flag;
}

bool Character::IsJumpReady(void)
{
	return _isJumpReady;
}

std::string Character::Animation()
{
	return _currentAnimation;
}

std::string Character::Animation(std::string name)
{
	return _currentAnimation = name;
}

void Character::update(float delta)
{
}

void Character::AddToUpdate(Setting& data)
{
	// キーが登録されたら、キーチェック関数オブジェクトを入れる
	if (data.key != EventKeyboard::KeyCode::KEY_NONE)
	{
		data.AddCheck(KeyCheck());
	}

	_update.emplace_back(data);
}
