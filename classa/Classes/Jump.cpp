#include "Jump.h"
#include "AnimationChanger.h"

#define CHARACTER ((Character&)sprite)

bool Jump::operator()(Sprite & sprite, Setting & setting)
{
	if (CHARACTER.IsJump() && !CHARACTER.IsFall())
	{
		AnimationChanger()(sprite, setting);
		auto currentVelocity = CHARACTER.JumpVelocity();
		auto movementY = sprite.getPositionY();

		*currentVelocity -= 10.0f * 0.2f;
		movementY += *currentVelocity * 0.2f;

		sprite.setPositionY(movementY);
		if (*currentVelocity <= 0.0f)
		{
			CHARACTER.IsJump(false);
			CHARACTER.IsFall(true);
		}
		return true;
	}
	return false;
}