#pragma once
#include "Input.h"
struct TouchInput :
	public Input
{
	void Update(cocos2d::Sprite* face);
};