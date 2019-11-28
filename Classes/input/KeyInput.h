#pragma once
#include "Input.h"
#include "Player.h"

struct KeyInput :
	public Input
{
	void Init(cocos2d::Node* node)override;		
	void Update() override;

private:
	std::map<char, char> nowInputType;			// ���ݓ��͂��Ă�����L�[
	std::map<char, char> oldInputType;			// 1�t���[���O���͂��Ă����L�[
};
