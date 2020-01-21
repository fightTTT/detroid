#include "JumpAct.h"
#include "Player.h"

bool JumpAct::operator()(cocos2d::Sprite & sprite, ActModule & actModule)
{
	((Player&)sprite).SetJumpSpeed(actModule.speed.y);
	((Player&)sprite).SetActType(PL_ACTION::JUMPING);

	return true;
}