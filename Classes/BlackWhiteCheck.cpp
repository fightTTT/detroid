#include "BlackWhiteCheck.h"
#include "Player.h"
bool BlackWhiteCheck::operator()(cocos2d::Sprite & sprite, ActModule & actModule)
{
	auto actType = ((Player&)sprite).ActType();

	for (auto &black : actModule.blackList)
	{
		for (auto &actData : actType)
		{
			if (actData == black)
			{
				return false;
			}
		}
	}

	return true;
}
