#include "JumpAct.h"
#include "Player.h"

bool JumpAct::operator()(cocos2d::Sprite & sprite, ActModule & actModule)
{
	((Player&)sprite).SetJumpSpeed(actModule.speed.y);

	return true;
}