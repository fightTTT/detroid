#include "MoveLR.h"

bool MoveLR::operator()(cocos2d::Sprite & sprite, ActModule & actModule)
{
	sprite.setPositionX(sprite.getPositionX() + actModule.speed.x);

	return true;
}
