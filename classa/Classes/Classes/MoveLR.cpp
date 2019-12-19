#include "MoveLR.h"
#include "AnimationChanger.h"

#define CHARACTER ((Character&)sprite)

bool MoveLR::operator()(Sprite & sprite, Setting & setting)
{
	if (!CHARACTER.IsJump())
	{
		AnimationChanger()(sprite, setting);
	}

	sprite.setPosition(sprite.getPosition() + setting.velocity);
	return true;
	return false;
}