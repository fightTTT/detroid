#include "TouchInput.h"
#include "ActCtrl.h"

void TouchInput::Init(cocos2d::Node * node)
{
	ActCtrl* act;
	auto touch = cocos2d::EventListenerTouchOneByOne::create();
	touch->onTouchBegan = CC_CALLBACK_2(TouchInput::OnTouch, this);
	touch->onTouchMoved = CC_CALLBACK_2(TouchInput::KeepTouch, this);
	touch->onTouchEnded = CC_CALLBACK_2(TouchInput::OffTouch, this);
	node->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touch, node);

	//inputType.insert(std::make_pair(act->GetActKeyCode("move")), INPUT_TRG::OFF));
}

void TouchInput::Update()
{
	
}

bool TouchInput::OnTouch(cocos2d::Touch * touch, cocos2d::Event * event)
{
	startPos = touch->getStartLocation();

	return true;
}

void TouchInput::KeepTouch(cocos2d::Touch * touch, cocos2d::Event * event)
{
	auto currentPos = touch->getLocation();
	int reservoir = 17;

	if (startPos.y > currentPos.y + reservoir)
	{
		moveDir[static_cast<int>(DIR::DOWN)] = true;
		moveDir[static_cast<int>(DIR::UP)] = false;
	}

	if (startPos.y < currentPos.y - reservoir)
	{
		moveDir[static_cast<int>(DIR::UP)] = true;
		moveDir[static_cast<int>(DIR::DOWN)] = false;
	}

	if (startPos.x < currentPos.x - reservoir)
	{
		moveDir[static_cast<int>(DIR::RIGHT)] = true;
		moveDir[static_cast<int>(DIR::LEFT)] = false;
	}

	if (startPos.x > currentPos.x + reservoir)
	{
		moveDir[static_cast<int>(DIR::LEFT)] = true;
		moveDir[static_cast<int>(DIR::RIGHT)] = false;
	}
}

void TouchInput::OffTouch(cocos2d::Touch * touch, cocos2d::Event * event)
{
	for (auto &dir : moveDir)
	{
		if (dir)
		{
			dir = false;
		}
	}
}
