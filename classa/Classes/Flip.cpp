#include "Flip.h"

bool Flip::operator()(Sprite & sprite, Setting & setting)
{
	sprite.setFlippedX(setting.flip);
	return true;
}
