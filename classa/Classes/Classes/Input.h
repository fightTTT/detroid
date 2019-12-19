#pragma once
#include "cocos2d.h"
#include <vector>
#include <map>

enum class INPUT_TYPE
{
	EMPTY = -1,
	NONE,
	UP,				// �L�[�������ĂȂ���Ԃ� true ���Ԃ�
	UP_MOMENT,		// �L�[�𗣂����u�Ԃ� true ���Ԃ�
	DOWN,			// �L�[�������Ă����Ԃ� true ���Ԃ�
	DOWN_MOMENT,	// �L�[���������u�Ԃ� true ���Ԃ�
	MAX,
};

enum class DIR {
	NONE = -1,
	UP,
	LEFT,
	DOWN,
	RIGHT,
	MAX,
};

USING_NS_CC;

struct OprtState : public Layer
{
	virtual void Init(void);
	void Update(void);
	const bool GetKey(EventKeyboard::KeyCode key);						// �L�[�̉������ςȂ�
	const bool GetKey(EventKeyboard::KeyCode key, INPUT_TYPE type);		// �L�[�ƃ^�C�v
	const bool GetKeyDown(EventKeyboard::KeyCode key);					// �L�[�̉������u��
	const bool GetKeyUp(EventKeyboard::KeyCode key);					// �L�[�̗������u��
	bool RegisterKey(EventKeyboard::KeyCode key);						// �L�[��o�^����
protected:
	std::vector<std::pair<EventKeyboard::KeyCode, bool>> _vectorData;	// �o�^���ꂽ�L�[�̔z��
	int _keyIndex[256];													// �L�[�̔z��ID
	int _currentIndex;													// ���݂̔z��ID
	void SetKeyIndex(EventKeyboard::KeyCode key);						// �o�^���ꂽ�L�[��ID���Z�b�g����
	const int GetKeyIndex(EventKeyboard::KeyCode key);					// �o�^���ꂽ�L�[��ID���Q�b�g����
	std::vector<int> _previousVectorData;								// �P�t���[���O�̏��
};