#include "AnimationCheck.h"

bool AnimationCheck::operator()(Sprite & sprite, Setting & setting)
{
	sprite.setFlippedX(false);
	return true;
}
