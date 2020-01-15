#pragma once
#include "Obj.h"
class Shot :
	public Obj
{
public:
	static cocos2d::Sprite *createSprite(cocos2d::Vec2 pos, int speed);
	Shot();
	Shot(cocos2d::Vec2 pos,int speed);
	~Shot();
	void Init();
	void update(float delta);
private:
	cocos2d::Animate* anim;
};
