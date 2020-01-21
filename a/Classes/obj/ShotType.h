#pragma once
#include <memory>
#include "cocos2d.h"

class ShotType :
	public cocos2d::Sprite
{
public:
	static cocos2d::Sprite *createSprite(cocos2d::Vec2& speed);
	ShotType();
	ShotType(cocos2d::Vec2 & speed);
	~ShotType();
	void Init(cocos2d::Vec2 & speed);
	void update(float dt);
private:
	cocos2d::Vec2 _speed;
};
