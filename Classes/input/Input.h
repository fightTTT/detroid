#pragma once
#include <map>
#include <array>
#include "cocos2d.h"
#include "SimpleAudioEngine.h"

enum class INPUT_TRG
{
	ON_MOMENT,
	ON,
	OFF_MOM,
	OFF,
	MAX
};

enum class DIR
{
	UP,
	DOWN,
	RIGHT,
	LEFT,
	MAX
};

struct Input
{
	virtual void Init(cocos2d::Node* node);
	virtual void Update() = 0;
	bool GetDir(DIR dir) { return moveDir[static_cast<int>(dir)]; };
	INPUT_TRG GetInput(DIR dir) { return _inputTrg[static_cast<int>(dir)]; };
	INPUT_TRG GetInputType(cocos2d::EventKeyboard::KeyCode keyCode) { return _inputType[static_cast<char>(keyCode)]; }
protected:
	bool moveDir[static_cast<int>(DIR::MAX)] = {false,false,false,false};
	std::array<INPUT_TRG, static_cast<int>(DIR::MAX)> _inputTrg;
	std::map<char, INPUT_TRG> _inputType;
	std::map<char, char> _nowInputType;			// 現在入力していいるキー
	std::map<char, char> _oldInputType;			// 1フレーム前入力していたキー
};
