#include "AnimationMng.h"
#include "cocos2d.h"

USING_NS_CC;

AnimationMng* AnimationMng::s_Instance = nullptr;

AnimationMng::AnimationMng()
{
}


AnimationMng::~AnimationMng()
{
}

void AnimationMng::AddAnim(PlayerAnimData & animData, std::string animName, PL_ACTION animType)
{
	int animTypeInt = static_cast<int>(animType);
	spriteCache = SpriteFrameCache::getInstance();
	auto animCache = AnimationCache::getInstance();

	spriteCache->addSpriteFramesWithFile(std::get<0>(animData));
	std::string a = std::get<1>(animData) + std::to_string(1) + ".png";
	Sprite::createWithSpriteFrameName(a);

	Animation* animation;

	animation = Animation::create();

	for (int s = 1; s <= std::get<2>(animData); s++)
	{
		std::string str = std::get<1>(animData) + std::to_string(s) + ".png";
		SpriteFrame* sprite = spriteCache->getSpriteFrameByName(str);
		animation->addSpriteFrame(sprite);
	}

	animation->setDelayPerUnit(0.08f);
	//animation->setRestoreOriginalFrame(std::get<3>(playerAnimData[animTypeInt]));
	playerAnim[animTypeInt] = RepeatForever::create(Animate::create(animation));

	animCache->addAnimation(animation, animName);
}