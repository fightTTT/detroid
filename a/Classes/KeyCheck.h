#pragma once
#include "ActCtrl.h"

// �ǂ܂��̓}�b�v���C���[�Ƃ̓����蔻��B	true...��������	false...�������ĂȂ�
struct KeyCheck
{
	bool operator()(cocos2d::Sprite &sprite, ActModule &actModule);
};