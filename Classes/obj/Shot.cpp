#include "Shot.h"
#include "ActCtrl.h"
#include "Console/_DebugConOut.h"

USING_NS_CC;

cocos2d::Sprite * Shot::createSprite(cocos2d::Vec2 pos, int speed)
{
	Shot *shot = new Shot(pos, speed);
	if (shot&&shot->init())
	{
		shot->autorelease();
		return shot;
	}

	delete shot;
	shot = nullptr;
	return nullptr;
}

Shot::Shot()
{
}

Shot::Shot(cocos2d::Vec2 pos, int speed)
{
	//setPosition(pos);
	TRACE("%d\n", getPositionX());
	_speed = speed;
	Init();
	TRACE("%d\n", getPositionX());
}


Shot::~Shot()
{
}

void Shot::Init()
{
	anim = Animate::create(AnimationCache::getInstance()->getAnimation("shot"));
	runAction(RepeatForever::create(anim));
	setGlobalZOrder(99);

	this->scheduleUpdate();
}

void Shot::update(float delta)
{
	/*if ( + _size.y / 2 < 0)
	{
		_death = true;
	}*/

	TRACE("%d\n", getPositionX());

	setPositionX(getPositionX() + _speed);
}
