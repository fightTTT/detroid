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

void AnimationMng::AddAnim(PlayerAnimData & animData, std::string animName)
{
	auto animCache = AnimationCache::getInstance();
	SpriteFrameCache* spriteCache = SpriteFrameCache::getInstance();

	// �X�v���C�g�t���[���̒ǉ�
	spriteCache->addSpriteFramesWithFile(std::get<0>(animData));
	std::string imageName = std::get<1>(animData) + std::to_string(1) + ".png";
	Sprite::createWithSpriteFrameName(imageName);

	Animation* animation = Animation::create();

	for (int frame = 1; frame <= std::get<2>(animData); frame++)
	{
		std::string str = std::get<1>(animData) + std::to_string(frame) + ".png";
		SpriteFrame* sprite = spriteCache->getSpriteFrameByName(str);
		animation->addSpriteFrame(sprite);
	}

	// �x���̐ݒ�
	animation->setDelayPerUnit(0.08f);

	animCache->addAnimation(animation, animName);
}