#pragma once
#include "ActCtrl.h"

struct JumpingAct
{
	bool operator()(cocos2d::Sprite &sprite, ActModule &actModule);
};
