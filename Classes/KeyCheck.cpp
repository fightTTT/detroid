#include "KeyCheck.h"
#include "input/KeyInput.h"
#include "player.h"

bool KeyCheck::operator()(cocos2d::Sprite & sprite, ActModule & actModule)
{
	if (((Player&)sprite).GetInputTrg(actModule.keyCode) == actModule.trgType)
	{
		return true;
	}

	return false;
}
