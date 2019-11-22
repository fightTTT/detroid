#pragma once
#include"Player.h"

struct StatusCheck
{
	bool operator()(cocos2d::Sprite &sprite, ActModule &actModule);
};
