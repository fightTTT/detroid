#pragma once
#include "Character.h"

struct AnimationChanger
{
	// キャラのアニメーションを変える処理
	bool operator()(Sprite& sprite, Setting& setting);
};