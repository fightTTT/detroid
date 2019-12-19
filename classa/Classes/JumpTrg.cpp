#include "JumpTrg.h"

#define CHARACTER ((Character&)sprite)

bool JumpTrg::operator()(Sprite & sprite, Setting & setting)
{
	if (!CHARACTER.IsJump() && CHARACTER.IsJumpReady())
	{
		CHARACTER.JumpVelocity(setting.velocity.y);
		CHARACTER.IsJump(true);
		CHARACTER.IsFall(false);
		CHARACTER.IsJumpReady(false);
	}
	return true;
}
