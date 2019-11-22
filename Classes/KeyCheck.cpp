#include "KeyCheck.h"
#include "input/KeyInput.h"

bool KeyCheck::operator()(cocos2d::Sprite & sprite, ActModule & actModule)
{
	if (((Player&)sprite).GetInputTrg(actModule.keyCode) == actModule.trgType)
	{
		return true;
	}
	else if (actModule.actionType == PL_ACTION::IDLE)
	{
		return true;
	}

	return false;
}
