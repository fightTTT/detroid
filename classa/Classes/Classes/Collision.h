#pragma once
#include "cocos2d.h"

USING_NS_CC;

bool BlockCheck(Node* node, float speed, int dir);
bool BlockCheck(Vec2 pos);				// ture : �����𓖂������@false : �ʂ��
bool BlockCheck(std::vector<Vec2> pos);
bool SlopeCheck(Node* node, float speed, int dir);