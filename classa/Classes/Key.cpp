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

	// �L�[���������u�ԂɃf�[�^�� true �ɂ���
	moveKey->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, Event * event)
	{
		if (GetKeyIndex(keyCode) != -1)
		{
			_vectorData[GetKeyIndex(keyCode)].second = true;
			log("Key %d is pressed.", keyCode);
		}
	};

	// �����Ă���L�[�𗣂�����f�[�^�� false �ɂ���
	moveKey->onKeyReleased = [&](EventKeyboard::KeyCode keyCode, Event * evnet)
	{
		if (GetKeyIndex(keyCode) != -1)
		{
			_vectorData[GetKeyIndex(keyCode)].second = false;
			log("Key %d is released.", keyCode);
		}
	};

	// �Z�b�g���������ƃf�[�^�̕ύX��o�^����
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(moveKey, this);
}