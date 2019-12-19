#include "Fall.h"
#include "AnimationChanger.h"

#define CHARACTER ((Character&)sprite)

bool Fall::operator()(Sprite & sprite, Setting& setting)
{
	if (CHARACTER.IsFall())
	{
		AnimationChanger()(sprite, setting);
		sprite.setPositionY(sprite.getPositionY() + setting.velocity.y);
		return true;
	}
	return false;
}
