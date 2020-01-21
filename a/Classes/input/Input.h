#pragma once
#include <map>
#include <array>
#include "cocos2d.h"
#include "SimpleAudioEngine.h"

#define KEYCODE(key)		EventKeyboard::KeyCode(key)
#define CHAR(keyCode)		static_cast<char>(keyCode)

enum class INPUT_TRG
{
	ON_MOMENT,		// �L�[���������u��
	ON,				// �L�[������������	
	OFF_MOMENT,		// �L�[�𗣂����u��
	OFF,			// �L�[�𗣂��Ă���
	MAX
};

struct Input
{
	virtual void Init(cocos2d::Node* node, cocos2d::Layer* layer) = 0;
	void Update();

	// �����Ŏw�肵���L�[�̓��͏�Ԃ�Ԃ�
	INPUT_TRG GetInputType(const cocos2d::EventKeyboard::KeyCode& keyCode) { return _inputType[static_cast<char>(keyCode)]; }
protected:
	//std::array<INPUT_TRG, static_cast<int>(DIR::MAX)> _inputTrg;
	std::map<char, INPUT_TRG> _inputType;		// ���ׂẴL�[�̓��͏��
	std::map<char, char> _nowInputType;			// ���ݓ��͂��Ă���L�[
	std::map<char, char> _oldInputType;			// 1�t���[���O���͂��Ă����L�[
};
