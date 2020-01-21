#pragma once
#include "ActCtrl.h"

struct BlackWhiteCheck
{
	bool operator()(cocos2d::Sprite &sprite, ActModule &actModule);
};
