#pragma once
#include "Input.h"
#include "Player.h"

struct KeyInput :
	public Input
{
	void Init(cocos2d::Node* node)override;
	void Update() override;

private:
	std::map<char, char> nowInputType;
	std::map<char, char> oldInputType;
};
