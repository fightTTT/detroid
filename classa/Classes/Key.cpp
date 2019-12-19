#include "Key.h"
#include <algorithm>

void OprtInputKey::Init(void)
{
	for (auto& index : _keyIndex)
	{
		index = -1;
	}
	_currentIndex = 0;

	auto moveKey = EventListenerKeyboard::create();

	// キーを押した瞬間にデータを true にする
	moveKey->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, Event * event)
	{
		if (GetKeyIndex(keyCode) != -1)
		{
			_vectorData[GetKeyIndex(keyCode)].second = true;
			log("Key %d is pressed.", keyCode);
		}
	};

	// 押しているキーを離したらデータを false にする
	moveKey->onKeyReleased = [&](EventKeyboard::KeyCode keyCode, Event * evnet)
	{
		if (GetKeyIndex(keyCode) != -1)
		{
			_vectorData[GetKeyIndex(keyCode)].second = false;
			log("Key %d is released.", keyCode);
		}
	};

	// セットした条件とデータの変更を登録する
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(moveKey, this);
}