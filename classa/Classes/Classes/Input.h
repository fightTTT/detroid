#pragma once
#include "cocos2d.h"
#include <vector>
#include <map>

enum class INPUT_TYPE
{
	EMPTY = -1,
	NONE,
	UP,				// キーが押してない状態で true お返す
	UP_MOMENT,		// キーを離した瞬間に true お返す
	DOWN,			// キーが押している状態で true お返す
	DOWN_MOMENT,	// キーを押した瞬間に true お返す
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
	const bool GetKey(EventKeyboard::KeyCode key);						// キーの押しっぱなし
	const bool GetKey(EventKeyboard::KeyCode key, INPUT_TYPE type);		// キーとタイプ
	const bool GetKeyDown(EventKeyboard::KeyCode key);					// キーの押した瞬間
	const bool GetKeyUp(EventKeyboard::KeyCode key);					// キーの離した瞬間
	bool RegisterKey(EventKeyboard::KeyCode key);						// キーを登録する
protected:
	std::vector<std::pair<EventKeyboard::KeyCode, bool>> _vectorData;	// 登録されたキーの配列
	int _keyIndex[256];													// キーの配列ID
	int _currentIndex;													// 現在の配列ID
	void SetKeyIndex(EventKeyboard::KeyCode key);						// 登録されたキーのIDをセットする
	const int GetKeyIndex(EventKeyboard::KeyCode key);					// 登録されたキーのIDをゲットする
	std::vector<int> _previousVectorData;								// １フレーム前の状態
};