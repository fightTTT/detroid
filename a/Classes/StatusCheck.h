#pragma once
#include "ActCtrl.h"

struct StatusCheck
{
	bool operator()(cocos2d::Sprite &sprite, ActModule &actModule);
};
