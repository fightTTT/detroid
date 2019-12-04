#include "KeyInput.h"

#define KEYCODE(key)		EventKeyboard::KeyCode(key)
#define CHAR(keyCode)		static_cast<char>(keyCode)

USING_NS_CC;
	
void KeyInput::Init(Node * node)
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

		_inputType[CHAR(keyCode)] = INPUT_TRG::OFF_MOM;

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
	for (auto trgType : _nowInputType)
	{
		// oldKey��NowKey�̓��͏�Ԃ�����Ă����Ƃ��ɒ��ɓ���
		if (_oldInputType[trgType.first] != _nowInputType[trgType.first])
		{
			// �������u��,�������u�Ԃ̏�������������A����������ɕς���
			if (_inputType[CHAR(trgType.first)] == INPUT_TRG::ON_MOMENT)
			{
				_inputType[CHAR(trgType.first)] = INPUT_TRG::ON;
			}
			else if (_inputType[CHAR(trgType.first)] == INPUT_TRG::OFF_MOM)
			{
				_inputType[CHAR(trgType.first)] = INPUT_TRG::OFF;
			}
			else
			{
				// ��L�̂ǂ���ł��Ȃ������ꍇ�͉������Ȃ�
			}
		}

		if (_oldInputType.insert(std::make_pair(CHAR(trgType.first),_nowInputType[trgType.first])).second)
		{
			_oldInputType[trgType.first] = _nowInputType[trgType.first];
		}
	}
}
