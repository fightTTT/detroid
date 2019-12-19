#pragma once
#include "Player.h"

struct  KeyCheck
{
	// キーをチェックする処理
	bool operator()(Sprite& sprite, Setting& setting);
};