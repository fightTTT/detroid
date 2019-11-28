#pragma once
#include <map>
#include "cocos2d.h"
#include "SimpleAudioEngine.h"

enum class INPUT_TRG
{
	ON_MOM,
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
	virtual void Init(cocos2d::Node* node) {};
	virtual void Update() = 0;
	bool GetDir(DIR dir) { return moveDir[static_cast<int>(dir)]; };
	INPUT_TRG GetInput(DIR dir) { return inputTrg[static_cast<int>(dir)]; };
	INPUT_TRG GetInputType(cocos2d::EventKeyboard::KeyCode keyCode) { return inputType[static_cast<char>(keyCode)]; }
protected:
	bool moveDir[static_cast<int>(DIR::MAX)] = {false,false,false,false};
	INPUT_TRG inputTrg[static_cast<int>(DIR::MAX)] = { INPUT_TRG::OFF,INPUT_TRG::OFF,INPUT_TRG::OFF,INPUT_TRG::OFF };
	std::map<char, INPUT_TRG> inputType;
};
