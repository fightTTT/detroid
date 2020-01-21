#pragma once
#include "cocos2d.h"

USING_NS_CC;


class Character :
	public cocos2d::Sprite
{
public:
	Character();
	virtual ~Character();
	virtual void Init(cocos2d::Node *node) = 0;
	virtual void Update(cocos2d::Node *node) = 0;

protected:
	cocos2d::Sprite *sprite;

};

