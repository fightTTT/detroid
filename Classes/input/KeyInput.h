#pragma once
#include "Input.h"


struct KeyInput :
	public Input
{
	void Init(cocos2d::Node* node, cocos2d::Layer* layer)override;
};
