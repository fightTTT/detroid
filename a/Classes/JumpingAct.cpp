#include "JumpingAct.h"
#include "Player.h"

bool JumpingAct::operator()(cocos2d::Sprite & sprite, ActModule & actModule)
{
	sprite.setPositionY(sprite.getPositionY() + ((Player&)sprite).GetJumpSpeed());

	((Player&)sprite).SetJumpSpeed(((Player&)sprite).GetJumpSpeed() - 0.2);

	if (((Player&)sprite).GetJumpSpeed() <= 0)
	{
		((Player&)sprite).SetJumpSpeed(0);
		((Player&)sprite).SetActType(PL_ACTION::FALL);
	}

	return true;
}