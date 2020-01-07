#pragma once
#include <map>
#include <array>
#include "cocos2d.h"
#include "SimpleAudioEngine.h"

#define KEYCODE(key)		EventKeyboard::KeyCode(key)
#define CHAR(keyCode)		static_cast<char>(keyCode)

enum class INPUT_TRG
{
	ON_MOMENT,		// キーを押した瞬間
	ON,				// キーを押し続ける	
	OFF_MOMENT,		// キーを離した瞬間
	OFF,			// キーを離している
	MAX
};

struct Input
{
	virtual void Init(cocos2d::Node* node, cocos2d::Layer* layer) = 0;
	void Update();

	// 引数で指定したキーの入力状態を返す
	INPUT_TRG GetInputType(const cocos2d::EventKeyboard::KeyCode& keyCode) { return _inputType[static_cast<char>(keyCode)]; }
protected:
	//std::array<INPUT_TRG, static_cast<int>(DIR::MAX)> _inputTrg;
	std::map<char, INPUT_TRG> _inputType;		// すべてのキーの入力状態
	std::map<char, char> _nowInputType;			// 現在入力しているキー
	std::map<char, char> _oldInputType;			// 1フレーム前入力していたキー
};
