#include "AnimationChanger.h"

bool AnimationChanger::operator()(Sprite & sprite, Setting & setting)
{
	if (setting.animation == "")
	{
		//log("Animation name is missing or is not set");
		return false;
	}

	if (((Character&)sprite).Animation() != setting.animation)
	{
		sprite.stopAllActions();

		if (AnimationCache::getInstance()->getAnimation(setting.animation) == nullptr)
		{
			//log("Animation %s is missing or not exisit", setting.animation);
			return false;
		}

		sprite.runAction(RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation(setting.animation))));
		((Character&)sprite).Animation(setting.animation);
		return true;
	}
	return false;
}
