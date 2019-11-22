#pragma once
#include "FallAct.h"
#include "input/KeyInput.h"

bool FallAct::operator()(Sprite & sprite, ActModule &actModule)
{
	sprite.setPositionY(sprite.getPositionY() - actModule.speed.y);
	return true;
}