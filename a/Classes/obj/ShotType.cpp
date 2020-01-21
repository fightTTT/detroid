#include "ShotType.h"
#include "Shot.h"

USING_NS_CC;

cocos2d::Sprite * ShotType::createSprite(cocos2d::Vec2 & speed)
{
	ShotType *shot = new ShotType(speed);
	if (shot&&shot->init())
	{
		shot->autorelease();
		return shot;
	}

	delete shot;
	shot = nullptr;
	return nullptr;
}

ShotType::ShotType()
{
}

ShotType::ShotType(cocos2d::Vec2 & speed)
{
	Init(speed);
}


ShotType::~ShotType()
{

}

void ShotType::Init(cocos2d::Vec2 & speed)
{
	auto layer = Director::getInstance()->getRunningScene()->getChildByName("FollowerLayer")->getChildByName("PlayerLayer");

	layer->addChild(this);

	auto player = layer->getChildByName("player");
	setPosition(player->getPosition());
	scheduleUpdate();
	_speed = speed;

	Animate* anim;
	anim = Animate::create(AnimationCache::getInstance()->getAnimation("shot"));
	runAction(RepeatForever::create(anim));
}

void ShotType::update(float dt)
{
	setPosition(getPosition() + _speed);
}
