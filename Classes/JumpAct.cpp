#include "JumpAct.h"

bool JumpAct::operator()(cocos2d::Sprite & sprite, ActModule & actModule)
{
	static float v = 15.0f;
	static float v0 = 10.0f;

	//auto high = v * v - v0 * v0;
	//high = high / (-2 * 9.8);

	sprite.setPositionY(sprite.getPositionY() + v0);
	v0 -= 0.2;

	if (v <= 0)
	{
		v = 65;
	}

	return true;
}