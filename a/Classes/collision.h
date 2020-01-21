#pragma once
#include "ActCtrl.h"

// 壁またはマップレイヤーとの当たり判定。	true...当たった	false...当たってない
struct MoveCol
{
	bool operator()(cocos2d::Sprite &sprite, ActModule &actModule);
};
