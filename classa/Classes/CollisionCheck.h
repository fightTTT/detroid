#pragma once
#include "Character.h"

struct CollisionCheck
{
	// �L�����ƃ}�b�v�̓����蔻����`�F�b�N���鏈��
	bool operator()(Sprite& sprite, Setting& setting);
};