#include "KeyCheck.h"
#include "input/KeyInput.h"
#include "player.h"

bool KeyCheck::operator()(cocos2d::Sprite & sprite, ActModule & actModule)
{
	/*if (actModule.actionType == PL_ACTION::IDLE
	 || actModule.actionType == PL_ACTION::FALL
	 || actModule.actionType == PL_ACTION::JUMPING)
	{
		return true;
	}*/

	if (((Player&)sprite).GetInputTrg(actModule.keyCode) == actModule.trgType)
	{
		return true;
	}

	return false;
}
