#pragma once
#include "Character.h"

struct Jump 
{
	// ジャンプ中の処理
	bool operator()(Sprite& sprite, Setting& setting);
};