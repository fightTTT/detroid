#pragma once
#include "ActCtrl.h"

struct JumpAct
{
	bool operator()(cocos2d::Sprite &sprite, ActModule &actModule);
};
