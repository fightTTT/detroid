#include "KeyInput.h"

USING_NS_CC;
	
void KeyInput::Init(Node * node, cocos2d::Layer* layer)
{
	for (int keyCode = 0; keyCode < static_cast<int>(EventKeyboard::KeyCode::KEY_PLAY); keyCode++)
	{
		_inputType.insert(std::make_pair(CHAR(KEYCODE(keyCode)), INPUT_TRG::OFF));
	}
	
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, cocos2d::Event* event)->bool
	{
		if (!_nowInputType.insert(std::make_pair(CHAR(keyCode), 1)).second)
		{
			_nowInputType[CHAR(keyCode)] = 1;
		}
		
		_inputType[CHAR(keyCode)] = INPUT_TRG::ON_MOMENT;
		
		return true;
	};

	listener->onKeyReleased = [&](EventKeyboard::KeyCode keyCode, Event* event)->bool
	{
		_nowInputType[CHAR(keyCode)] = 0;

		_inputType[CHAR(keyCode)] = INPUT_TRG::OFF_MOMENT;

		if(keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
		{
			Director::getInstance()->end();
		}

		return true;
	};

	node->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, node);
}
