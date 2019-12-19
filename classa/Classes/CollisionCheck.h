#pragma once
#include "Character.h"

struct CollisionCheck
{
	// キャラとマップの当たり判定をチェックする処理
	bool operator()(Sprite& sprite, Setting& setting);
};