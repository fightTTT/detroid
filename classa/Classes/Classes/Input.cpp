#include "Input.h"

void OprtState::Init(void)
{
	for (auto& index : _keyIndex)
	{
		index = -1;
	}
	_currentIndex = 0;
}

void OprtState::Update(void)
{
	if (_previousVectorData.size() != _vectorData.size())
	{
		log("Data count is not match.");
		return;
	}

	for (int i = 0; i < _vectorData.size(); i++)
	{
		_previousVectorData[i] = _vectorData[i].second;
	}
}

const bool OprtState::GetKey(EventKeyboard::KeyCode key)
{
	if (GetKeyIndex(key) == -1)
	{
		RegisterKey(key);
	}

	return _vectorData[GetKeyIndex(key)].second;
}

const bool OprtState::GetKey(EventKeyboard::KeyCode key, INPUT_TYPE type)
{
	switch (type)
	{
	case INPUT_TYPE::UP:
		return !GetKey(key);
		break;
	case INPUT_TYPE::UP_MOMENT:
		return GetKeyUp(key);
		break;
	case INPUT_TYPE::DOWN:
		return GetKey(key);
		break;
	case INPUT_TYPE::DOWN_MOMENT:
		return GetKeyDown(key);
		break;
	}

	return false;
}

const bool OprtState::GetKeyDown(EventKeyboard::KeyCode key)
{
	if (GetKeyIndex(key) == -1)
	{
		RegisterKey(key);
	}

	return _vectorData[GetKeyIndex(key)].second && !_previousVectorData[GetKeyIndex(key)];
}

const bool OprtState::GetKeyUp(EventKeyboard::KeyCode key)
{
	if (GetKeyIndex(key) == -1)
	{
		RegisterKey(key);
	}

	return !_vectorData[GetKeyIndex(key)].second && _previousVectorData[GetKeyIndex(key)];
}

bool OprtState::RegisterKey(EventKeyboard::KeyCode key)
{
	for (int i = 0; i < _vectorData.size(); i++)
	{
		if (_vectorData[i].first == key)
		{
			//log("Key %d is already registered.", key);
			return false;
		}
	}	

	_vectorData.emplace_back(key, false);
	_previousVectorData.emplace_back(0);
	SetKeyIndex(key);
	//log("Key %d is registered to index %d.",key,_currentIndex - 1);
	return true;
}

void OprtState::SetKeyIndex(EventKeyboard::KeyCode key)
{
	_keyIndex[static_cast<int>(key)] = _currentIndex;
	_currentIndex++;
}

const int OprtState::GetKeyIndex(EventKeyboard::KeyCode key)
{
	return _keyIndex[static_cast<int>(key)];
}
