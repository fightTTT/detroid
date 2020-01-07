#pragma once
#include "FallAct.h"
#include "Player.h"
//#include "input/KeyInput.h"

bool FallAct::operator()(cocos2d::Sprite & sprite, ActModule &actModule)
{
	sprite.setPositionY(sprite.getPositionY() - actModule.speed.y);
	((Player&)sprite).SetJumpSpeed(0);

	return true;
}