#pragma once
#include "ActCtrl.h"

struct FallAct
{
	bool operator()(cocos2d::Sprite &sprite, ActModule &actModule);
};
