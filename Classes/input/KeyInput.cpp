#include "KeyInput.h"

#define CHAR(keyCode)	 static_cast<char>(keyCode)

USING_NS_CC;
	
void KeyInput::Init(Node * node)
{
	for (int keyCode = 0; keyCode < static_cast<int>(EventKeyboard::KeyCode::KEY_PLAY); keyCode++)
	{
		inputType.try_emplace(CHAR(EventKeyboard::KeyCode(keyCode)), INPUT_TRG::OFF);
	}
	
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, cocos2d::Event* event)->bool
	{
		
		if (!nowInputType.try_emplace(CHAR(keyCode), 1).second)
		{
			nowInputType[CHAR(keyCode)] = 1;
		}
		
		inputType[CHAR(keyCode)] = INPUT_TRG::ON_MOM;
		
		return true;
	};

	listener->onKeyReleased = [&](EventKeyboard::KeyCode keyCode, Event* event)->bool
	{

		nowInputType[CHAR(keyCode)] = 0;

		inputType[CHAR(keyCode)] = INPUT_TRG::OFF_MOM;

		if(keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
		{
			Director::getInstance()->end();
		}

		return true;
	};

	node->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, node);
}

void KeyInput::Update()
{
	for (auto trgType : nowInputType)
	{
		if (oldInputType[trgType.first] != nowInputType[trgType.first])
		{
			if (inputType[CHAR(trgType.first)] == INPUT_TRG::ON_MOM)
			{
				inputType[CHAR(trgType.first)] = INPUT_TRG::ON;
			}
			else if (inputType[CHAR(trgType.first)] == INPUT_TRG::OFF_MOM)
			{
				inputType[CHAR(trgType.first)] = INPUT_TRG::OFF;
			}
			else
			{
				// è„ãLÇÃÇ«ÇøÇÁÇ≈Ç‡Ç»Ç©Ç¡ÇΩèÍçáÇÕâΩÇ‡ÇµÇ»Ç¢
			}
		}

		if (oldInputType.try_emplace(CHAR(cocos2d::EventKeyboard::KeyCode(trgType.first)),
			nowInputType[trgType.first]).second)
		{
			oldInputType[trgType.first] = nowInputType[trgType.first];
		}
	}
}
