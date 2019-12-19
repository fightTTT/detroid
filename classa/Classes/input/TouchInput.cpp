#include "TouchInput.h"
#include "ActCtrl.h"
#include "ui/CocosGUI.h"
#include "Player.h"

//#define KEYCODE(key)		EventKeyboard::KeyCode(key)
//#define CHAR(keyCode)		static_cast<char>(keyCode)

USING_NS_CC;

void TouchInput::Init(cocos2d::Node * node,cocos2d::Layer* layer)
{
	ActCtrl* act;
	auto touch = cocos2d::EventListenerTouchOneByOne::create();
	touch->onTouchBegan = CC_CALLBACK_2(TouchInput::OnTouch, this);
	touch->onTouchMoved = CC_CALLBACK_2(TouchInput::KeepTouch, this);
	touch->onTouchEnded = CC_CALLBACK_2(TouchInput::OffTouch, this);
	node->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touch, node);
	_inputType[CHAR(EventKeyboard::KeyCode::KEY_DOWN_ARROW)] = INPUT_TRG::OFF;
	_inputType[CHAR(EventKeyboard::KeyCode::KEY_UP_ARROW)] = INPUT_TRG::OFF;
	_inputType[CHAR(EventKeyboard::KeyCode::KEY_RIGHT_ARROW)] = INPUT_TRG::OFF;
	_inputType[CHAR(EventKeyboard::KeyCode::KEY_LEFT_ARROW)] = INPUT_TRG::OFF;
	_inputType[CHAR(EventKeyboard::KeyCode::KEY_Z)] = INPUT_TRG::OFF;

	// ‰EˆÚ“®
	{
		ui::Button * button = ui::Button::create();
		button->setTouchEnabled(true);
		button->loadTextures("RightUp.png", "RightDown.png", "");
		//button->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
		button->setPosition({ 200,50 });
		button->setGlobalZOrder(20);
		button->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type)
		{
			if (type == ui::Widget::TouchEventType::BEGAN)
			{
				if (!_nowInputType.insert(std::make_pair(CHAR(EventKeyboard::KeyCode::KEY_RIGHT_ARROW), 1)).second)
				{
					_nowInputType[CHAR(EventKeyboard::KeyCode::KEY_RIGHT_ARROW)] = 1;
				}
				_inputType[CHAR(EventKeyboard::KeyCode::KEY_RIGHT_ARROW)] = INPUT_TRG::ON_MOMENT;
			}
			if (type == ui::Widget::TouchEventType::ENDED || type == ui::Widget::TouchEventType::CANCELED)
			{
				if (!_nowInputType.insert(std::make_pair(CHAR(EventKeyboard::KeyCode::KEY_RIGHT_ARROW), 0)).second)
				{
					_nowInputType[CHAR(EventKeyboard::KeyCode::KEY_RIGHT_ARROW)] = 0;
				}
				_inputType[CHAR(EventKeyboard::KeyCode::KEY_RIGHT_ARROW)] = INPUT_TRG::OFF_MOMENT;
			}
		});
		layer->addChild(button);
	}

	// ¶ˆÚ“®
	{
		ui::Button * button = ui::Button::create();
		button->setTouchEnabled(true);
		button->loadTextures("LeftUp.png", "LeftDown.png", "");
		button->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
		button->setGlobalZOrder(20);
		button->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type)
		{
			if (type == ui::Widget::TouchEventType::BEGAN)
			{
				if (!_nowInputType.insert(std::make_pair(CHAR(EventKeyboard::KeyCode::KEY_LEFT_ARROW), 1)).second)
				{
					_nowInputType[CHAR(EventKeyboard::KeyCode::KEY_LEFT_ARROW)] = 1;
				}
				_inputType[CHAR(EventKeyboard::KeyCode::KEY_LEFT_ARROW)] = INPUT_TRG::ON_MOMENT;
			}
			if (type == ui::Widget::TouchEventType::ENDED || type ==  ui::Widget::TouchEventType::CANCELED)
			{
				if (!_nowInputType.insert(std::make_pair(CHAR(EventKeyboard::KeyCode::KEY_LEFT_ARROW), 0)).second)
				{
					_nowInputType[CHAR(EventKeyboard::KeyCode::KEY_LEFT_ARROW)] = 0;
				}
				_inputType[CHAR(EventKeyboard::KeyCode::KEY_LEFT_ARROW)] = INPUT_TRG::OFF_MOMENT;
			}
		});

		layer->addChild(button);
	}

	// ƒWƒƒƒ“ƒv
	{
		ui::Button * button = ui::Button::create();
		button->setTouchEnabled(true);
		button->loadTextures("JumpButton.png", "JumpButton.png", "");
		button->setPosition({ 910,50 });
		button->setGlobalZOrder(20);
		button->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type)
		{
			if (type == ui::Widget::TouchEventType::BEGAN)
			{
				if (!_nowInputType.insert(std::make_pair(CHAR(EventKeyboard::KeyCode::KEY_UP_ARROW), 1)).second)
				{
					_nowInputType[CHAR(EventKeyboard::KeyCode::KEY_UP_ARROW)] = 1;
				}
				_inputType[CHAR(EventKeyboard::KeyCode::KEY_UP_ARROW)] = INPUT_TRG::ON_MOMENT;
			}
			if (type == ui::Widget::TouchEventType::ENDED || type == ui::Widget::TouchEventType::CANCELED)
			{
				if (!_nowInputType.insert(std::make_pair(CHAR(EventKeyboard::KeyCode::KEY_UP_ARROW), 0)).second)
				{
					_nowInputType[CHAR(EventKeyboard::KeyCode::KEY_UP_ARROW)] = 0;
				}
				_inputType[CHAR(EventKeyboard::KeyCode::KEY_UP_ARROW)] = INPUT_TRG::OFF_MOMENT;
			}
		});

		layer->addChild(button);
	}
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

	/*if (startPos.y > currentPos.y + reservoir)
	{
		if(!_nowInputType.insert(std::make_pair(CHAR(EventKeyboard::KeyCode::KEY_DOWN_ARROW), 1)).second)
		{
			_nowInputType[CHAR(EventKeyboard::KeyCode::KEY_DOWN_ARROW)] = 1;
		}
		_inputType[CHAR(EventKeyboard::KeyCode::KEY_DOWN_ARROW)] = INPUT_TRG::ON_MOMENT;
	}

	if (startPos.y < currentPos.y - reservoir)
	{
		if (!_nowInputType.insert(std::make_pair(CHAR(EventKeyboard::KeyCode::KEY_UP_ARROW), 1)).second)
		{
			_nowInputType[CHAR(EventKeyboard::KeyCode::KEY_UP_ARROW)] = 1;
		}
		_inputType[CHAR(EventKeyboard::KeyCode::KEY_UP_ARROW)] = INPUT_TRG::ON_MOMENT;
	}

	if (startPos.x < currentPos.x - reservoir)
	{
		if (!_nowInputType.insert(std::make_pair(CHAR(EventKeyboard::KeyCode::KEY_RIGHT_ARROW), 1)).second)
		{
			_nowInputType[CHAR(EventKeyboard::KeyCode::KEY_RIGHT_ARROW)] = 1;
		}
		_inputType[CHAR(EventKeyboard::KeyCode::KEY_RIGHT_ARROW)] = INPUT_TRG::ON_MOMENT;
	}

	if (startPos.x > currentPos.x + reservoir)
	{
		if (!_nowInputType.insert(std::make_pair(CHAR(EventKeyboard::KeyCode::KEY_LEFT_ARROW), 1)).second)
		{
			_nowInputType[CHAR(EventKeyboard::KeyCode::KEY_LEFT_ARROW)] = 1;
		}
		_inputType[CHAR(EventKeyboard::KeyCode::KEY_LEFT_ARROW)] = INPUT_TRG::ON_MOMENT;
	}*/
}

void TouchInput::OffTouch(cocos2d::Touch * touch, cocos2d::Event * event)
{
	for (auto &input : _nowInputType)
	{
		_inputType[input.first] = INPUT_TRG::OFF;
		input.second = 0;
		_oldInputType[input.second] = 0;
	}
}
