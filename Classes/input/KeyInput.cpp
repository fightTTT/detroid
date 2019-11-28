#include "KeyInput.h"

#define KEYCODE(key)		EventKeyboard::KeyCode(key)
#define CHAR(keyCode)		static_cast<char>(keyCode)

USING_NS_CC;
	
void KeyInput::Init(Node * node)
{
	for (int keyCode = 0; keyCode < static_cast<int>(EventKeyboard::KeyCode::KEY_PLAY); keyCode++)
	{
		inputType.insert(std::make_pair(CHAR(KEYCODE(keyCode)), INPUT_TRG::OFF));
	}
	
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, cocos2d::Event* event)->bool
	{
		
		if (!nowInputType.insert(std::make_pair(CHAR(keyCode), 1)).second)
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
		// oldKey‚ÆNowKey‚Ì“ü—Íó‘Ô‚ªˆá‚Á‚Ä‚¢‚½‚Æ‚«‚É’†‚É“ü‚é
		if (oldInputType[trgType.first] != nowInputType[trgType.first])
		{
			// ‰Ÿ‚µ‚½uŠÔ,—£‚µ‚½uŠÔ‚Ìî•ñ‚ğ‰Ÿ‚µ‘±‚¯‚éA—£‚µ‘±‚¯‚é‚É•Ï‚¦‚é
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
				// ã‹L‚Ì‚Ç‚¿‚ç‚Å‚à‚È‚©‚Á‚½ê‡‚Í‰½‚à‚µ‚È‚¢
			}
		}

		if (oldInputType.insert(std::make_pair(CHAR(trgType.first),nowInputType[trgType.first])).second)
		{
			oldInputType[trgType.first] = nowInputType[trgType.first];
		}
	}
}
