#pragma once
#include "Input.h"
struct TouchInput :
	public Input
{
	void Init(cocos2d::Node* node);
	void Update()override;
private:
	bool OnTouch(cocos2d::Touch *touch,cocos2d::Event *event);
	void KeepTouch(cocos2d::Touch *touch, cocos2d::Event *event);
	void OffTouch(cocos2d::Touch *touch, cocos2d::Event *event);
	cocos2d::Vec2 startPos;
};
