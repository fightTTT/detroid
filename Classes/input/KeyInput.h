#pragma once
#include "Input.h"
#include "Player.h"

struct KeyInput :
	public Input
{
	void Init(cocos2d::Node* node)override;		
	void Update() override;

private:
	std::map<char, char> nowInputType;			// 現在入力していいるキー
	std::map<char, char> oldInputType;			// 1フレーム前入力していたキー
};
