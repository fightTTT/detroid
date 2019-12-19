#include "Touch.h"
#include "ui//CocosGUI.h"

void OprtInputTouch::Init(void)
{
	for (auto& index : _keyIndex)
	{
		index = -1;
	}
	_currentIndex = 0;

	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto leftButton = ui::Button::create("Left.png");
	leftButton->setOpacity(180);
	leftButton->setPosition(Vec2(100.0f, 100.0f));
	leftButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		auto keyCode = EventKeyboard::KeyCode::KEY_A;
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			if (GetKeyIndex(keyCode) != -1)
			{
				_vectorData[GetKeyIndex(keyCode)].second = true;
				log("Key %d is pressed.", keyCode);
			}
			break;
		case ui::Widget::TouchEventType::ENDED:
			if (GetKeyIndex(keyCode) != -1)
			{
				_vectorData[GetKeyIndex(keyCode)].second = false;
				log("Key %d is released.", keyCode);
			}
			break;
		case ui::Widget::TouchEventType::CANCELED:
			if (GetKeyIndex(keyCode) != -1)
			{
				_vectorData[GetKeyIndex(keyCode)].second = false;
				log("Key %d is released.", keyCode);
			}
			break;
		default:
			break;
		}
	});

	auto rightButton = ui::Button::create("Right.png");
	rightButton->setOpacity(180);
	rightButton->setPosition(Vec2(250.0f, 100.0f));
	rightButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		auto keyCode = EventKeyboard::KeyCode::KEY_D;
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			if (GetKeyIndex(keyCode) != -1)
			{
				_vectorData[GetKeyIndex(keyCode)].second = true;
				log("Key %d is pressed.", keyCode);
			}
			break;
		case ui::Widget::TouchEventType::ENDED:
			if (GetKeyIndex(keyCode) != -1)
			{
				_vectorData[GetKeyIndex(keyCode)].second = false;
				log("Key %d is released.", keyCode);
			}
			break;
		case ui::Widget::TouchEventType::CANCELED:
			if (GetKeyIndex(keyCode) != -1)
			{
				_vectorData[GetKeyIndex(keyCode)].second = false;
				log("Key %d is released.", keyCode);
			}
			break;
		default:
			break;
		}
	});

	auto fireButton = ui::Button::create("button_fire.png");
	fireButton->setOpacity(180);
	fireButton->setPosition(Vec2(visibleSize.width - 100.0f, 100.0f));
	fireButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		auto keyCode = EventKeyboard::KeyCode::KEY_F;
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			if (GetKeyIndex(keyCode) != -1)
			{
				_vectorData[GetKeyIndex(keyCode)].second = true;
				log("Key %d is pressed.", keyCode);
			}
			break;
		case ui::Widget::TouchEventType::ENDED:
			if (GetKeyIndex(keyCode) != -1)
			{
				_vectorData[GetKeyIndex(keyCode)].second = false;
				log("Key %d is released.", keyCode);
			}
			break;
		case ui::Widget::TouchEventType::CANCELED:
			if (GetKeyIndex(keyCode) != -1)
			{
				_vectorData[GetKeyIndex(keyCode)].second = false;
				log("Key %d is released.", keyCode);
			}
			break;
		default:
			break;
		}
	});

	auto jumpButton = ui::Button::create("button_jump.png");
	jumpButton->setOpacity(180);
	jumpButton->setPosition(Vec2(visibleSize.width - 250.0f, 100.0f));
	jumpButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		auto keyCode = EventKeyboard::KeyCode::KEY_SPACE;
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			if (GetKeyIndex(keyCode) != -1)
			{
				_vectorData[GetKeyIndex(keyCode)].second = true;
				log("Key %d is pressed.",keyCode);
			}
			break;
		case ui::Widget::TouchEventType::ENDED:
			if (GetKeyIndex(keyCode) != -1)
			{
				_vectorData[GetKeyIndex(keyCode)].second = false;
				log("Key %d is released.",keyCode);
			}
			break;
		case ui::Widget::TouchEventType::CANCELED:
			if (GetKeyIndex(keyCode) != -1)
			{
				_vectorData[GetKeyIndex(keyCode)].second = false;
				log("Key %d is released.", keyCode);
			}
			break;
		default:
			break;
		}
	});

	this->addChild(leftButton);
	this->addChild(rightButton);
	this->addChild(fireButton);
	this->addChild(jumpButton);
}