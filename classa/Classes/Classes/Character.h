#pragma once
#include "cocos2d.h"
#include <vector>
#include <functional>
#include "Input.h"
#include <list>

USING_NS_CC;
struct Setting;
using modular = std::function<bool(Sprite& sprite, Setting& setting)>;

// 毎モジュールの設定
struct Setting
{
	std::list<modular> functionList;									// 処理を持っている配列
	std::list<modular> checkList;										// チェック処理を持っている配列
	INPUT_TYPE input = INPUT_TYPE::EMPTY;								// 入力のタイプ
	EventKeyboard::KeyCode key = EventKeyboard::KeyCode::KEY_NONE;		// キーの指定
	Vec2 velocity = Vec2(0.0f, 0.0f);									// 速度
	Vec2 collisionPoint[2] = { Vec2(0.0f,0.0f),Vec2(0.0f,0.0f) };		// 当たり判定
	std::string animation = "";											// アニメーションの指定
	bool flip;

	// 処理の追加
	void AddFunction(modular function)
	{
		functionList.emplace_back(function);
	}

	// チェックの追加
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
	void AddToUpdate(Setting& data);			// モジュールの追加
	std::vector<Setting> _update;				// 全モジュールを持っている配列
	std::string _currentAnimation;				// キャラの現在アニメーション
	float _jumpVelocity;						// キャラのジャンプの速度
	bool _isJump;
	bool _isFall;
	bool _isJumpReady;
};